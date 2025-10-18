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

#include "Dot.h"

using namespace std;


class GlobalSearch
{

	vector<Dot> testSequence;
	double coefR;
	double a;
	double b;
	TShekelProblemFamily shekelFam;
	THillProblemFamily hillFam;
	int index;

	double countingM(int t, double M); // подсчёт коэффициента M

	void sortTestSequence(); // сортировка последовательности испытаний в порядке возрастания значений координаты

	double countingm(double M); // подсчёт коэффициента m

	int countingt(double m); // определение индекса интервала, которому соответствуетмаксимальная характеристика

	double GlobalSearch::pointTestShekel(Dot d) // испытание в точке для функции Шекеля
	{
		return shekelFam[index]->ComputeFunction({ d.getX() });
	}

	double GlobalSearch::pointTestHill(Dot d) // испытание в точке для функции Хилла
	{
		return hillFam[index]->ComputeFunction({ d.getX() });
	}

public:
	GlobalSearch(double a, double b, double r, int i) : a(a), b(b), coefR(r), index(i) {}

	vector<double> startShekel(); // алгоритм глобального поиска для функции Шекеля

	vector<double> startHill(); // алгоритм глобального поиска для функции Хилла

	double GetMinVShekel()
	{
		return shekelFam[index]->GetOptimumValue();
	}

	double GetMinVHill()
	{
		return hillFam[index]->GetOptimumValue();
	}
};
