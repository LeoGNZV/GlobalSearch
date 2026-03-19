#include <iostream>

#include "GlobalSearchM.h"

using namespace std;

int main()
{
	std::ofstream fout;
	vector<double> ans;

	cout << "  Shekel Problem Family" << std::endl;
	fout.open("MResultShekel.csv");
	fout << "Function number; number of iterations; 1 deviation from the global minimum by argument; 2 deviation from the global minimum by argument;Deviation from the global minimum in the value of the function; time\n";
	if (fout.is_open())
	{
		double N = 2;
		double* a = new double[N];
		double* b = new double[N];
		a[0] = a[1] = 0;
		b[0] = b[1] = 10;
		for (int i = 0; i < 1000; i++)
		{
			GlobalSearchM a(N, a, b, 4.05, i);
			ans = a.startShekel();
			string devValue = to_string(abs(ans[1] - a.GetMinVShekel()));
			string devArg1 = to_string(abs(a.GetMinArgShekel()[0] - ans[3]));
			string devArg2 = to_string(abs(a.GetMinArgShekel()[0] - ans[4]));
			devArg1.replace(devArg1.find("."), 1, ",");
			devArg2.replace(devArg2.find("."), 1, ",");
			devValue.replace(devValue.find("."), 1, ",");
			//cout << a.GetMinVShekel() << "\t" << a.GetMinArgShekel();
			fout << i << ";" << ans[0] << ";" << devArg1 << ";" << devArg2 << ";" << devValue << ";" << ans[2] << endl;
			cout << i << ";" << ans[0] << ";" << devArg1 << ";" << devArg2 << ";" << devValue << ";" << ans[2] << endl;
		}
		delete a, b;
	}
	fout.close();

	//cout << "  Shekel Problem Family" << std::endl;
	//fout.open("ResultShekelM.txt");
	//fout << "Function number; number of iterations; deviation from the global minimum by argument; Deviation from the global minimum in the value of the function; time\n";
	//if (fout.is_open())
	//{
	//	double N = 2;
	//	double* a = new double[N];
	//	double* b = new double[N];
	//	a[0] = a[1] = 0;
	//	b[0] = b[1] = 10;
	//	for (double r = 2; r <= 10; r += 0.01)
	//	{
	//		double maximumDeviation = 0.0;
	//		double averageDeviation = 0.0;
	//		for (int i = 0; i < 1000; i++)
	//		{
	//			GlobalSearchM a(N, a, b, r, i);
	//			ans = a.startShekel();
	//			double devValue = abs(ans[1] - a.GetMinVShekel());
	//			if (devValue > maximumDeviation)
	//				maximumDeviation = devValue;
	//			averageDeviation += devValue;
	//		}
	//		averageDeviation /= 1000;
	//		//string averDev = to_string(averageDeviation / 1000);
	//		//string maxDev = to_string(maximumDeviation);
	//		//maxDev.replace(maxDev.find("."), 1, ",");
	//		//averDev.replace(averDev.find("."), 1, ",");
	//		fout << r << ";" << maximumDeviation << ";" << averageDeviation << endl;
	//		cout << r << ";" << maximumDeviation << ";" << averageDeviation << endl;
	//	}
	//}
	//fout.close();

	//cout << "  Grishagin Problem Family" << std::endl;
	//fout.open("MResultGrishagin.csv");
	//fout << "Function number; number of iterations; 1 deviation from the global minimum by argument; 2 deviation from the global minimum by argument;Deviation from the global minimum in the value of the function; time\n";
	//if (fout.is_open())
	//{
	//	size_t N = 2;
	//	double* a = new double[N];
	//	double* b = new double[N];
	//	a[0] = a[1] = 0;
	//	b[0] = b[1] = 1;
	//	for (int i = 0; i < 100; i++)
	//	{
	//		GlobalSearchM a(N, a, b, 4, i);
	//		ans = a.startGrishagin();
	//		string devValue = to_string(abs(ans[1] - a.GetMinVGrishagin()));
	//		string devArg1 = to_string(abs(a.GetMinArgGrishagin()[0] - ans[3]));
	//		string devArg2 = to_string(abs(a.GetMinArgGrishagin()[1] - ans[4]));
	//		devArg1.replace(devArg1.find("."), 1, ",");
	//		devArg2.replace(devArg2.find("."), 1, ",");
	//		devValue.replace(devValue.find("."), 1, ",");
	//		cout << ans[1] << "\t" << a.GetMinVGrishagin() << "\n";
	//		cout << ans[3] << "\t" << a.GetMinArgGrishagin()[0] << "\n";
	//		cout << ans[4] << "\t" << a.GetMinArgGrishagin()[1] << "\n";
	//		fout << i << ";" << ans[0] << ";" << devArg1 << ";" << devArg2 << ";" << devValue << ";" << ans[2] << endl;
	//	}
	//	delete a, b;
	//}
	//fout.close();

	//cout << "  Grishagin Problem Family" << std::endl;
	//fout.open("ResultGrishaginM.txt");
	////fout << "Function number; number of iterations; deviation from the global minimum by argument; Deviation from the global minimum in the value of the function; time\n";
	//if (fout.is_open())
	//{
	//	double N = 2;
	//	double* a = new double[N];
	//	double* b = new double[N];
	//	a[0] = a[1] = 0;
	//	b[0] = b[1] = 1;
	//	for (double r = 8.94; r <= 10; r += 0.01)
	//	{
	//		double maximumDeviation = 0.0;
	//		double averageDeviation = 0.0;
	//		for (int i = 0; i < 100; i++)
	//		{
	//			GlobalSearchM a(N, a, b, r, i);
	//			ans = a.startGrishagin();
	//			double devValue = abs(ans[1] - a.GetMinVGrishagin());
	//			if (devValue > maximumDeviation)
	//				maximumDeviation = devValue;
	//			averageDeviation += devValue;
	//		}
	//		averageDeviation /= 1000;
	//		//string averDev = to_string(averageDeviation / 1000);
	//		//string maxDev = to_string(maximumDeviation);
	//		//maxDev.replace(maxDev.find("."), 1, ",");
	//		//averDev.replace(averDev.find("."), 1, ",");
	//		fout << r << ";" << maximumDeviation << ";" << averageDeviation << endl;
	//		cout << r << ";" << maximumDeviation << ";" << averageDeviation << endl;
	//	}
	//}
	fout.close();

}



