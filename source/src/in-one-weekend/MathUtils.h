#pragma once
#include <string>
#include <algorithm>

using namespace std;
namespace raytracing_1
{
    namespace MathUtils{

        template<typename T>
        inline T max(T x, T y)
        {
            return x > y ? x : y;
        }
        
        template<typename T>
        inline T min(T x, T y)
        {
            return x < y ? x : y;
        }

        template<typename T>
        inline T clamp(T value, T min, T max)
        {
            if (value > max)
            {return max;}
            else if(value < min)
            {return min;}
            return value;
        }
    }
}
