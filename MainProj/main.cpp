#include <iostream>

#include "GlobalSearch.h"

using namespace std;

int main()
{
	cout << "  Shekel Problem Family" << std::endl;
	std::ofstream fout;
	fout.open("ResultShekel.csv");
	fout << "Function number; number of iterations; deviation from the global minimum; time\n";
	vector<double> ans;
	if (fout.is_open())
	{
		for (int i = 0; i < 1000; i++)
		{
			GlobalSearch a(0, 10, 2, i);
			ans = a.startShekel();
			fout << i << ";" << ans[0] << ";" << abs(ans[1] - a.GetMinVShekel()) << ";" << ans[2] << endl;
		}
	}
	fout.close();
	cout << "  Hill Problem Family" << std::endl;
	fout.open("ResultHill.csv");
	fout << "Function number; number of iterations; deviation from the global minimum; time\n";
	if (fout.is_open())
	{
		for (int i = 0; i < 1000; i++)
		{
			GlobalSearch a(0, 1, 2, i);
			ans = a.startHill();
			fout << i << ";" << ans[0] << ";" << abs(ans[1] - a.GetMinVHill()) << ";" << ans[2] << endl;
		}
	}
	fout.close();
}

