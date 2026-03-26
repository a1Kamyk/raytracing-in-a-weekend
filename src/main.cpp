#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"
#include "Plane.h"
#include "Utility.h"

int main() {
    HittableList world;

    auto groundMaterial = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(std::make_unique<Plane>(Point3(0, 0, 0), Vec3(0, 1, 0), groundMaterial));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            const auto choose_mat = randomDouble();
            Point3 center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());

            if ((center - Point3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> Sphere_Material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Color::random() * Color::random();
                    Sphere_Material = std::make_shared<Lambertian>(albedo);
                    const Point3 centerEnd = center + Vec3(0, randomDouble(0, 0.5), 0);
                    world.add(std::make_unique<Sphere>(center, centerEnd, 0.2, Sphere_Material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Color::random(0.5, 1);
                    auto fuzz = randomDouble(0, 0.5);
                    Sphere_Material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_unique<Sphere>(center, 0.2, Sphere_Material));
                } else {
                    // glass
                    Sphere_Material = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_unique<Sphere>(center, 0.2, Sphere_Material));
                }
            }
        }
    }

    auto Material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_unique<Sphere>(Point3(0, 1, 0), 1.0, Material1));

    auto Material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(std::make_unique<Sphere>(Point3(-4, 1, 0), 1.0, Material2));

    auto Material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_unique<Sphere>(Point3(4, 1, 0), 1.0, Material3));

    Camera camera;

    camera.aspectRatio      = 16.0 / 9.0;
    camera.imageWidth       = 1920;
    camera.samplesPerPixel  = 50;
    camera.maxDepth         = 25;

    camera.vFov            = 20;
    camera.lookFrom        = Point3(13,2,3);
    camera.lookAt          = Point3(0,0,0);
    camera.vectorUp        = Vec3(0,1,0);

    camera.defocusAngle     = 0.6;
    camera.focusDistance    = 0.1;

    camera.render(world);
}