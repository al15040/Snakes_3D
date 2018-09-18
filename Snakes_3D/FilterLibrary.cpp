#include "FilterLibrary.h"

#define _USE_MATH_DEFINES
#include <math.h>

FilterLibrary::FilterLibrary()
{
}


FilterLibrary::~FilterLibrary()
{
}



float FilterLibrary::convolution_33(const byte* img, float filter[][3][3], int x, int y, int z, int width, int height, int depth)
{
	float result = 0;
	for (int i = x - 1; i <= x + 1; ++i) if (i >= 0 && i < width)
		for (int j = y - 1; j <= y + 1; ++j) if (j >= 0 && j < height)
			for (int k = z - 1; k <= z + 1; ++k) if (k >= 0 && k < depth)
				result += img[i + j * width + k * width*height] * filter[i + 1 - x][j + 1 - y][k + 1 - z];

	unsigned short resultAbs = abs(result);
	return resultAbs;
}



unique_ptr<byte[]> FilterLibrary::laplacianFilter_6N(const byte* img, int width, int height, int depth)
{
	float filter[3][3][3] = { 0 };//xyz
	filter[1][1][1] = -6;
	filter[0][1][1] =
		filter[2][1][1] =
		filter[1][0][1] =
		filter[1][2][1] =
		filter[1][1][0] =
		filter[1][1][2] = 1;

	unique_ptr<byte[]> lapImg(new byte[width*height*depth]);

#pragma omp parallel for
	for (int x = 0; x < width ; ++x)
#pragma omp parallel for
	for (int y = 0; y < height; ++y)
	for (int z = 0; z < depth ; ++z)
	{ 
		float value = convolution_33(img, filter, x, y, z, width, height, depth);
		lapImg[x + y * width + z * width * height] = 
			(value > 255) ? 255 : (value < 0) ? 0 : (byte)(value+0.5);
	}
	return move(lapImg);
}


static float gaussian(float sigma, int x, int y, int z)
{
	return expf( -(x*x + y * y + z * z) / (2 * sigma*sigma) ) / ( sqrt(2*M_PI) * sigma );
}

unique_ptr<byte[]> FilterLibrary::gaussianFilter33(const byte* img, int width, int height, int depth, float sigma)
{
	float filter[3][3][3] = { 0 };

	for (int x = 0; x < 3; ++x)
	for (int y = 0; y < 3; ++y)
	for (int z = 0; z < 3; ++z)
		filter[x][y][z] = gaussian(sigma, x - 1, y - 1, z - 1);

	unique_ptr<byte[]> blurImg(new byte[width*height*depth]);

#pragma omp parallel for
	for (int x = 0; x < width; ++x)
#pragma omp parallel for
	for (int y = 0; y < height; ++y)
	for (int z = 0; z < depth; ++z)
	{
		float value = convolution_33(img, filter, x, y, z, width, height, depth);
		blurImg[x + y * width + z * width * height] =
			(value > 255) ? 255 : (value < 0) ? 0 : (byte)(value + 0.5);
	}
	return move(blurImg);
}



unique_ptr<byte[]> FilterLibrary::sobelFilter_X33(const byte* img, int width, int height, int depth)
{
	float filter[3][3][3] = { 0 };
	filter[0][0][1] = filter[0][2][1] = -1;
	filter[0][1][1] = -2;
	filter[2][0][1] = filter[2][2][1] = 1;
	filter[2][1][1] = 2;

	unique_ptr<byte[]> sobelImg(new byte[width*height*depth]);

#pragma omp parallel for
	for (int x = 0; x < width ; ++x)
#pragma omp parallel for
	for (int y = 0; y < height; ++y)
	for (int z = 0; z < depth ; ++z)
	{
		float value = convolution_33(img, filter, x, y, z, width, height, depth);
		sobelImg[x + y * width + z * width * height] =
				(value > 255) ? 255 : (value < 0) ? 0 : (byte)(value + 0.5);
	}
	return move(sobelImg);
}

unique_ptr<byte[]> FilterLibrary::sobelFilter_Y33(const byte* img, int width, int height, int depth)
{


}

unique_ptr<byte[]> FilterLibrary::sobelFilter_Z33(const byte* img, int width, int height, int depth)
{

}