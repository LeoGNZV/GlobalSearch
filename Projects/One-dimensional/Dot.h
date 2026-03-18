#include <iostream>

class Dot
{
	double x;
	double z;

	Dot() {}
public:
	Dot(double x_) : x(x_) {}
	Dot(double x_, double z_) : x(x_), z(z_) {}

	double getX()
	{
		return x;
	}
	double getZ()
	{
		return z;
	}

	void pointTest(double d);

	Dot operator+(const Dot& d);

	Dot operator-(const Dot& d);

	bool operator>(const double d);

	bool operator>=(const double d);

	bool operator<(const Dot& d);

	double operator/(double d);
};