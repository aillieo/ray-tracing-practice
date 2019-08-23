#include "Ray.h"

namespace raytracing
{
    float schlick(float cosine, float ref_idx) {
        float t = (1 - ref_idx) / (1 + ref_idx);
        float r0 = t * t;
        return r0 + (1 - r0)*pow((1 - cosine), 5);
    }
    
    bool refract(const Vector3& in, const Vector3& normal, float ni_over_nt, Vector3& refracted) 
    {
        Vector3 uv = normalize(in);
        float dt = dot(uv, normal);
        float discriminant = 1.0 - ni_over_nt * ni_over_nt*(1 - dt * dt);
        if (discriminant > 0) {
            refracted = ni_over_nt * (uv - normal * dt) - normal * sqrt(discriminant);
            return true;
        }
        else
            return false;
    }

    Vector3 reflect(const Vector3& in, const Vector3& normal)
    {
        return in - 2*dot(in,normal) * normal;
    }
}
