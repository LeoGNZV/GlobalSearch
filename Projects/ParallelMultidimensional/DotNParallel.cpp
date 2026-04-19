#include <iostream>
#include "DotNParallel.h"

void DotN::pointTest(double d)
{
	z = d;
}

DotN::DotN(vector<double> x_, double* a, double* b) : y(x_)
{
	Evolvent h(y.size(), 10);
	h.SetBounds(a, b);
	double* yNewFormat = new double[y.size()];
	for (int i = 0; i < y.size(); i++)
		yNewFormat[i] = y[i];
	h.GetInverseImage(yNewFormat, xExt);
	delete[] yNewFormat;
}

DotN::DotN(Extended x_, double* a, double* b, size_t N) : xExt(x_)
{
	Evolvent h(N, 10);
	h.SetBounds(a, b);
	double* yNewFormat = new double[N];
	h.GetImage(xExt, yNewFormat);
	for (int i = 0; i < N; i++)
		y.push_back(yNewFormat[i]);
	delete[] yNewFormat;
}

DotN::DotN(Extended x_, double* a, double* b, size_t N, double z_) : xExt(x_), z(z_)
{
	Evolvent h(N, 10);
	h.SetBounds(a, b);
	double* yNewFormat = new double[N];
	h.GetImage(xExt, yNewFormat);
	for (int i = 0; i < N; i++)
		y.push_back(yNewFormat[i]);
	delete[] yNewFormat;
}

DotN& DotN::operator=(const DotN& d)
{
	if (&d != this)
	{
		y = d.y;
		xExt = d.xExt;
		z = d.z;
	}
	return *this;
}

DotN::DotN(const vector<double>& y_, Extended x_, double z_) : y(y_), xExt(x_), z(z_) {}

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
