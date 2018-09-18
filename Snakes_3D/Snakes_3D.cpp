#include "Snakes_3D.h"

#define _USE_MATH_DEFINES
#include <math.h>

Snakes_3D::Snakes_3D()
{
}

Snakes_3D::Snakes_3D(const vector<EVec3f>& initCurve)
{
	contour_curve_.resize((int)initCurve.size());
#pragma omp parallel for
	for (int i=0; i < (int)initCurve.size(); ++i)
		contour_curve_[i] = initCurve[i];
}

Snakes_3D::~Snakes_3D()
{
}

void Snakes_3D::moveContour(const byte* img, int width, int height, int depth)
{
	if ( (int)contour_curve_.size() < 2 ) return ;

	unique_ptr<unsigned short[]> lapImg = laplacianFilter_6N(img, width, height, depth);



}

