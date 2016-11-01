#ifndef MONTION_ESTIMATOR_H
#define MONTION_ESTIMATOR_H

#include "Parameters.h"

class MontionEstimator
{
private:

public:
	MontionEstimator();
	virtual ~MontionEstimator();
	Mat Estimate(Mat reference, Mat target, EstimateType type=EstimateType::FullSearch,int searchRegionMin=-7,int searchRegionMax=7);
};

#endif