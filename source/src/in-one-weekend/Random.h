#pragma once
#include <string>
#include "Vector3.h"
#include "Color.h"

using namespace std;

namespace raytracing_1
{
	namespace Random {

        void init(unsigned seed);
		void init();
		int randomInt(int max = 0);
        double random01();
		Vector3 randomInUnitSphere();
		Vector3 randomInUnitDisk();
        Color randomColor();
    };
}
