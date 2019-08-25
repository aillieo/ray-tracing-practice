
#include "Camera.h"
#include "Random.h"
using namespace raytracing_1;

Camera::Camera(Vector3 origin0, Vector3 lookat, Vector3 up, float vfov, float aspect, float aperture, float focusDist)
{
    float theta = vfov * M_PI / 180;
    float half_height = tan(theta / 2);
    float half_width = aspect * half_height;
    
    lensRadius = aperture / 2;
    
    // 指向相机内（屏幕外）
    w = normalize(origin0 - lookat);
    // 指向面朝屏幕右手
    u = normalize(cross(up, w));
    // 是投影不一定是up
    v = cross(w, u);
    
    origin = origin0;
    lb = origin  - half_width * focusDist * u - half_height * focusDist * v - focusDist * w;
    horizontal = 2 * half_width * focusDist * u;
    vertical = 2 * half_height * focusDist * v;
}

Ray Camera::getRay(float u0, float v0)
{
    Vector3 rd = lensRadius* Random::randomInUnitDisk();
    Vector3 offset = u * rd.x + v * rd.y;
    return Ray(origin + offset,
               lb + u0 * horizontal + v0 * vertical - (origin + offset));
}


