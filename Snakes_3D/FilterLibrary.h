#pragma once
#include "../../KDTree/KDTree/Eigen/Core"

#include <vector>
#include <memory>

typedef Eigen::Vector3f EVec3f;
typedef unsigned char byte;

using namespace std;

class FilterLibrary
{
public:
	FilterLibrary();
	~FilterLibrary();


	static unique_ptr<byte[]> gaussianFilter33  (const byte* img, int width, int height, int depth, float sigma);
	static unique_ptr<byte[]> laplacianFilter_6N(const byte* img, int width, int height, int depth);
	static unique_ptr<byte[]> sobelFilter_X33   (const byte* img, int width, int height, int depth);
	static unique_ptr<byte[]> sobelFilter_Y33   (const byte* img, int width, int height, int depth);
	static unique_ptr<byte[]> sobelFilter_Z33   (const byte* img, int width, int height, int depth);

private:
	static float convolution_33(const byte* img, float filter[][3][3], int x, int y, int z, int width, int height, int depth);


};

