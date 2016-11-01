#ifndef DIFFERENCE_CALCULATOR_H
#define DIFFERENCE_CALCULATOR_H

#include "Parameters.h"

class DifferenceCalculator
{
private:

public:
	DifferenceCalculator();
	virtual ~DifferenceCalculator();
	float CalculateMSE(Mat &A, Mat &B);
	float CalculatePSNR(Mat &A,Mat &B);
	Mat GetDifferenceImage(Mat &A, Mat &B);
};

#endif