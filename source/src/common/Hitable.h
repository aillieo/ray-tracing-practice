#pragma once

#include "Ray.h"
#include "Vector3.h"
#include <stdlib.h>
#include <iostream>

namespace raytracing
{
    class Material;
    
    struct RaycastHit
    {
        float distance;
        Vector3 hitPoint;
        Vector3 normal;
        Material *material;
    };
    
    // interface for hit
    class Hitable  {
    public:
        virtual bool hit(const Ray& r, float t_min, float t_max, RaycastHit& hitInfo) const = 0;
        virtual bool hit(const Ray& r, float maxDistance, RaycastHit& hitInfo) const = 0;

        virtual ~Hitable(){};
    };
}
