#include <stdio.h>
#include <time.h>
#include "MotionEstimator.h"
#include "DifferenceCalculator.h"

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

void Run(Mat reference, Mat target, EstimateType type)
{
	DifferenceCalculator differentCalculator;
	MontionEstimator estimator;

	float st = clock();
	Mat result = estimator.Estimate(reference, target, type);
	float ed = clock();
	differentCalculator.CalculatePSNR(result, target);
	Mat differenceImage=differentCalculator.GetDifferenceImage(result, target);

	imshow("motion estimation result.bmp", result);
	imshow("origin.bmp", target);
	imshow("difference.bmp", differenceImage);
	printf("cost=%fs\n", (ed - st)/CLOCKS_PER_SEC);
	waitKey();
}

int main()
{
	EstimateType type = EstimateType::DiamondSearch;
	Mat m0 = ReadFile("Images\\mobile0.Y");
	Mat m1 = ReadFile("Images\\mobile1.Y");
	Mat m2 = ReadFile("Images\\mobile2.Y");
	Run(m0, m1, type);
	//Run(m0, m2, type);
	return 0;
}