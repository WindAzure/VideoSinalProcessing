#include <stdio.h>
#include "MotionEstimator.h"

Mat ReadFile(string fileName)
{
	char data;
	int len = 0;
	Mat result(Size(720, 480), CV_8UC1);
	FILE *file = fopen(fileName.c_str(), "rb");
	while ((data = fgetc(file)) != EOF)
	{
		result.data[len++] = (unsigned)data;
	}
	fclose(file);
	return result;
}

int main()
{
	Mat m0 = ReadFile("Images\\mobile0.Y");
	Mat m1 = ReadFile("Images\\mobile1.Y");
	Mat m2 = ReadFile("Images\\mobile2.Y");

	MontionEstimator estimator;
	Mat result1 = estimator.Estimate(m0, m1, EstimateType::FullSearch);
	//Mat result2 = estimator.Estimate(m0, m2);
	imshow("result1.bmp", result1);
	imshow("origin1.bmp", m1);
	//imshow("result2.bmp", result2);
	//imshow("origin2.bmp", m2);
	waitKey();
	return 0;
}