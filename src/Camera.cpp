#include "Camera.h"

#include <atomic>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "Material.h"
#include "Utility.h"

std::atomic<int> completedRows{0};
constexpr double infinity = std::numeric_limits<double>::infinity();

Camera::Camera() {
    this->initialize();
}

void Camera::render(const HittableList& world) {
    this->initialize();

    std::vector<std::tuple<int, int, int>> pixels(this->imageWidth * this->imageHeight);
    std::fstream file("output.ppm", std::ios::out);

    // File header
    file << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    // Start timer
    const auto start = std::chrono::system_clock::now();

    #pragma omp parallel for
    for (int j = 0; j < imageHeight; j++) {
        for (int i = 0; i < imageWidth; i++) {
            Color pixelColor = {0,0,0};
            for (int sample = 0; sample < samplesPerPixel; sample++) {
                Ray ray = getRay(i, j);
                pixelColor += rayColor(ray, maxDepth, world);
            }
            pixels[j * imageWidth + i] = normalizeColor(pixelColor * pixelSamplesScale);
        }
        // Progress display
        if (int current = ++completedRows; current % 20 == 0 || current == imageHeight) {
            #pragma omp critical
            {
                float progress = static_cast<float>(current) / static_cast<float>(imageHeight) * 100.0f;
                std::cout << "Rendering: " << std::fixed << std::setprecision(1)
                    << progress << "% complete\n" << std::flush;
            }
        }
    }

    // Stop timer
    const auto stop = std::chrono::system_clock::now();
    const auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    const auto timePerPixel = static_cast<double>(time.count()) / (imageWidth * imageHeight);

    for (auto pixel : pixels) {
        file << std::get<0>(pixel) << ' ' <<
                std::get<1>(pixel) << ' ' <<
                std::get<2>(pixel) << '\n';
    }

    std::clog << std::format("\rDone, time taken: {:.3f} ms, time per pixel: {:.3f} ns\n", static_cast<double>(time.count()) / 1e6, timePerPixel);
}

void Camera::initialize() {
    imageHeight = static_cast<int>(imageWidth / aspectRatio);
    imageHeight = imageHeight > 0 ? imageHeight : 1;

    pixelSamplesScale = 1.0 / samplesPerPixel;

    center = lookFrom;

    // Determine viewport dimensions
    const double theta = degreesToRadians(vFov);
    const double h  = tan(theta / 2);
    const double viewportHeight = 2.0 * h * focusDistance;
    const double viewportWidth = viewportHeight * (static_cast<double>(imageWidth) / imageHeight);

    // Calculate the u, v, w unit basis vectors for the camera coordinate frame
    w = (lookFrom - lookAt).normalize();
    u = cross(vectorUp, w).normalize();
    v = cross(w, u);

    // Calculate vectors along the horizontal and vertical viewport edges
    const Vec3 viewportU = viewportWidth * u;
    const Vec3 viewportV = viewportHeight * -v;

    // Calculate the horizontal and vertical delta vectors from pixel to pixel
    pixelDeltaU = viewportU / imageWidth;
    pixelDeltaV = viewportV / imageHeight;

    // Calculate the location of the upper left pixel
    const Point3 viewportUpperLeft = center -
                                 (focusDistance * w)
                                 - viewportU/2
                                 - viewportV/2;
    originPixelLocation = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

    // Calculate the camera defocus disk basis vectors
    const double defocusRadius = focusDistance * std::tan(degreesToRadians(defocusAngle) / 2);
    defocusDiskU = u * defocusRadius;
    defocusDiskV = v * defocusRadius;
}

Ray Camera::getRay(const int x, const int y) const {
    // Construct a ray directed at randomly sampled point around pixel (x, y)

    const Vec3 offset = sampleSquare();
    const Vec3 pixelCenter = originPixelLocation +
                            (x + offset.x) * pixelDeltaU +
                            (y + offset.y) * pixelDeltaV;
    const Point3 rayOrigin = defocusAngle <= 0 ? center : defocusDiskSample();
    const Vec3 rayDirection = (pixelCenter - center).normalize();
    const double rayTime = randomDouble();

    return {rayOrigin, rayDirection, rayTime};
}

Point3 Camera::defocusDiskSample() const {
    // Returns random point in camera focus disk
    const Vec3 p = Vec3::randomInUnitDisk();
    return center + (p.x * defocusDiskU) + (p.y * defocusDiskV);
}

Vec3 Camera::sampleSquare() {
    // Returns a vector to a random point within the [-0.5, -0.5] to [0.5, 0.5] unit square
    return {
        randomDouble() - 0.5,
        randomDouble() - 0.5,
        0
    };
}

Color Camera::rayColor(const Ray& ray, const int depth, const HittableList& world) {
    if (depth <= 0)
        return {0,0,0};

    HitRecord hitRecord{};

    if (const bool hit = world.hit(ray, {1e-4, infinity}, hitRecord); hit) {
        Ray scattered;
        Color attenuation;
        if (hitRecord.material->scatter(ray, hitRecord, attenuation, scattered)) {
            return attenuation * rayColor(scattered, depth - 1, world);
        }

        return {0,0,0};
    }

    const Vec3 unitDirection = ray.unitDirection();
    // Get coefficient in range [0, 1], based on y component in range [-1, 1]
    const double coef = 0.5 * (unitDirection.y + 1.0);
    const Color result = (1.0 - coef) * Color(1.0,1.0,1.0) + coef * Color(0.5, 0.7, 1.0);
    return result;
}