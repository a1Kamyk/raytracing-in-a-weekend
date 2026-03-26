#pragma once

#include "Hittable.h"

class Material {
public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray& rayIn, HitRecord& hitRecord, Color& attenuation, Ray& scattered) const;
};

class Lambertian  final : public Material {
public:
    explicit Lambertian(const Color& albedo);

    bool scatter(const Ray& rayIn, HitRecord& hitRecord, Color& attenuation, Ray& scattered) const override;

private:
    Color m_albedo{};
};

class Metal final : public Material {
public:
    explicit Metal(const Color& albedo, double fuzziness);

    bool scatter(const Ray& rayIn, HitRecord& hitRecord, Color& attenuation, Ray& scattered) const override;
private:
    Color m_albedo{};
    double m_fuzziness;
};

class Dielectric final : public Material {
public:
    explicit Dielectric(double refractionIndex);

    bool scatter(const Ray& rayIn, HitRecord& hitRecord, Color& attenuation, Ray& scattered) const override;
private:
    // Refractive index in vacuum, or ratio of the material's refractive index over the index of enclosing media
    double m_refractionIndex;

    static double reflectance(double cosine, double refractionIndex);
};