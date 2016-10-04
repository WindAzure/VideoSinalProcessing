#include "Utility.h"

Utility::Utility()
{
}

Utility::~Utility()
{
}

float Utility::CalculateMSE(Mat &mat1, Mat &mat2)
{
	float sum = 0;
	for (int i = 0; i < mat1.rows; i++)
	{
		for (int j = 0; j < mat1.cols; j++)
		{
			int Q = mat1.at<uchar>(i, j) - mat2.at<uchar>(i, j);
			sum += Q*Q;
		}
	}
	return sum;
}

void Utility::CutBlocks(Mat &img, vector<Mat> &blockList)
{
	for (int i = 0; i < img.rows; i += HEIGHT_DIMENSION)
	{
		for (int j = 0; j < img.cols; j += WIDTH_DIMENSION)
		{
			Mat block(img, Rect(j, i, WIDTH_DIMENSION, HEIGHT_DIMENSION));
			blockList.push_back(block.clone());
		}
	}
}