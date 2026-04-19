#include "mpi.h"
#include <iostream>

#include"GlobalSearchMParallel.h"

bool compare(DotN& left, DotN& right)
{
	return left.getxExt() < right.getxExt();
}

//GlobalSearchM::GlobalSearchM(size_t n, double r, int i) : N(n), coefR(r), index(i), GKLSFam(N, Simple), GKLSFamHard(N, Hard)
//{
//	TGKLSProblemFamily GKLSFamTemp(N, Simple);
//	TGKLSProblemFamily GKLSFamHardTemp(N, Hard);
//
//	GKLSFam = GKLSFamTemp;
//	GKLSFamHard = GKLSFamHardTemp;
//}

void GlobalSearchM::sortTestSequence()
{
	sort(testSequence.begin(), testSequence.end(), compare);
}

//Extended GlobalSearchM::countingM(Extended M)
//{
//	for (int i = 1; i < testSequence.size(); i++)
//	{
//		if (abs((testSequence[i].getZ() - testSequence[i - 1].getZ())) / (testSequence[i].getxExt() - testSequence[i - 1].getxExt()) > M)
//		{
//			M = abs((testSequence[i].getZ() - testSequence[i - 1].getZ())) / (testSequence[i].getxExt() - testSequence[i - 1].getxExt());
//		}
//	}
//	return M;
//}

