#include <vector>
#include "HitableList.h"
using namespace raytracing_1;
using namespace std;

HitableList::HitableList() {
    hitableList = vector<const Hitable*>();
}

HitableList::~HitableList() {
    hitableList.clear();
}

bool HitableList::hit(const Ray& r, float t_min, float t_max, RaycastHit& hitInfo) const
{
    RaycastHit tempHitInfo;
    bool isHit = false;
    double closest = t_max;
    for(auto it = hitableList.begin(); it != hitableList.end(); it ++)
    {
        if((*it)->hit(r,t_min,t_max,tempHitInfo))
        {
            if(tempHitInfo.distance <= closest)
            {
                closest = tempHitInfo.distance;
                hitInfo = tempHitInfo;
                isHit = true;
            }
        }
    }
    return isHit;
}



bool HitableList::hit(const Ray &r, float maxDistance, RaycastHit &hitInfo) const {
    return hit(r,0,maxDistance,hitInfo);
}

const int HitableList::addHitable(const Hitable* const hitable) {
    hitableList.push_back(hitable);
    return hitableList.size();
}


