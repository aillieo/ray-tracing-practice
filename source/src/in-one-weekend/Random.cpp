#include "Random.h"
#include <stdlib.h>
#include <time.h> 

using namespace raytracing_1;
using namespace std;

void Random::init(unsigned seed)
{
#ifdef WIN32
	srand(seed);
#else
	srand48(seed);
#endif
}

void Random::init()
{
	init((unsigned)time(NULL));
}

int Random::randomInt(int max)
{
	int r = rand();
	if (max > 0)
	{r %= max;}
	return r;
}

double Random::random01() {

#ifdef WIN32
    //return rand_s();
    return double(rand())/RAND_MAX;
#else
    return drand48();
#endif
}

Vector3 Random::randomInUnitSphere()
{
	Vector3 p;
	do 
	{
		p = 2.0 * Vector3(
			Random::random01(),
			Random::random01(),
			Random::random01()
		) - Vector3::One;
	} while (p.squaredLength() >= 1.0);
	return p;
}

Vector3 Random::randomInUnitDisk()
{
	Vector3 p;
	do
	{
		p = Vector3(
			2.0 * Random::random01() - 1,
			2.0 * Random::random01() - 1,
			0
		);
	} while (p.squaredLength() >= 1.0);
	return p;
}

Color Random::randomColor()
{
    return Color(
        Random::random01(),
        Random::random01(),
        Random::random01()
    );
}
