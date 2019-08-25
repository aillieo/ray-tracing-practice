#include <vector>
#include "InOneWeekend.h"
#include "Color.h"
#include "Sphere.h"
#include "ImageUtils.h"
#include "MathUtils.h"
#include "HitableList.h"
#include "Camera.h"
#include "Random.h"

using namespace std;
using namespace raytracing_1;

Color getColorForRay(const Ray& ray, const Hitable& scene, int depth = 0)
{
    RaycastHit hitInfo = RaycastHit();
    if (scene.hit(ray, 10000, hitInfo))
    {
        Ray scattered;
        Color attenuation = Color::White;
        if (depth < 50 && hitInfo.material->scatter(ray, hitInfo, attenuation, scattered)) 
        {
            // recursive getColor
            return attenuation * getColorForRay(scattered, scene, depth + 1);
        }
        else
        {
            return attenuation;
        }
    }
    else
    {
        // background color
        Vector3 dir = normalize(ray.direction);
        return Color(dir.x,dir.y,1) * 0.4 + Color::White * 0.6;
    }
}

void InOneWeekend::makeImage() {

    // configs
    int width = 800;
    int height = 400;
    int multiSampling = 64;

    //int width = 200;
    //int height = 100;
    //int multiSampling = 1;

    Camera cam = Camera(Vector3(0,30,300),Vector3(0,20,0),Vector3::PositiveY,30,2);
    //Camera cam = Camera(Vector3(0,30,300),Vector3(0,20,0),Vector3::PositiveY,60,2,0,1);
    
    HitableList scene = HitableList();
    scene.addHitable(new Sphere(Vector3(32, 15, 16), 15, new MatMetal(Color::Blue, 0.01)));
    scene.addHitable(new Sphere(Vector3(0, 15, 16), 15, new MatDielectric(1.3)));
    scene.addHitable(new Sphere(Vector3(-32, 15, 16), 15, new MatDielectric(1.2)));
    scene.addHitable(new Sphere(Vector3(-58, 55, -55), 55, new MatMetal(Color(0.9,0.9,1),0.01)));
    scene.addHitable(new Sphere(Vector3(58, 55, -55), 55, new MatMetal(Color::White,0.01)));
    scene.addHitable(new Sphere(Vector3(0, -1000000, 0), 1000000, new MatLambertian(Color::White)));

    for (int i = 0; i < 200; i ++)
    {
        Vector3 p = Random::randomInUnitDisk();
        float r = Random::random01() * 2 + 1;
        Vector3 center = Vector3(
            p.x * 100,
            r,
            p.y * 100 + 100
        );
        float randForMat = Random::random01();
        Material* mat = nullptr;
        if (randForMat > 0.66)
        {
            mat = new MatLambertian(Random::randomColor());
        }
        else if(randForMat > 0.33)
        {
            mat = new MatMetal(Random::randomColor(), 0.01);
        }
        else
        {
            mat = new MatDielectric(1.3);
        }
        scene.addHitable(new Sphere(center, r, mat));
    }
    
    vector<Color> colors = vector<Color>();
    // vertical
    for (int y = height - 1; y >= 0; --y)
    {
        cout << "start rendering line: " << y << endl;
        // horizontal
        for (int x = 0; x < width; ++x)
        {
            // anti aliasing
            Color c = Color::Black;
            for (int i = 0; i < multiSampling; ++i)
            {
                Ray r = cam.getRay(
                    (x + Random::random01()) / width,
                    (y + Random::random01()) / height
                );
                c += getColorForRay(r, scene);
            }
            c /= multiSampling;
            colors.push_back(c);
        }
        // cout << "end rendering line: " << y << endl;
    }

    ImageUtils::saveImage("___rt___.png", width, height, colors);

}
