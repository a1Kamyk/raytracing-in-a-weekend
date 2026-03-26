#include "Material.h"

#include "Utility.h"

bool Material::scatter(const Ray& rayIn, HitRecord& hitRecord, Color& attenuation, Ray& scattered) const {
    return false;
}

// Lambertian
Lambertian::Lambertian(const Color& albedo) :
    m_albedo(albedo) {}

bool Lambertian::scatter(const Ray& rayIn, HitRecord& hitRecord, Color& attenuation, Ray& scattered) const {
    Vec3 scatterDirection = hitRecord.normal + Vec3::randomUnitVector();

    // Edge case where randomUnitVector is exactly -normal
    if (scatterDirection.isZero())
        scatterDirection = hitRecord.normal;

    scatterDirection.normalizeSelf();

    scattered = Ray(hitRecord.point, scatterDirection, rayIn.time());
    attenuation = m_albedo;

    return true;
}

Metal::Metal(const Color& albedo, const double fuzziness) :
    m_albedo(albedo), m_fuzziness(fuzziness) {}

bool Metal::scatter(const Ray& rayIn, HitRecord& hitRecord, Color& attenuation, Ray& scattered) const {
    Vec3 reflected = reflect(rayIn.direction(), hitRecord.normal);
    reflected = reflected.normalizeSelf() + (m_fuzziness * Vec3::randomUnitVector());
    reflected.normalizeSelf();

    scattered = Ray(hitRecord.point, reflected, rayIn.time());
    attenuation = m_albedo;

    return (dot(scattered.direction(), hitRecord.normal) > 0);
}

Dielectric::Dielectric(const double refractionIndex) :
    m_refractionIndex(refractionIndex) {}

bool Dielectric::scatter(const Ray& rayIn, HitRecord& hitRecord, Color& attenuation, Ray& scattered) const {
    attenuation = Color(1.0, 1.0, 1.0);
    const double refractionIndex = hitRecord.frontFace ? (1.0 / m_refractionIndex) : m_refractionIndex;

    // TODO check if all rays have normalized direction to optimize
    const Vec3 unitDirection = rayIn.direction().normalize();
    const double cosTheta = std::fmin(dot(-unitDirection, hitRecord.normal), 1.0);
    const double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

    const bool canRefract = refractionIndex * sinTheta < 1.0;

    Vec3 direction{};
    if (!canRefract || reflectance(cosTheta, refractionIndex) > randomDouble())
        direction = reflect(rayIn.direction(), hitRecord.normal);
    else
        direction = refract(unitDirection, hitRecord.normal, refractionIndex);

    scattered = Ray(hitRecord.point, direction, rayIn.time());
    return true;
}

double Dielectric::reflectance(const double cosine, const double refractionIndex) {
    // Using Sclick's approximation for reflectance
    double r0 = (1 - refractionIndex) / (1 + refractionIndex);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}
