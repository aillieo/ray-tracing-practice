#pragma once

#include "Ray.h"
#include "Vector3.h"
#include <stdlib.h>
#include <iostream>
#include "Hitable.h"
#include "Material.h"

namespace raytracing_1
{
    class Sphere: public Hitable  {
    public:
        Sphere() : center(Vector3::Zero), radius(1.0f), material(nullptr) {}
        Sphere(Vector3 cen, float r, Material *mat) : center(cen), radius(r), material(mat)  {};
        virtual bool hit(const Ray& r, float t_min, float t_max, RaycastHit& hitInfo) const;
        virtual bool hit(const Ray& r, float maxDistance, RaycastHit& hitInfo) const;

        ~Sphere();
    protected:
        Vector3 center;
        float radius;
        Material *material;
    };
}