Extended GlobalSearchM::countingMfrommaxt(vector<int> t, Extended M, int p)
{
	if (t[0] == -1 || M == -numeric_limits<double>::infinity())
	{
		for (int i = 1; i < testSequence.size(); i++)
		{
			Extended M1 = fabs(testSequence[i].getZ() - testSequence[i - 1].getZ()) / pow((testSequence[i].getxExt() - testSequence[i - 1].getxExt()), 1 / N);
			if (M1 > M)
				M = M1;
		}
	}
	else
	{
		for (int i = 0; i < p; i++)
		{
			int sequenceSize = testSequence.size();
			Extended sl1 = fabs(testSequence[sequenceSize - p + i].getZ() - testSequence[t[i] - 1].getZ());
			Extended sl2 = pow((testSequence[sequenceSize - p + i].getxExt() - testSequence[t[i] - 1].getxExt()), 1 / N);

			Extended M1 = sl1 / sl2;
			Extended M2 = fabs(testSequence[t[i]].getZ() - testSequence[sequenceSize - p + i].getZ()) / pow(fabs(testSequence[t[i]].getxExt() - testSequence[sequenceSize - p + i].getxExt()), 1 / N);
			if (M1 > M)
			{
				M = M1;
			}
			if (M2 > M)
			{
				M = M2;
			}
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
	return t;
}

vector<int> GlobalSearchM::countingtParallel(Extended m, int p, double bestGlobalMin)
{
	vector<Extended> valueRt(p, -numeric_limits<double>::infinity());
	vector<int> t(p, 0);
	Extended minValueRt = -numeric_limits<double>::infinity();
	int minIndex = 0;

	for (int i = 1; i < testSequence.size(); i++)
	{
		Extended subX = pow(testSequence[i].getxExt() - testSequence[i - 1].getxExt(), 1 / N);
		double subZ = (testSequence[i].getZ() - testSequence[i - 1].getZ());
		double sumZ = (testSequence[i].getZ() + testSequence[i - 1].getZ());
		Extended interValueRt = subX + subZ * subZ / m / m / subX - 2 * (sumZ - 2 * bestGlobalMin) / m;
		//Extended interValueRt = subX + subZ * subZ / m / m / subX - 2 * sumZ / m;

		// если новая характеристика интервала становится больше, 
		// чем минимальное значение из массива максимальных характеристик,
		// то новая характеристика заменяет старую
		if (interValueRt > minValueRt) 
		{
			valueRt[minIndex] = interValueRt;
			t[minIndex] = i;

			// выбор новой минимальной характеристики из максимальных
			minValueRt = valueRt[0];
			minIndex = 0;
			for (int j = 1; j < p; j++)
			{
				if (valueRt[j] < minValueRt)
				{
					minValueRt = valueRt[j];
					minIndex = j;
				}
			}
		}
	}
	return t;
}

template<typename Func>
vector<double> GlobalSearchM::start(Func valueCountFunc, vector<double> a_ , vector<double> b_)
{
	double* a = new double[N];
	double* b = new double[N];
	for (int j = 0; j < a_.size(); j++)
	{
		a[j] = a_[j];
	}
	for (int j = 0; j < b_.size(); j++)
	{
		b[j] = b_[j];
	}

	Extended x1 = 0.0, x2 = 1.0;
	DotN x(x1, a, b, N);
	x.pointTest(valueCountFunc(x.getY()));
	DotN y(x2, a, b, N);
	y.pointTest(valueCountFunc(y.getY()));
	testSequence.push_back(x);
	testSequence.push_back(y);

	int count = 0;
	DotN bestGlobalMin(0.0, a, b, N, numeric_limits<double>::infinity());
	bestGlobalMin = testSequence[0];
	if (testSequence[1].getZ() < bestGlobalMin.getZ())
		bestGlobalMin = testSequence[1];
	int procNum = 0;
	int procRank = 0;
	MPI_Comm_size(MPI_COMM_WORLD, &procNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
	
	auto t1 = std::chrono::steady_clock::now();
	// формируем новые точки с шагом step, чтобы количество интварвалов стало равно procNum
	Extended step = (y.getxExt() - x.getxExt()) / (procNum);
	for (int i = 1; i < procNum; i++)
	{
		Extended nEl = x.getxExt() + i * step;
		DotN newElemSequence(nEl, a, b, N);
		newElemSequence.pointTest(valueCountFunc(newElemSequence.getY()));
		if (newElemSequence.getZ() < bestGlobalMin.getZ())
			bestGlobalMin = newElemSequence;
		testSequence.push_back(newElemSequence);
	}

	sortTestSequence();
	Extended M = -numeric_limits<double>::infinity();

	bool continue_iteration = true;
	vector<int> tmax(procNum, -1);
	double m;

	do
	{
		vector<double> bufferSend; // буффер, в который на корневом процессе загружаются точки N-мерного пространства
		vector<double> bufferReceiving(N, 0.0); // буффер, содержащий точки N-мерного пространства, для которых нужно вычислить новую точку

		vector<Extended> newElementsExtended;
		vector<vector<double>> newElementsY;
		vector<double> newElementsZ;

		newElementsZ.resize(procNum);

		count++;
		M = countingMfrommaxt(tmax, M, procNum);
		sortTestSequence();
		Extended m = countingm(M);

		tmax = countingtParallel(m, procNum, bestGlobalMin.getZ());


		// формируем newElementsExtended
		for (int k = 0; k < procNum; k++)
		{
			Extended nEl;
			if ((tmax[k] == 1) || (tmax[k] == testSequence.size() - 1))
				nEl = 0.5 * (testSequence[tmax[k]].getxExt() + testSequence[tmax[k] - 1].getxExt());
			else
				nEl = 0.5 * (testSequence[tmax[k]].getxExt() + testSequence[tmax[k] - 1].getxExt())
				- 0.5 / coefR * sgn(testSequence[tmax[k]].getZ() - testSequence[tmax[k] - 1].getZ()) * pow(abs(testSequence[tmax[k]].getZ() - testSequence[tmax[k] - 1].getZ()) / M, N);
			newElementsExtended.push_back(nEl);
		}

		for (int k = 0; k < procNum; k++)
		{
			vector<double> newY;

			// формируем newElementsY
			Evolvent h(N, 10);
			h.SetBounds(a, b);
			double* yNewFormat = new double[N];
			h.GetImage(newElementsExtended[k], yNewFormat);
			for (int l = 0; l < N; l++)
			{
				newY.push_back(yNewFormat[l]);
				bufferSend.push_back(yNewFormat[l]); // собираем координаты точек в N-мерном пространстве, в которых нужно провести испытание, в один буффер
			}
			delete yNewFormat;
			newElementsY.push_back(newY);
		}

		MPI_Scatter((procRank == 0) ? bufferSend.data() : nullptr, N, MPI_DOUBLE, bufferReceiving.data(), N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		double z = valueCountFunc(bufferReceiving);
		
		MPI_Gather(&z, 1, MPI_DOUBLE, newElementsZ.data(), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		bool provisional_continue_iteratiom = true;
		for (int k = 0; k < procNum; k++)
		{
			vector<double> yCopy = newElementsY[k];  // явная копия
			Extended xCopy = newElementsExtended[k]; // явная копия
			double zCopy = newElementsZ[k];          // копия

			DotN newElemSequence(yCopy, xCopy, zCopy);

			//DotN newElemSequence(newElementsY[k], newElementsExtended[k], newElementsZ[k]);
			//newElemSequence.pointTest(valueCountFunc(newElemSequence.getY()));
			if (newElemSequence.getZ() < bestGlobalMin.getZ())
				bestGlobalMin = newElemSequence;
			testSequence.push_back(newElemSequence);
			//for (int l = 0; l < N; l++)
			//{
			//	if (pow(abs(testSequence[tmax[k]].getY()[l] - testSequence[tmax[k] - 1].getY()[l]), 1 / N) < 0.01)
			//		provisional_continue_iteratiom = false;
			//	else
			//	{
			//		provisional_continue_iteratiom = true;
			//		break;
			//	}
			//}
			if (pow(testSequence[tmax[k]].getxExt() - testSequence[tmax[k] - 1].getxExt(), 1 / N) < 0.01)
				provisional_continue_iteratiom = false;
		}
		continue_iteration = provisional_continue_iteratiom;

		MPI_Bcast(&continue_iteration, 1, MPI_C_BOOL, 0, MPI_COMM_WORLD);
	} while (continue_iteration);

	auto t2 = std::chrono::steady_clock::now();
	double time = (t2 - t1).count();

	delete[] a;
	delete[] b;

	vector<double> res;
	res.push_back(count);
	res.push_back(bestGlobalMin.getZ());
	res.push_back(time);
	for (int k = 0; k <  N; k++)
		res.push_back(bestGlobalMin.getY()[k]);
	return res;
}

vector<double> GlobalSearchM::startShekel()
{
	vector<double> lb, ub;
	shekelFam[index]->GetBounds(lb, ub);
	vector<double> answer = start([=](vector<double> y) { return shekelFam[index]->ComputeFunction({ y }); }, lb, ub);
	return answer;
}

vector<double> GlobalSearchM::startGrishagin()
{
	vector<double> lb, ub;
	grishaginFam[index]->GetBounds(lb, ub);
	vector<double> answer = start([=](vector<double> y) { return grishaginFam[index]->ComputeFunction({ y }); }, lb, ub);
	return answer;
}

vector<double> GlobalSearchM::startGKLS()
{
	vector<double> lb, ub;
	GKLSFam[index]->GetBounds(lb, ub);
	vector<double> answer = start([=](vector<double> y) { return GKLSFam[index]->ComputeFunction({ y }); }, lb, ub);
	return answer;
}

vector<double> GlobalSearchM::startHardGKLS()
{
	vector<double> lb, ub;
	GKLSFamHard[index]->GetBounds(lb, ub);
	vector<double> answer = start([=](vector<double> y) { return GKLSFamHard[index]->ComputeFunction({ y }); }, lb, ub);
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
