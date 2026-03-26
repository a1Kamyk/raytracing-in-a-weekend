#pragma once

#include "HittableList.h"

class Camera {
public:
    double aspectRatio  = 1.0;
    int imageWidth      = 100;
    int samplesPerPixel = 10;
    int maxDepth        = 10;

    double  vFov        = 90.0;
    Point3  lookFrom    = Point3(0,0,0);
    Point3  lookAt      = Point3(0,0,-1);
    Vec3    vectorUp    = Vec3(0,1,0);

    double defocusAngle     = 0.0;
    double focusDistance    = 10.0;

    Camera();

    void render(const HittableList& world);
private:
    int imageHeight{};
    double pixelSamplesScale{};
    Point3 center{};
    Point3 originPixelLocation{};
    Vec3 pixelDeltaU{};
    Vec3 pixelDeltaV{};
    Vec3 u{}, w{}, v{};
    Vec3 defocusDiskU{};
    Vec3 defocusDiskV{};

    void initialize();
    [[nodiscard]] Ray getRay(int x, int y) const;
    [[nodiscard]] Point3 defocusDiskSample() const;
    static Vec3 sampleSquare();
    static Color rayColor(const Ray& ray, int depth, const HittableList& world);
};