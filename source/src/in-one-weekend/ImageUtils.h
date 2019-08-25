#pragma once
#include <string>
#include <vector>

using namespace std;
namespace raytracing_1
{
    class Color;
    class ImageUtils {

    public:
        static void saveImage(const string& file, const vector<int>& ppmStream);

        static void saveImage(const string& file, const int width, const int height, const vector<Color>& pixels);

    };
}
