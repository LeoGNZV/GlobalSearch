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
	DotN(vector<double> x_, double* a, double* b) : y(x_) 
	{
		Evolvent h(y.size(), 10);
		h.SetBounds(a, b);
		double* yNewFormat = new double[y.size()];
		for (int i = 0; i < y.size(); i++)
			yNewFormat[i] = y[i];
		h.GetInverseImage(yNewFormat, xExt);
		delete yNewFormat;
	}

	DotN(Extended x_, double* a, double* b, size_t N) : xExt(x_)
	{
		Evolvent h(N, 10);
		h.SetBounds(a, b);
		double* yNewFormat = new double[N];
		h.GetImage(xExt, yNewFormat);
		for (int i = 0; i < N; i++)
			y.push_back(yNewFormat[i]);
		delete yNewFormat;
	}

	DotN(Extended x_, double* a, double* b, size_t N, double z_) : xExt(x_), z(z_)
	{
		Evolvent h(N, 10);
		h.SetBounds(a, b);
		double* yNewFormat = new double[N];
		h.GetImage(xExt, yNewFormat);
		for (int i = 0; i < N; i++)
			y.push_back(yNewFormat[i]);
		delete yNewFormat;
	}

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

	DotN& operator=(const DotN& d)
	{
		if (&d != this)
		{
			y = d.y;
			xExt = d.xExt;
			z = d.z;
		}
		return *this;
	}

	void pointTest(double d);

	/*DotN operator+(const DotN& d);

	DotN operator-(const DotN& d);

	bool operator>(const double d);

	bool operator>=(const double d);

	bool operator<(const DotN& d);

	double operator/(double d);*/
};