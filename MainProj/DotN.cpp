#include <iostream>
#include "DotN.h"

void DotN::pointTest(double d)
{
	z = d;
}

//DotN DotN::operator+(const DotN& d)
//{
//	DotN res;
//	for (int i = 0; i < y.size(); i++)
//		res.y[i] = d.y[i] + y[i];
//	return res;
//}
//
//DotN DotN::operator-(const DotN& d)
//{
//	DotN res;
//	for (int i = 0; i < x.size(); i++)
//		res.x[i] = x[i] - d.x[i];
//	return res;
//}

//bool Dot::operator>(const double d)
//{
//	if (x > d)
//	{
//		return true;
//	}
//	return false;
//}
//
//bool Dot::operator>=(const double d)
//{
//	if (x >= d)
//	{
//		return true;
//	}
//	return false;
//}
//
//bool Dot::operator<(const Dot& d)
//{
//	if (x < d.x)
//	{
//		return true;
//	}
//	return false;
//}
//
//double Dot::operator/(double d)
//{
//	return x / d;
//}
