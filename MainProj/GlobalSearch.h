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

	double countingM(int t, double M); // ������� ������������ M

	void sortTestSequence(); // ���������� ������������������ ��������� � ������� ����������� �������� ����������

	double countingm(double M); // ������� ������������ m

	int countingt(double m); // ����������� ������� ���������, �������� ������������������������� ��������������

	double GlobalSearch::pointTestShekel(Dot d) // ��������� � ����� ��� ������� ������
	{
		return shekelFam[index]->ComputeFunction({ d.getX() });
	}

	double GlobalSearch::pointTestHill(Dot d) // ��������� � ����� ��� ������� �����
	{
		return hillFam[index]->ComputeFunction({ d.getX() });
	}

public:
	GlobalSearch(double a, double b, double r, int i) : a(a), b(b), coefR(r), index(i) {}

	vector<double> startShekel(); // �������� ����������� ������ ��� ������� ������

	vector<double> startHill(); // �������� ����������� ������ ��� ������� �����

	double GetMinVShekel()
	{
		return shekelFam[index]->GetOptimumValue();
	}

	double GetMinVHill()
	{
		return hillFam[index]->GetOptimumValue();
	}
};
