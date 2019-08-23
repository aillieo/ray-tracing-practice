#pragma once

#include "Ray.h"
#include <stdlib.h>
#include <vector>
#include "Hitable.h"
#include "Material.h"

namespace raytracing
{
    class HitableList: public Hitable  {
    public:
        HitableList();
        ~HitableList();
        
        const int addHitable(const Hitable* const hitable);
        virtual bool hit(const Ray& r, float t_min, float t_max, RaycastHit& hitInfo) const;
        virtual bool hit(const Ray& r, float maxDistance, RaycastHit& hitInfo) const;
    private:
        std::vector<const Hitable*> hitableList;
    };
}
