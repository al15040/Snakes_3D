#pragma once
#include "../../KDTree/KDTree/Eigen/Core"

#include <vector>
#include <memory>

typedef Eigen::Vector3f EVec3f;
typedef unsigned char byte;

using namespace std;

class Snakes_3D
{
	vector<EVec3f> contour_curve_;

public:
	Snakes_3D();
	Snakes_3D(const vector<EVec3f>& initCurve);

	~Snakes_3D();

	void moveContour(const byte* img, int width, int height, int depth);


	const vector<EVec3f>& getCurve()
	{
		return contour_curve_;
	}

private:
	float lossFunction();
	unique_ptr<unsigned short[]> laplacianFilter_6N(const byte* img, int width, int height, int depth);
};

