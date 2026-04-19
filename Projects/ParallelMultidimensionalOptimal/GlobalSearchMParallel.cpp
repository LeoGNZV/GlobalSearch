#include "mpi.h"
#include <iostream>

#include"GlobalSearchMParallel.h"

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



template<typename Func>
vector<double> GlobalSearchM::start(Func valueCountFunc, vector<double> a_ , vector<double> b_)
{

	Extended x1 = 0.0, x2 = 1.0;
	Interval a1(x1, x2, a_.data(), b_.data(), N, valueCountFunc);
	testSequenceInterval.push(a1);

	size_t count = 0;
	DotN bestGlobalMin(a1.getLeftDot());
	if (a1.getRightZ() < bestGlobalMin.getZ())
	{
		bestGlobalMin = a1.getRightDot();
		//recountInterval(Extended M, double bestGlobalMin, size_t N, double m)
	}
	int procNum = 0;
	int procRank = 0;
	MPI_Comm_size(MPI_COMM_WORLD, &procNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
	
	auto t1 = std::chrono::steady_clock::now();

	Extended M = fabs(testSequenceInterval.top().getRightZ() - testSequenceInterval.top().getLeftZ()) / pow((testSequenceInterval.top().getRightX() - testSequenceInterval.top().getLeftX()), 1.0 / N);
	Extended m = countingm(M);

	bool changesCharac = false;
	// формируем новые точки с шагом step, чтобы количество интварвалов стало равно procNum
	if (procNum > 1)
	{
		Extended step = (x2 - x1) / (procNum);
		Interval primaryInterval = testSequenceInterval.top();
		testSequenceInterval.pop();
		vector<DotN> testSequenceDot;
		testSequenceDot.resize(procNum - 2);

		Extended nEl1 = x1 + step; // получаем координату первой новой точки
		DotN newElemSequence1(nEl1, a_.data(), b_.data(), N); // получаем новую точку
		newElemSequence1.pointTest(valueCountFunc(newElemSequence1.getY())); // получаем значение новой точки
		testSequenceDot.push_back(newElemSequence1);
		if (newElemSequence1.getZ() < bestGlobalMin.getZ()) // проверяем не является ли новая точка предполагаемой точкой глобального минимума
		{
			changesCharac = true;
			bestGlobalMin = newElemSequence1;
		}

		Interval interval1(primaryInterval.getLeftDot(), newElemSequence1, m, N, bestGlobalMin.getZ()); // формируем новый интервал
		testSequenceInterval.push(interval1); // добавляем этот интварл в очередь 
		Extended M1 = fabs(interval1.getRightZ() - interval1.getLeftZ()) / pow((interval1.getRightX() - interval1.getLeftX()), 1.0 / N);
		if (M1 > M)
		{
			changesCharac = true;
			M = M1;
			m = countingm(M);
		}
		for (int i = 1; i < procNum - 1; i++)
		{
			Extended nEl = x1 + i * step;
			DotN newElemSequence(nEl, a_.data(), b_.data(), N);
			newElemSequence.pointTest(valueCountFunc(newElemSequence.getY()));
			if (newElemSequence.getZ() < bestGlobalMin.getZ())
			{
				changesCharac = true;
				bestGlobalMin = newElemSequence;
			}
			testSequenceDot.push_back(newElemSequence);

			Interval interval3(testSequenceDot[i - 1], newElemSequence, m, N, bestGlobalMin.getZ()); // формируем новый интервал
			testSequenceInterval.push(interval3); // добавляем этот интварл в очередь 
			M1 = fabs(interval3.getRightZ() - interval3.getLeftZ()) / pow((interval3.getRightX() - interval3.getLeftX()), 1.0 / N);
			if (M1 > M)
			{
				changesCharac = true;
				M = M1;
				m = countingm(M);
			}
		}
		Extended nEl2 = x1 + (procNum - 1) * step;
		DotN newElemSequence2(nEl2, a_.data(), b_.data(), N);
		newElemSequence2.pointTest(valueCountFunc(newElemSequence2.getY()));
		if (newElemSequence2.getZ() < bestGlobalMin.getZ())
		{
			changesCharac = true;
			bestGlobalMin = newElemSequence2;
		}
			

		Interval interval2(newElemSequence2, primaryInterval.getRightDot(), m, N, bestGlobalMin.getZ()); // формируем новый интервал
		testSequenceInterval.push(interval2); // добавляем этот интварл в очередь 
		M1 = fabs(interval2.getRightZ() - interval2.getLeftZ()) / pow((interval2.getRightX() - interval2.getLeftX()), 1.0 / N);
		if (M1 > M)
		{
			changesCharac = true;
			M = M1;
			m = countingm(M);
		}

		if (changesCharac)
		{
			size_t size = testSequenceInterval.size();
			std::vector<Interval> helpSequence;
			helpSequence.reserve(size);
			for (int j = 0; j < size; j++)
			{
				Interval a = testSequenceInterval.top();
				a.recountInterval(m, bestGlobalMin.getZ(), N);
				helpSequence.push_back(a);
				testSequenceInterval.pop();
			}
			for (int j = 0; j < size; j++)
				testSequenceInterval.push(helpSequence[j]);
		}
	}

	bool continue_iteration = true;
	do
	{
		vector<double> bufferSend; // буффер, в который на корневом процессе загружаются точки N-мерного пространства
		vector<double> bufferReceiving(N, 0.0); // буффер, содержащий координаты точки N-мерного пространства, для которой нужно вычислить значение

		vector<Extended> newElementsExtended;
		vector<vector<double>> newElementsY;
		vector<double> newElementsZ(procNum);

		count++;
		m = countingm(M);

		vector<Interval> maxInterval;

		// формируем newElementsExtended
		for (int k = 0; k < procNum; k++)
		{
			maxInterval.push_back(testSequenceInterval.top());
			testSequenceInterval.pop();
			Extended nEl;
			if ((maxInterval[k].getLeftX() == 0.0) || (maxInterval[k].getRightX() == 1.0))
				nEl = 0.5 * (maxInterval[k].getRightX() + maxInterval[k].getLeftX());
			else
				nEl = 0.5 * (maxInterval[k].getRightX() + maxInterval[k].getLeftX()) 
					- 0.5 / coefR * sgn(maxInterval[k].getRightZ() - maxInterval[k].getLeftZ()) 
						* pow(abs(maxInterval[k].getRightZ() - maxInterval[k].getLeftZ()) / M, N);
			newElementsExtended.push_back(nEl);
		}

		for (int k = 0; k < procNum; k++)
		{
			vector<double> newY;

			// формируем newElementsY
			Evolvent h(N, 10);
			h.SetBounds(a_.data(), b_.data());
			double* yNewFormat = new double[N];
			h.GetImage(newElementsExtended[k], yNewFormat);
			for (int l = 0; l < N; l++)
			{
				newY.push_back(yNewFormat[l]);
				bufferSend.push_back(yNewFormat[l]); // собираем координаты точек в N-мерном пространстве, в которых нужно провести испытание, в один буффер
			}
			delete[] yNewFormat;
			newElementsY.push_back(newY);
		}

		MPI_Scatter((procRank == 0) ? bufferSend.data() : nullptr, N, MPI_DOUBLE, bufferReceiving.data(), N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		double z = valueCountFunc(bufferReceiving);
		
		MPI_Gather(&z, 1, MPI_DOUBLE, newElementsZ.data(), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		changesCharac = false;
		bool provisional_continue_iteratiom = true;
		for (int k = 0; k < procNum; k++)
		{
			DotN newElemSequence(newElementsY[k], newElementsExtended[k], newElementsZ[k]);
			if (newElemSequence.getZ() < bestGlobalMin.getZ())
			{
				changesCharac = true;
				bestGlobalMin = newElemSequence;
			}
			Interval interval1(maxInterval[k].getLeftDot(), newElemSequence, m, N, bestGlobalMin.getZ());
			testSequenceInterval.push(interval1);

			Extended M1 = fabs(interval1.getRightZ() - interval1.getLeftZ()) / pow((interval1.getRightX() - interval1.getLeftX()), 1.0 / N);
			if (M1 > M)
			{
				changesCharac = true;
				M = M1;
				m = countingm(M);
			}

			Interval interval2(newElemSequence, maxInterval[k].getRightDot(), m, N, bestGlobalMin.getZ());
			testSequenceInterval.push(interval2);

			M1 = fabs(interval2.getRightZ() - interval2.getLeftZ()) / pow((interval2.getRightX() - interval2.getLeftX()), 1.0 / N);
			if (M1 > M)
			{
				changesCharac = true;
				M = M1;
				m = countingm(M);
			}

			if (pow(interval2.getRightX() - interval1.getLeftX(), 1.0 / N) < 0.01)
			{
				provisional_continue_iteratiom = false;
			}
		}
		if (changesCharac)
		{
			size_t size = testSequenceInterval.size();
			std::vector<Interval> helpSequence;
			helpSequence.reserve(size);
			for (int j = 0; j < size; j++)
			{
				Interval a = testSequenceInterval.top();
				a.recountInterval(m, bestGlobalMin.getZ(), N);
				helpSequence.push_back(a);
				testSequenceInterval.pop();
			}
			for (int j = 0; j < size; j++)
				testSequenceInterval.push(helpSequence[j]);
		}
		continue_iteration = provisional_continue_iteratiom;

		MPI_Bcast(&continue_iteration, 1, MPI_C_BOOL, 0, MPI_COMM_WORLD);

	} while (continue_iteration);

	auto t2 = std::chrono::steady_clock::now();
	double time = (t2 - t1).count();

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
	double hN = N;
	N = 1;
	vector<double> answer = start([=](vector<double> y) { return shekelFam[index]->ComputeFunction({ y }); }, lb, ub);
	N = hN;
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
