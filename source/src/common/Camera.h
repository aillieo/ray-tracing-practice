#pragma once
#include "Vector3.h"
#include "Ray.h"
#include "RTDefine.h"

using namespace std;

namespace raytracing
{
	class Camera {

	public:

		Camera(
               Vector3 origin = Vector3::Zero,
               Vector3 lookat = Vector3::NegtiveZ,
               Vector3 up = Vector3::PositiveY,
               float vfov = 90,
               float aspect = 2,
               float aperture = 0,
               float focusDist = 1
               );
        
        Ray getRay(float u, float v);

	private:
		Vector3 origin;
        Vector3 u, v, w;
		Vector3 horizontal;
		Vector3 vertical;
		Vector3 lb;
        float lensRadius;

    };
    
}
