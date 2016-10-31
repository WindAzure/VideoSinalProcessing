#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

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
	imshow("m0.bmp", m0);
	imshow("m1.bmp", m1);
	imshow("m2.bmp", m2);
	waitKey();
	return 0;
}