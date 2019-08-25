#pragma once

#include "Vector3.h"
#include <stdlib.h>
#include <iostream>

namespace raytracing_1
{
    class Ray {

    public:
        Ray():origin(Vector3::Zero),direction(Vector3::One) {}
        Ray(const Vector3& a, const Vector3& b): origin(a), direction(b) {}
        Vector3 pointAtDistance(float t) const { return lerp(origin,direction,t);}
        
        Vector3 origin;
        Vector3 direction;

    };
    
    float schlick(float cosine, float ref_idx);

    bool refract(const Vector3& in, const Vector3& normal, float ni_over_nt, Vector3& refracted);

    Vector3 reflect(const Vector3& in, const Vector3& normal);

}
