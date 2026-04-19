#include "IntervalNParallel.h"

//Interval::Interval(Extended lX, Extended rX, std::vector<double> lY, std::vector<double> rY, double N): leftX(lX), rightX(rX), leftY(lY), rightY(rY)/*, N(N)*/
//{ 
//	//Extended subX = pow(rightX - leftX, 1.0 / N);
//	//double subZ = (testSequence[i].getZ() - testSequence[i - 1].getZ());
//	//double sumZ = (testSequence[i].getZ() + testSequence[i - 1].getZ());
//	//Extended interValueRt = subX + subZ * subZ / m / m / subX - 2 * (sumZ - 2 * bestGlobalMin) / m;
//}

Interval::Interval(DotN lDot, DotN rDot, Extended m, size_t N, double bestGlobalMin)
{
	leftX = lDot.getxExt();
	rightX = rDot.getxExt();
	leftY = lDot.getY();
	rightY = rDot.getY();
	leftZ = lDot.getZ();
	rightZ = rDot.getZ();

	Extended subX = pow(rightX - leftX, 1.0 / N);
	double subZ = rightZ - leftZ;
	double sumZ = rightZ + leftZ;
	valueRt = subX + subZ * subZ / m / m / subX - 2 * (sumZ - 2 * bestGlobalMin) / m;
	//valueRt = subX + subZ * subZ / m / m / subX - 2 * (sumZ) / m;
}