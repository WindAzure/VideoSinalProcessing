#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>

using namespace cv;
using namespace std;

const int WIDTH_DIMENSION = 4;
const int HEIGHT_DIMENSION = 4;

class Utility
{
private:

public:
	Utility();
	virtual ~Utility();
	float static CalculateMSE(Mat &mat1, Mat &mat2);
	void static CutBlocks(Mat &img, vector<Mat> &blockList);
};

#endif