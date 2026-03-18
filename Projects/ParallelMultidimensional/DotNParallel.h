#include <iostream>
#include <vector>
#include <Evolvent.h>

using std::vector;

class DotN
{
	vector<double> y;
	Extended xExt;
	double z;

	DotN() {}
public:
	DotN(vector<double> x_, double* a, double* b);

	DotN(Extended x_, double* a, double* b, size_t N);

	DotN(Extended x_, double* a, double* b, size_t N, double z_);

	DotN(const vector<double>& y_, Extended x_, double z);

	vector<double> getY()
	{
		return y;
	}

	double getZ()
	{
		return z;
	}

	Extended getxExt()
	{
		return xExt;
	}

	DotN& operator=(const DotN& d);

	void pointTest(double d);

	/*DotN operator+(const DotN& d);

	DotN operator-(const DotN& d);

	bool operator>(const double d);

	bool operator>=(const double d);

	bool operator<(const DotN& d);

	double operator/(double d);*/
};