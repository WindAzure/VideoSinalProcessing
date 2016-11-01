#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;

const int BLOCK_WIDTH = 16;
const int BLOCK_HEIGHT = 16;

enum EstimateType
{
	FullSearch,
	DiamondSearch
};

#endif