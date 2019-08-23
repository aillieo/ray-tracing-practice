#include "ImageUtils.h"
#include <string>
#include "svpng/svpng.inc"
#include <vector>
#include "Color.h"
#include "MathUtils.h"

using namespace raytracing;
using namespace std;

void ImageUtils::saveImage(const string& file, const vector<int>& ppmStream)
{
    if (ppmStream.size() < 3)
    {return;}
    int width = ppmStream.at(0);
    int height = ppmStream.at(1);
    if (ppmStream.size() < width * height * 3 + 3)
    {return;}

    unsigned char *data = new unsigned char[width * height * 3];
    FILE *fp = fopen(file.c_str(), "wb");
    for (int i = 0; i < width * height * 3; i++)
    {
        data[i] = (unsigned char)ppmStream.at(i+3);
    }
    svpng(fp, width, height, data, 0);
    fclose(fp);
    delete[]data;

}

void ImageUtils::saveImage(const string &file, const int width, const int height, const vector<Color>& pixels)
{
    if(width <= 0 || height <= 0)
    {return;}
    if (pixels.size() < width * height)
    {return;}
    
    unsigned char *data = new unsigned char[width * height * 3];
    FILE *fp = fopen(file.c_str(), "wb");
    for (int i = 0; i < width * height; i++)
    {
        data[i * 3    ] = (unsigned char)(MathUtils::clamp<int>((pixels.at(i).r * 255), 0, 255));
        data[i * 3 + 1] = (unsigned char)(MathUtils::clamp<int>((pixels.at(i).g * 255), 0, 255));
        data[i * 3 + 2] = (unsigned char)(MathUtils::clamp<int>((pixels.at(i).b * 255), 0, 255));
    }
    svpng(fp, width, height, data, 0);
    fclose(fp);
    delete[]data;
}

