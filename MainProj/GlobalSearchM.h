#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <ctime>

#include "Shekel/ShekelProblem.hpp"
#include "Shekel/ShekelProblemFamily.hpp"

#include "Hill/HillProblem.hpp"
#include "Hill/HillProblemFamily.hpp"

#include "Grishagin/Grishagin_function.hpp"
#include "Grishagin/GrishaginProblemFamily.hpp"

#include "DotN.h"

using namespace std;


class GlobalSearchM
{

	vector<DotN> testSequence;
	double N; // размерность пространства
	double coefR;
	double* a;
	double* b;
	TShekelProblemFamily shekelFam;
	THillProblemFamily hillFam;
	TGrishaginProblemFamily grishaginFam;
	int index;

	Extended countingM(int t, Extended M); // подсчёт коэффициента M

	void sortTestSequence(); // сортировка последовательности испытаний в порядке возрастания значений координаты

	Extended countingm(Extended M); // подсчёт коэффициента m

	int countingt(Extended m); // определение индекса интервала, которому соответствуетмаксимальная характеристика

	double GlobalSearchM::pointTestShekel(DotN d) // испытание в точке для функции Шекеля
	{
		return shekelFam[index]->ComputeFunction({ d.getY() });
	}

	double GlobalSearchM::pointTestHill(DotN d) // испытание в точке для функции Хилла
	{
		return hillFam[index]->ComputeFunction({ d.getY() });
	}

	double GlobalSearchM::pointTestGrishagin(DotN d) // испытание в точке для функции Гришагина
	{
		return grishaginFam[index]->ComputeFunction({ d.getY() });
	}

	double sgn(Extended x)
	{
		return (x > 0) ? 1.0 : (x < 0) ? -1.0: 0.0;
	}

	template<typename Func>
	vector<double> start(Func valueCountFunc);

public:
	GlobalSearchM(size_t n, double* a, double* b, double r, int i) : N(n), a(a), b(b), coefR(r), index(i) {}

	vector<double> startShekel(); // алгоритм глобального поиска для функции Шекеля

	vector<double> startHill(); // алгоритм глобального поиска для функции Xилла

	vector<double> startGrishagin(); // алгоритм глобального поиска для функции Гришагина

	double GetMinVShekel()
	{
		return shekelFam[index]->GetOptimumValue();
	}

	double GetMinVHill()
	{
		return hillFam[index]->GetOptimumValue();
	}

	double GetMinVGrishagin()
	{
		return grishaginFam[index]->GetOptimumValue();
	}

	vector<double> GetMinArgShekel()
	{
		return shekelFam[index]->GetOptimumPoint();
	}

	vector<double> GetMinArgHill()
	{
		return hillFam[index]->GetOptimumPoint();
	}

	vector<double> GetMinArgGrishagin()
	{
		return grishaginFam[index]->GetOptimumPoint();
	}
};
