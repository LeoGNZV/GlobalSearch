#include <iostream>
#include <algorithm>
#include <cmath>
//#include <functional>
#include "DotNParallel.h"

class Interval
{
	Extended leftX;
	Extended rightX;
	std::vector<double> leftY;
	std::vector<double> rightY;
	double leftZ;
	double rightZ;
	Extended valueRt;
public:
	//Interval(Extended lX, Extended rX, std::vector<double> lY, std::vector<double> rY, Extended vRt): leftX(lX), rightX(rX), leftY(lY), rightY(rY) {}
	//Interval(Extended lX, Extended rX, std::vector<double> lY, std::vector<double> rY, double N);

	template<typename Func>
	Interval(Extended lX, Extended rX, double* a, double* b, size_t N, Func function, double bestGlobalMin = 1000000000, Extended m = 1.0) : leftX(lX), rightX(rX)
	{
		// отображаем Extended точки в их многомерное представление
		Evolvent h(N, 10);
		h.SetBounds(a, b);
		leftY.resize(N);
		h.GetImage(lX, leftY.data());
		rightY.resize(N);
		h.GetImage(rX, rightY.data());

		// проводим испытания в точках
		leftZ = function(leftY);
		rightZ = function(rightY);

		bestGlobalMin = std::min({ leftZ, rightZ, bestGlobalMin });
		Extended subX = pow(rightX - leftX, 1.0 / N);
		double subZ = rightZ - leftZ;
		double sumZ = rightZ + leftZ;
		valueRt = subX + subZ * subZ / m / m / subX - 2 * (sumZ - 2 * bestGlobalMin) / m;
		//valueRt = subX + subZ * subZ / m / m / subX - 2 * (sumZ) / m;
	}


	Interval(DotN lDot, DotN rDot, Extended m, size_t N, double bestGlobalMin);

	Interval() : leftX(0.0), rightX(1.0) { }

	void recountInterval(Extended m, double bestGlobalMin, size_t N)
	{
		Extended subX = pow(rightX - leftX, 1.0 / N);
		double subZ = rightZ - leftZ;
		double sumZ = rightZ + leftZ;
		valueRt = subX + subZ * subZ / m / m / subX - 2 * (sumZ - 2 * bestGlobalMin) / m;
		//valueRt = subX + subZ * subZ / m / m / subX - 2 * (sumZ) / m;
	}

	Extended getValueRt() { return valueRt; }
	DotN getLeftDot() const { return DotN(leftY, leftX, leftZ); }
	DotN getRightDot() const { return DotN(rightY, rightX, rightZ); }
	double getLeftZ() const { return leftZ; }
	double getRightZ() const { return rightZ; }
	Extended getLeftX() const { return leftX; }
	Extended getRightX() const { return rightX; }
};