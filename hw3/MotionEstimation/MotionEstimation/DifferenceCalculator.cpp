#include "DifferenceCalculator.h"
#include <math.h>

DifferenceCalculator::DifferenceCalculator()
{
}

DifferenceCalculator::~DifferenceCalculator()
{
}

float DifferenceCalculator::CalculateMSE(Mat &A, Mat &B)
{
	float sum = 0;
	for (int i = 0; i < A.rows; i++)
	{
		for (int j = 0; j < A.cols; j++)
		{
			float Q = (float)(A.at<uchar>(i, j) - B.at<uchar>(i, j));
			sum += Q*Q;
		}
	}
	return sum / A.rows / A.cols;
}

float DifferenceCalculator::CalculatePSNR(Mat &A, Mat &B)
{
	return 10 * log10(255 * 255 / CalculateMSE(A, B));
}

Mat DifferenceCalculator::GetDifferenceImage(Mat &A, Mat &B)
{
	Mat result(Size(A.cols, A.rows), CV_8UC1);
	for (int i = 0; i < A.rows; i++)
	{
		for (int j = 0; j < A.cols; j++)
		{
			result.at<uchar>(i, j) = abs(A.at<uchar>(i, j) - B.at<uchar>(i, j));
		}
	}
	return result;
}