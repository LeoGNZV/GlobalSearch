#include <iostream>

#include"GlobalSearchM.h"

bool compare(DotN& left, DotN& right)
{
	return left.getxExt() < right.getxExt();
}

void GlobalSearchM::sortTestSequence()
{
	sort(testSequence.begin(), testSequence.end(), compare);
}

Extended GlobalSearchM::countingM(int t, Extended M)
{
	//for (int i = 1; i < testSequence.size(); i++)
	//{
	//	Extended M1 = fabs(testSequence[i].getZ() - testSequence[i-1].getZ()) / pow((testSequence[i].getxExt() - testSequence[i-1].getxExt()), 1 / N);
	//	if (M1 > M)
	//		M = M1;
	//}
	if (M == -numeric_limits<double>::infinity())
	{
		M = fabs(testSequence[1].getZ() - testSequence[0].getZ()) / pow((testSequence[1].getxExt() - testSequence[0].getxExt()), 1/N);
	}
	else
	{
		Extended M1 = fabs(testSequence.back().getZ() - testSequence[t - 1].getZ()) / pow((testSequence.back().getxExt() - testSequence[t - 1].getxExt()), 1 / N);
		Extended M2 = fabs(testSequence[t].getZ() - testSequence.back().getZ()) / pow(fabs(testSequence[t].getxExt() - testSequence.back().getxExt()), 1 / N);
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

Extended GlobalSearchM::countingm(Extended M)
{
	Extended m;
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

int GlobalSearchM::countingt(Extended m)
{
	int t = 1;
	/*Extended subX = pow(testSequence[1].getxExt() - testSequence[0].getxExt(), 1 / N);
	Extended valueRt = 2 * subX - 4 / m * testSequence[1].getZ();*/
	Extended valueRt = -numeric_limits<double>::infinity();
	for (int i = 1; i < testSequence.size(); i++)
	{
		Extended subX = pow(testSequence[i].getxExt() - testSequence[i - 1].getxExt(), 1/N);
		double subZ = (testSequence[i].getZ() - testSequence[i - 1].getZ());
		double sumZ = (testSequence[i].getZ() + testSequence[i - 1].getZ());
		Extended interValueRt = subX + subZ * subZ / m / m / subX - 2 * sumZ / m;
		if (interValueRt > valueRt)
		{
			valueRt = interValueRt;
			t = i;
		}
	}
	//if (valueRt < 2 * pow(testSequence.back().getxExt() - testSequence[testSequence.size() - 1].getxExt(), 1 / N) - 4 / m * testSequence.back().getZ())
	//	return testSequence.size();
	return t;
}

template<typename Func>
vector<double> GlobalSearchM::start(Func valueCountFunc)
{
	vector<double> x1, x2;
	for (int i = 0; i < N; i++)
	{
		x1.push_back(a[i]);
		x2.push_back(b[i]);
	}
	DotN x(x1, a, b);
	x.pointTest(valueCountFunc(x));
	DotN y(x2, a, b);
	y.pointTest(valueCountFunc(y));
	testSequence.push_back(x);
	testSequence.push_back(y);
	double t1 = time(NULL);
	int t = 1;
	Extended M = -numeric_limits<double>::infinity();
	int count = 0;
	DotN bestGlobalMin(0.0, a, b, N, numeric_limits<double>::infinity());
	do
	{
		count++;
		//sortTestSequence();
		M = countingM(t, M);
		sortTestSequence();

		Extended m = countingm(M);
		t = countingt(m);
		Extended nEl;
		if (count == 1)
			nEl = 0.5 * (testSequence[t].getxExt() + testSequence[t - 1].getxExt());
		else
			nEl = 0.5 * (testSequence[t].getxExt() + testSequence[t - 1].getxExt()) 
			- 0.5 / coefR * sgn(testSequence[t].getZ() - testSequence[t - 1].getZ()) * pow(abs(testSequence[t].getZ() - testSequence[t - 1].getZ()) / M, N);
		DotN newElemSequence(nEl, a, b, N);
		newElemSequence.pointTest(valueCountFunc(newElemSequence));
		if (newElemSequence.getZ() < bestGlobalMin.getZ())
			bestGlobalMin = newElemSequence;
		testSequence.push_back(newElemSequence);
	} while (pow(testSequence[t].getxExt() - testSequence[t - 1].getxExt(), 1/N) > 0.01);
	double t2 = time(NULL);
	double time = t2 - t1;
	vector<double> res;
	res.push_back(count);
	res.push_back(bestGlobalMin.getZ());
	res.push_back(time);
	res.push_back(bestGlobalMin.getY()[0]);
	res.push_back(bestGlobalMin.getY()[1]);
	return res;
}

vector<double> GlobalSearchM::startShekel()
{
	vector<double> answer = start([=](DotN d) { return shekelFam[index]->ComputeFunction({ d.getY() }); });
	return answer;
}

vector<double> GlobalSearchM::startHill()
{
	vector<double> answer = start([=](DotN d) { return hillFam[index]->ComputeFunction({ d.getY() }); });
	return answer;
}
vector<double> GlobalSearchM::startGrishagin()
{
	vector<double> answer = start([=](DotN d) { return grishaginFam[index]->ComputeFunction({ d.getY() }); });
	return answer;
}
//vector<double> GlobalSearchM::startShekel()
//{
//	vector<double> x1, x2;
//	for (int i = 0; i < N; i++)
//	{
//		x1.push_back(a[i]);
//		x2.push_back(b[i]);
//	}
//	DotN x(x1, a, b);
//	x.pointTest(pointTestShekel(x));
//	DotN y(x2, a, b);
//	y.pointTest(pointTestShekel(y));
//	testSequence.push_back(x);
//	testSequence.push_back(y);
//	double t1 = time(NULL);
//	int t = 1;
//	Extended M = -numeric_limits<double>::infinity();
//	int count = 0;
//	do
//	{
//		count++;
//		//sortTestSequence();
//		M = countingM(t, M);
//		sortTestSequence();
//
//		Extended m = countingm(M);
//		t = countingt(m);
//		Extended nEl;
//		//if (t == 1 || t == testSequence.size())
//		//	nEl = 0.5 * (testSequence[t].getxExt() + testSequence[t - 1].getxExt());
//		//else
//		nEl = 0.5 * (testSequence[t].getxExt() + testSequence[t - 1].getxExt()) 
//			- 0.5 / coefR * sgn(testSequence[t].getZ() - testSequence[t - 1].getZ()) * pow(abs(testSequence[t].getZ() - testSequence[t - 1].getZ()) / M, N);
//		DotN newElemSequence(nEl, a, b, N);
//		newElemSequence.pointTest(pointTestShekel(newElemSequence));
//		testSequence.push_back(newElemSequence);
//	} while (pow(testSequence[t].getxExt() - testSequence[t - 1].getxExt(), 1/N) > 0.01);
//	double t2 = time(NULL);
//	double time = t2 - t1;
//	vector<double> res;
//	res.push_back(count);
//	res.push_back(testSequence.back().getZ());
//	res.push_back(time);
//	return res;
//}
//
//vector<double> GlobalSearchM::startHill()
//{
//	vector<double> x1, x2;
//	for (int i = 0; i < N; i++)
//	{
//		x1.push_back(a[i]);
//		x2.push_back(b[i]);
//	}
//	DotN x(x1, a, b);
//	x.pointTest(pointTestHill(x));
//	DotN y(x2, a, b);
//	y.pointTest(pointTestHill(y));
//	testSequence.push_back(x);
//	testSequence.push_back(y);
//	double t1 = time(NULL);
//	int t = 1;
//	Extended M = -numeric_limits<double>::infinity();
//	int count = 0;
//	do
//	{
//		count++;
//		//sortTestSequence();
//		M = countingM(t, M);
//		sortTestSequence();
//
//		Extended m = countingm(M);
//		t = countingt(m);
//		Extended nEl;
//		if (t == 1 || t == testSequence.size())
//			nEl = 0.5 * (testSequence[t].getxExt() + testSequence[t - 1].getxExt());
//		else
//			nEl = 0.5 * (testSequence[t].getxExt() + testSequence[t - 1].getxExt())
//			- 0.5 / coefR * sgn(testSequence[t].getZ() - testSequence[t - 1].getZ()) * pow(abs(testSequence[t].getZ() - testSequence[t - 1].getZ()) / M, N);
//		DotN newElemSequence(nEl, a, b, N);
//		newElemSequence.pointTest(pointTestHill(newElemSequence));
//		testSequence.push_back(newElemSequence);
//	} while (pow(testSequence[t].getxExt() - testSequence[t - 1].getxExt(), 1 / N) > 0.01);
//	double t2 = time(NULL);
//	double time = t2 - t1;
//	vector<double> res;
//	res.push_back(count);
//	res.push_back(testSequence.back().getZ());
//	res.push_back(time);
//	return res;
//}
//
//vector<double> GlobalSearchM::startGrishagin()
//{
//	vector<double> x1, x2;
//	for (int i = 0; i < N; i++)
//	{
//		x1.push_back(a[i]);
//		x2.push_back(b[i]);
//	}
//	DotN x(x1, a, b);
//	x.pointTest(pointTestGrishagin(x));
//	DotN y(x2, a, b);
//	y.pointTest(pointTestGrishagin(y));
//	testSequence.push_back(x);
//	testSequence.push_back(y);
//	double t1 = time(NULL);
//	int t = 1;
//	Extended M = -numeric_limits<double>::infinity();
//	int count = 0;
//	do
//	{
//		count++;
//		//sortTestSequence();
//		M = countingM(t, M);
//		sortTestSequence();
//
//		Extended m = countingm(M);
//		t = countingt(m);
//		Extended nEl;
//		if (t == 1 || t == testSequence.size())
//			nEl = 0.5 * (testSequence[t].getxExt() + testSequence[t - 1].getxExt());
//		else
//			nEl = 0.5 * (testSequence[t].getxExt() + testSequence[t - 1].getxExt())
//			- 0.5 / coefR * sgn(testSequence[t].getZ() - testSequence[t - 1].getZ()) * pow(abs(testSequence[t].getZ() - testSequence[t - 1].getZ()) / M, N);
//		DotN newElemSequence(nEl, a, b, N);
//		newElemSequence.pointTest(pointTestGrishagin(newElemSequence));
//		testSequence.push_back(newElemSequence);
//	} while (pow(testSequence[t].getxExt() - testSequence[t - 1].getxExt(), 1 / N) > 0.01);
//	double t2 = time(NULL);
//	double time = t2 - t1;
//	vector<double> res;
//	res.push_back(count);
//	res.push_back(testSequence.back().getZ());
//	res.push_back(time);
//	return res;
//}
