#include "Sphere.h"
using namespace raytracing;


// (r.pointAtDistance(t) - s.center).length() == s.radius
// got t

bool Sphere::hit(const Ray& r, float t_min, float t_max, RaycastHit& hitInfo) const
{
    Vector3 oc = r.origin - center;
    float a = dot(r.direction, r.direction);
    float b = dot(oc, r.direction);
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - a*c;
    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant))/a;
        if (temp < t_max && temp > t_min) {
            hitInfo.distance = temp;
            hitInfo.hitPoint = r.pointAtDistance(hitInfo.distance);
            hitInfo.normal = (hitInfo.hitPoint - center) / radius;
            hitInfo.material = material;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            hitInfo.distance = temp;
            hitInfo.hitPoint = r.pointAtDistance(hitInfo.distance);
            hitInfo.normal = (hitInfo.hitPoint - center) / radius;
            hitInfo.material = material;
            return true;
        }
    }
    return false;
}

Sphere::~Sphere() { 

}

bool Sphere::hit(const raytracing::Ray &r, float maxDistance, raytracing::RaycastHit &hitInfo) const { 
    return hit(r,0,maxDistance,hitInfo);
}


