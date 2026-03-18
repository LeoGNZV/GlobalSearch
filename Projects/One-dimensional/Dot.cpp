#include <iostream>
#include "Dot.h"

void Dot::pointTest(double d)
{
	z = d;
}

Dot Dot::operator+(const Dot& d)
{
	Dot res;
	res.x = d.x + x;
	return res;
}

Dot Dot::operator-(const Dot& d)
{
	Dot res;
	res.x = x - d.x;
	return res;
}

bool Dot::operator>(const double d)
{
	if (x > d)
	{
		return true;
	}
	return false;
}

bool Dot::operator>=(const double d)
{
	if (x >= d)
	{
		return true;
	}
	return false;
}

bool Dot::operator<(const Dot& d)
{
	if (x < d.x)
	{
		return true;
	}
	return false;
}

double Dot::operator/(double d)
{
	return x / d;
}
