#include "mpi.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <chrono>

#include "Shekel/ShekelProblem.hpp"
#include "Shekel/ShekelProblemFamily.hpp"

#include "Grishagin/Grishagin_function.hpp"
#include "Grishagin/GrishaginProblemFamily.hpp"

#include "GKLS/GKLSProblem.hpp"
#include "GKLS/GKLSProblemFamily.hpp"

#include "DotNParallel.h"

using namespace std;


class GlobalSearchM
{

	vector<DotN> testSequence;
	double N; // размерность пространства
	double coefR;
	TShekelProblemFamily shekelFam;
	TGrishaginProblemFamily grishaginFam;
	TGKLSProblemFamily GKLSFam;
	TGKLSProblemFamily GKLSFamHard;
	int index;

	Extended countingM(Extended M); // подсчёт коэффициента M

	Extended countingMfrommaxt(vector<int> t, Extended M, int p);

	void sortTestSequence(); // сортировка последовательности испытаний в порядке возрастания значений координаты

	Extended countingm(Extended M); // подсчёт коэффициента m

	int countingt(Extended m); // определение индекса интервала, которому соответствуетмаксимальная характеристика

	vector<int> countingtParallel(Extended m, int p, double bestGlobalMin); // определение набора индексов интервалов, которым соответствует количество максимальных характеристик равное количеству процессов

	//double GlobalSearchM::pointTestShekel(DotN d) // испытание в точке для функции Шекеля
	//{
	//	return shekelFam[index]->ComputeFunction({ d.getY() });
	//}

	//double GlobalSearchM::pointTestGrishagin(DotN d) // испытание в точке для функции Гришагина
	//{
	//	return grishaginFam[index]->ComputeFunction({ d.getY() });
	//}

	//double GlobalSearchM::pointTestGKLS(DotN d) // испытание в точке для функции GKLS
	//{
	//	return GKLSFam[index]->ComputeFunction({ d.getY() });
	//}


	double sgn(Extended x)
	{
		return (x > 0) ? 1.0 : (x < 0) ? -1.0: 0.0;
	}

	template<typename Func>
	vector<double> start(Func valueCountFunc, vector<double> a, vector<double> b);

public:
	GlobalSearchM(size_t n, double r, int i) : N(n), coefR(r), index(i), GKLSFam(N, Simple), GKLSFamHard(N, Hard) {}

	vector<double> startShekel(); // алгоритм глобального поиска для функции Шекеля

	vector<double> startHill(); // алгоритм глобального поиска для функции Xилла

	vector<double> startGrishagin(); // алгоритм глобального поиска для функции Гришагина

	vector<double> startGKLS(); // алгоритм глобального поиска для функции GKLS simple

	vector<double> startHardGKLS(); // алгоритм глобального поиска для функции GKLS hard

	double GetMinVShekel()
	{
		return shekelFam[index]->GetOptimumValue();
	}

	double GetMinVGrishagin()
	{
		return grishaginFam[index]->GetOptimumValue();
	}

	double GetMinVGKLS()
	{
		return GKLSFam[index]->GetOptimumValue();
	}

	double GetMinVHardGKLS()
	{
		return GKLSFam[index]->GetOptimumValue();
	}

	vector<double> GetMinArgShekel()
	{
		return shekelFam[index]->GetOptimumPoint();
	}

	vector<double> GetMinArgGrishagin()
	{
		return grishaginFam[index]->GetOptimumPoint();
	}

	vector<double> GetMinArgGKLS()
	{
		return GKLSFam[index]->GetOptimumPoint();
	}

	vector<double> GetMinArgHardGKLS()
	{
		return GKLSFam[index]->GetOptimumPoint();
	}
};
