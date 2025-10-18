#include <iostream>

#include"GlobalSearch.h"

bool compare(Dot& left, const Dot& right)
{
	return left < right;
}

void GlobalSearch::sortTestSequence() 
{
	sort(testSequence.begin(), testSequence.end(), compare);
}

double GlobalSearch::countingM(int t, double M)
{
	if (M == -numeric_limits<double>::infinity())
	{
		M = abs((testSequence[1].getZ() - testSequence[0].getZ()) / (testSequence[1] - testSequence[0]).getX());
	}
	else
	{
		double M1 = abs(testSequence.back().getZ() - testSequence[t - 1].getZ()) / (testSequence.back() - testSequence[t - 1]).getX();
		double M2 = abs(testSequence[t].getZ() - testSequence.back().getZ()) / (testSequence[t] - testSequence.back()).getX();
		if (M1 > M)
		{
			M = M1;
		}
		if (M2 > M)
		{
			M = M2;
		}
	}
	return M;
}

double GlobalSearch::countingm(double M)
{
	double m;
	if (M == 0)
	{
		m = 1;
	}
	else
	{
		m = coefR * M;
	}
	return m;
}

int GlobalSearch::countingt(double m)
{
	int t = 1;
	double valueRt = -numeric_limits<double>::infinity();
	for (int i = 1; i < testSequence.size(); i++)
	{
		double subX = (testSequence[i] - testSequence[i - 1]).getX();
		double subZ = (testSequence[i].getZ() - testSequence[i - 1].getZ());
		double sumZ = (testSequence[i].getZ() + testSequence[i - 1].getZ());
		double interValueRt = m * subX + subZ * subZ / m / subX - 2 * sumZ;
		if (interValueRt > valueRt)
		{
			valueRt = interValueRt;
			t = i;
		}
	}
	return t;
}

vector<double> GlobalSearch::startShekel()
{
	Dot x(a);
	x.pointTest(pointTestShekel(x));
	Dot y(b);
	y.pointTest(pointTestShekel(y));
	testSequence.push_back(x);
	testSequence.push_back(y);
	double t1 = time(NULL);
	int t = 1;
	double M = -numeric_limits<double>::infinity();
	int count = 0;
	do
	{
		count++;
		M = countingM(t, M);
		sortTestSequence();

		double m = countingm(M);
		t = countingt(m);
		Dot newElemSequence(0.5 * (testSequence[t] + testSequence[t - 1]).getX() - 0.5 / m * (testSequence[t].getZ() - testSequence[t - 1].getZ()));
		newElemSequence.pointTest(pointTestShekel(newElemSequence));
		testSequence.push_back(newElemSequence);
	} while (testSequence[t] - testSequence[t - 1] > 0.01);
	double t2 = time(NULL);
	double time = t2 - t1;
	vector<double> res;
	res.push_back(count);
	res.push_back(testSequence.back().getZ());
	res.push_back(time);
	return res;
}

vector<double> GlobalSearch::startHill()
{
		Dot x(a);
		x.pointTest(pointTestHill(x));
		Dot y(b);
		y.pointTest(pointTestHill(y));
		testSequence.push_back(x);
		testSequence.push_back(y);
		double t1 = time(NULL);
		int t = 1;
		double M = -numeric_limits<double>::infinity();
		int count = 0;
		do
		{
			count++;
			M = countingM(t, M);
			sortTestSequence();

			double m = countingm(M);
			t = countingt(m);
			Dot newElemSequence(0.5 * (testSequence[t] + testSequence[t - 1]).getX() - 0.5 / m * (testSequence[t].getZ() - testSequence[t - 1].getZ()));
			newElemSequence.pointTest(pointTestHill(newElemSequence));
			testSequence.push_back(newElemSequence);
		} while (testSequence[t] - testSequence[t - 1] > 0.01);
		double t2 = time(NULL);
		double time = t2 - t1;
		vector<double> res;
		res.push_back(count);
		res.push_back(testSequence.back().getZ());
		res.push_back(time);
		return res;
}
