#include <mpi.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <random>

#include "GlobalSearchMParallel.h"

using namespace std;

int main()
{
	MPI_Init(NULL, NULL);

	int procNum = 0;
	int procRank = 0;
	MPI_Comm_size(MPI_COMM_WORLD, &procNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);

	double N = 2;

	//TGKLSProblemFamily(int dim = 2, GKLSClass type = Simple, GKLSFuncionType functionType = TD) : IOptProblemFamily()
	//{
	//	for (int i = 1; i <= 100; i++)
	//		pOptProblems.push_back(new TGKLSProblem(i, dim, type, functionType));
	//}

	if (procRank == 0)
	{

		std::ofstream fout;
		vector<double> ans;
		
		//cout << "  Shekel Problem Family" << std::endl;
		//fout.open("MResultShekel.csv");
		//fout << "Function number; number of iterations; 1 deviation from the global minimum by argument; Deviation from the global minimum in the value of the function; time\n";
		//if (fout.is_open())
		//{
		//	for (int i = 0; i < 1000; i++)
		//	{
		//		GlobalSearchM a(N, 2.7, i);
		//		ans = a.startShekel();
		//		string devValue = to_string(abs(ans[1] - a.GetMinVShekel()));
		//		string devArg1 = to_string(abs(a.GetMinArgShekel()[0] - ans[3]));
		//		devArg1.replace(devArg1.find("."), 1, ",");
		//		devValue.replace(devValue.find("."), 1, ",");
		//		fout << i << ";" << ans[0] << ";" << devArg1 << ";" << devValue << ";" << ans[2] << ";" << endl;
		//		cout << i << ";" << ans[0] << "; devArg1 " << devArg1 << "; devValue " << devValue << ";" << ans[2] << endl;
		//	}
		//}
		//fout.close();

		/*cout << "  Grishagin Problem Family" << std::endl;
		fout.open("ResultGrishaginM.csv");
		fout << "Function number; number of iterations; deviation from the global minimum by argument 1; deviation from the global minimum by argument 2;Deviation from the global minimum in the value of the function; time\n";
		if (fout.is_open())
		{
			for (int i = 0; i < 100; i++)
			{
				GlobalSearchM a(2, 4.9, i);
				ans = a.startGrishagin();
				string devValue = to_string(abs(ans[1] - a.GetMinVGrishagin()));
				string devArg1 = to_string(abs(a.GetMinArgGrishagin()[0] - ans[3]));
				string devArg2 = to_string(abs(a.GetMinArgGrishagin()[1] - ans[4]));
				devArg1.replace(devArg1.find("."), 1, ",");
				devArg2.replace(devArg2.find("."), 1, ",");
				devValue.replace(devValue.find("."), 1, ",");
				fout << i << ";" << ans[0] << ";" << devArg1 << ";" << devArg2 << ";" << devValue << ";" << ans[2] << ";" << endl;
				cout << i << ";" << ans[0] << "; devArg1 " << devArg1 << "; devArg2 " << devArg2 <<  "; devValue " << devValue << ";" << ans[2] << endl;
			}
		}
		fout.close();*/

		cout << " GKLS Problem Family" << std::endl;
		fout.open("MResultGKLS.csv");
		fout << "Function number; number of iterations; 1 deviation from the global minimum by argument; 2 deviation from the global minimum by argument;Deviation from the global minimum in the value of the function; time\n";
		if (fout.is_open())
		{
			//for (double r = 8.49; r < 10.0; r += 0.01)
			//{
			//	bool ok = true;
			//	for (int i = 0; i <= 99; i++)
			//	{
			//		GlobalSearchM a(N, r, i);
			//		ans = a.startGKLS();
			//		string devValue = to_string(abs(ans[1] - a.GetMinVGKLS()));
			//		string devArg1 = to_string(abs(a.GetMinArgGKLS()[0] - ans[3]));
			//		string devArg2 = to_string(abs(a.GetMinArgGKLS()[1] - ans[4]));
			//		cout << i << ";" << ans[0] << "; devArg1 " << devArg1 << ";" << devArg2 << "; devValue " << devValue << ";" << ans[2] << endl;
			//		if (abs(a.GetMinArgGKLS()[0] - ans[3]) > 0.01 || (abs(a.GetMinArgGKLS()[1] - ans[4])) > 0.01)
			//		{
			//			cout << "\n Pipezh " << r << " bad \n";
			//			ok = false;
			//			break;
			//		}
			//		devArg1.replace(devArg1.find("."), 1, ",");
			//		devArg2.replace(devArg2.find("."), 1, ",");
			//		devValue.replace(devValue.find("."), 1, ",");
			//		fout << i << ";" << ans[0] << ";" << devArg1 << ";" << devArg2 << ";" << devValue << ";" << ans[2] << endl;
			//	}
			//	if (ok == true)
			//	{
			//		cout << "\n Win! \n " << r << endl;
			//		break;
			//	}
			//}
			
			for (int i = 0; i < 100; i++)
			{
				GlobalSearchM a(3, 8.5, i);
				ans = a.startGKLS();
				string devValue = to_string(abs(ans[1] - a.GetMinVGKLS()));
				string devArg1 = to_string(abs(a.GetMinArgGKLS()[0] - ans[3]));
				string devArg2 = to_string(abs(a.GetMinArgGKLS()[1] - ans[4]));
				if (abs(a.GetMinArgGKLS()[0] - ans[3]) > 0.01 || (abs(a.GetMinArgGKLS()[1] - ans[4])) > 0.01)
					cout << "\n Pipezh \n";
				devArg1.replace(devArg1.find("."), 1, ",");
				devArg2.replace(devArg2.find("."), 1, ",");
				devValue.replace(devValue.find("."), 1, ",");
				fout << i << ";" << ans[0] << ";" << devArg1 << ";" << devArg2 << ";" << devValue << ";" << ans[2] << endl;
				cout << i << ";" << ans[0] << "; devArg1 " << devArg1 << ";" << devArg2 << "; devValue " << devValue << ";" << ans[2] << endl;
			}
		}
		fout.close();

		cout << " GKLS Problem Family" << std::endl;
		fout.open("MResultGKLS.csv");
		fout << "Function number; number of iterations; 1 deviation from the global minimum by argument; 2 deviation from the global minimum by argument; 3 deviation from the global minimum by argument;Deviation from the global minimum in the value of the function; time; solved\n";
		if (fout.is_open())
		{
			N = 3;
			size_t averageNumberIterations = 0;
			double average1deviationArgument = 0;
			double average2deviationArgument = 0;
			double average3deviationArgument = 0;
			double averageDeviationValueFunction = 0;
			double averageTime = 0;
			size_t Solved = 0;
			double max1deviationArgument = 0;
			double max2deviationArgument = 0;
			double max3deviationArgument = 0;
			double maxDeviationValueFunction = 0;
			for (int i = 0; i < 100; i++)
			{
				size_t solved = 0;
				GlobalSearchM a(N, 8.5, i);
				ans = a.startGKLS();
				string devValue = to_string(abs(ans[1] - a.GetMinVGKLS()));
				string devArg1 = to_string(abs(a.GetMinArgGKLS()[0] - ans[3]));
				string devArg2 = to_string(abs(a.GetMinArgGKLS()[1] - ans[4]));
				string devArg3 = to_string(abs(a.GetMinArgGKLS()[2] - ans[5]));
				string t = to_string(ans[2]);
				if (abs(a.GetMinArgGKLS()[0] - ans[3] + 0.000001 < 0.01) && (abs(a.GetMinArgGKLS()[1] - ans[4]) + 0.000001 < 0.01) && (abs(a.GetMinArgGKLS()[2] - ans[5]) + 0.000001 < 0.01))
				{
					solved++;
					Solved++;
				}
				devArg1.replace(devArg1.find("."), 1, ",");
				devArg2.replace(devArg2.find("."), 1, ",");
				devArg3.replace(devArg3.find("."), 1, ",");
				devValue.replace(devValue.find("."), 1, ",");
				t.replace(t.find("."), 1, ",");
				fout << i << ";" << ans[0] << ";" << devArg1 << ";" << devArg2 << ";" << devArg3 << ";" << devValue << ";" << t << ";" << solved << endl;
				cout << i << ";" << ans[0] << "; devArg1 " << devArg1 << ";" << devArg2 << ";" << devArg2 << "; devValue " << devValue << ";" << t << ";" << solved << endl;

				averageNumberIterations += ans[0];
				average1deviationArgument += abs(a.GetMinArgGKLS()[0] - ans[3]);
				average2deviationArgument += abs(a.GetMinArgGKLS()[1] - ans[4]);
				average3deviationArgument += abs(a.GetMinArgGKLS()[2] - ans[5]);
				averageDeviationValueFunction += abs(ans[1] - a.GetMinVGKLS());
				averageTime += ans[2];

				if (max1deviationArgument < abs(a.GetMinArgGKLS()[0] - ans[3])) max1deviationArgument = abs(a.GetMinArgGKLS()[0] - ans[3]);
				if (max2deviationArgument < abs(a.GetMinArgGKLS()[1] - ans[4])) max2deviationArgument = abs(a.GetMinArgGKLS()[1] - ans[4]);
				if (max3deviationArgument < abs(a.GetMinArgGKLS()[2] - ans[5])) max2deviationArgument = abs(a.GetMinArgGKLS()[2] - ans[5]);
				if (maxDeviationValueFunction < abs(a.GetMinArgGKLS()[1] - ans[4])) maxDeviationValueFunction = abs(ans[1] - a.GetMinVGKLS());
			}
			N = 2;
			cout << "averageNumberIterations" << "\t" << averageNumberIterations / 100 << endl;
			cout << "average1deviationArgument" << "\t" << average1deviationArgument / 100 << endl;
			cout << "average2deviationArgument" << "\t" << average2deviationArgument / 100 << endl;
			cout << "average3deviationArgument" << "\t" << average3deviationArgument / 100 << endl;
			cout << "averageDeviationValueFunction" << "\t" << averageDeviationValueFunction / 100 << endl;
			cout << "averageTime" << "\t" << averageTime / 100 << endl;
			cout << "Solved" << Solved << endl;
			cout << "max1deviationArgument" << "\t" << max1deviationArgument << endl;
			cout << "max2deviationArgument" << "\t" << max2deviationArgument << endl;
			cout << "max3deviationArgument" << "\t" << max3deviationArgument << endl;
			cout << "maxDeviationValueFunction" << "\t" << maxDeviationValueFunction << endl;
		}
		fout.close();

		//cout << " GKLS Problem Family" << std::endl;
		//fout.open("MResultGKLSN3.csv");
		//fout << "Function number; number of iterations; 1 deviation from the global minimum by argument; 2 deviation from the global minimum by argument; 3 deviation from the global minimum by argument;Deviation from the global minimum in the value of the function; time\n";
		//if (fout.is_open())
		//{
		//	for (int i = 0; i < 100; i++)
		//	{
		//		GlobalSearchM a(3, 8.5, i);
		//		ans = a.startGKLS();
		//		string devValue = to_string(abs(ans[1] - a.GetMinVGKLS()));
		//		string devArg1 = to_string(abs(a.GetMinArgGKLS()[0] - ans[3]));
		//		string devArg2 = to_string(abs(a.GetMinArgGKLS()[1] - ans[4]));
		//		string devArg3 = to_string(abs(a.GetMinArgGKLS()[2] - ans[5]));
		//		if (abs(a.GetMinArgGKLS()[0] - ans[3]) > 0.01 || (abs(a.GetMinArgGKLS()[1] - ans[4])) > 0.01 || (abs(a.GetMinArgGKLS()[2] - ans[5])) > 0.01)
		//			cout << "\n Pipezh \n";
		//		devArg1.replace(devArg1.find("."), 1, ",");
		//		devArg2.replace(devArg2.find("."), 1, ",");
		//		devArg3.replace(devArg3.find("."), 1, ",");
		//		devValue.replace(devValue.find("."), 1, ",");
		//		fout << i << ";" << ans[0] << ";" << devArg1 << ";" << devArg2 << ";" << devArg3 << ";" << devValue << ";" << ans[2] << endl;
		//		cout << i << ";" << ans[0] << "; devArg1 " << devArg1 << ";" << devArg2 << ";" << devArg3 << "; devValue " << devValue << ";" << ans[2] << endl;
		//	}
		//}
		//fout.close();
		
		//cout << " hard GKLS Problem Family" << std::endl;
		//fout.open("MResultHardGKLS.csv");
		//fout << "Function number; number of iterations; 1 deviation from the global minimum by argument; 2 deviation from the global minimum by argument;Deviation from the global minimum in the value of the function; time\n";
		//if (fout.is_open())
		//{
		//	/*for (double r = 1.01; r < 10.0; r += 0.01)
		//	{
		//		bool ok = true;
		//		for (int i = 0; i <= 99; i++)
		//		{
		//			GlobalSearchM a(N, r, i);
		//			ans = a.startHardGKLS();
		//			string devValue = to_string(abs(ans[1] - a.GetMinVHardGKLS()));
		//			string devArg1 = to_string(abs(a.GetMinArgHardGKLS()[0] - ans[3]));
		//			string devArg2 = to_string(abs(a.GetMinArgHardGKLS()[1] - ans[4]));
		//			cout << i << ";" << ans[0] << "; devArg1 " << devArg1 << ";" << devArg2 << "; devValue " << devValue << ";" << ans[2] << endl;
		//			if (abs(a.GetMinArgHardGKLS()[0] - ans[3]) > 0.001 || (abs(a.GetMinArgHardGKLS()[1] - ans[4])) > 0.001)
		//			{
		//				cout << "\n Pipezh " << r << " bad \n";
		//				ok = false;
		//				break;
		//			}
		//			devArg1.replace(devArg1.find("."), 1, ",");
		//			devArg2.replace(devArg2.find("."), 1, ",");
		//			devValue.replace(devValue.find("."), 1, ",");
		//			fout << i << ";" << ans[0] << ";" << devArg1 << ";" << devArg2 << ";" << devValue << ";" << ans[2] << endl;
		//		}
		//		if (ok == true)
		//		{
		//			cout << "\n Win! \n " << r << endl;
		//			break;
		//		}
		//	}*/
		//	//for (int i = 0; i < 1000000; i++)
		//	//{
		//	//	TGKLSProblemFamily GKLSFamHard(N, Hard);

		//	//	double z = GKLSFamHard[i]->ComputeFunction({  });
		//	//	/*GlobalSearchM a(N, 8.5, i);
		//	//	ans = a.startHardGKLS();
		//	//	string devValue = to_string(abs(ans[1] - a.GetMinVHardGKLS()));
		//	//	string devArg1 = to_string(abs(a.GetMinArgHardGKLS()[0] - ans[3]));
		//	//	string devArg2 = to_string(abs(a.GetMinArgHardGKLS()[1] - ans[4]));
		//	//	if (abs(a.GetMinArgHardGKLS()[0] - ans[3]) > 0.01 || (abs(a.GetMinArgHardGKLS()[1] - ans[4])) > 0.01)
		//	//		cout << "\n Pipezh \n";
		//	//	devArg1.replace(devArg1.find("."), 1, ",");
		//	//	devArg2.replace(devArg2.find("."), 1, ",");
		//	//	devValue.replace(devValue.find("."), 1, ",");
		//	//	fout << i << ";" << ans[0] << ";" << devArg1 << ";" << devArg2 << ";" << devValue << ";" << ans[2] << endl;
		//	//	cout << i << ";" << ans[0] << "; devArg1 " << devArg1 << ";" << devArg2 << "; devValue " << devValue << ";" << ans[2] << endl;*/

		//	//}
		//	for (int i = 0; i < 100; i++)
		//	{
		//		GlobalSearchM a(3, 9.1, i);
		//		ans = a.startHardGKLS();
		//		string devValue = to_string(abs(ans[1] - a.GetMinVHardGKLS()));
		//		string devArg1 = to_string(abs(a.GetMinArgHardGKLS()[0] - ans[3]));
		//		string devArg2 = to_string(abs(a.GetMinArgHardGKLS()[1] - ans[4]));
		//		if (abs(a.GetMinArgHardGKLS()[0] - ans[3]) > 0.01 || (abs(a.GetMinArgHardGKLS()[1] - ans[4])) > 0.01)
		//			cout << "\n Pipezh \n";
		//		devArg1.replace(devArg1.find("."), 1, ",");
		//		devArg2.replace(devArg2.find("."), 1, ",");
		//		devValue.replace(devValue.find("."), 1, ",");
		//		fout << i << ";" << ans[0] << ";" << devArg1 << ";" << devArg2 << ";" << devValue << ";" << ans[2] << endl;
		//		cout << i << ";" << ans[0] << "; devArg1 " << devArg1 << ";" << devArg2 << "; devValue " << devValue << ";" << ans[2] << endl;
		//	}
		//}
		//fout.close();
	}
	else
	{
		TShekelProblemFamily shekelFam;
		TGrishaginProblemFamily grishaginFam;
		TGKLSProblemFamily GKLSFam;
		TGKLSProblemFamily GKLSFamHard(N, Hard);

		std::vector<double> bufferReceiving(N);
		std::vector<double> newElementsZ(procNum);

		//for (int i = 0; i < 1000; i++)
		//{
		//	bool continue_iteration = true;
		//	do
		//	{
		//		MPI_Scatter(nullptr, N, MPI_DOUBLE, bufferReceiving.data(), N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		//		double z = shekelFam[i]->ComputeFunction({ bufferReceiving });

		//		MPI_Gather(&z, 1, MPI_DOUBLE, newElementsZ.data(), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		//		MPI_Bcast(&continue_iteration, 1, MPI_C_BOOL, 0, MPI_COMM_WORLD);
		//	} while (continue_iteration);
		//}
		
		/*for (int i = 0; i < 100; i++)
		{
			bool continue_iteration = true;
			do
			{
				MPI_Scatter( nullptr, N, MPI_DOUBLE, bufferReceiving.data(), N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

				double z = grishaginFam[i]->ComputeFunction({ bufferReceiving });

				MPI_Gather(&z, 1, MPI_DOUBLE, newElementsZ.data(), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

				MPI_Bcast(&continue_iteration, 1, MPI_C_BOOL, 0, MPI_COMM_WORLD);
			} while (continue_iteration);
		}*/

		//for (int i = 0; i < 100; i++)
		//{
		//	bool continue_iteration = true;
		//	do
		//	{
		//		MPI_Scatter(nullptr, N, MPI_DOUBLE, bufferReceiving.data(), N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		//		double z = GKLSFam[i]->ComputeFunction({ bufferReceiving });

		//		MPI_Gather(&z, 1, MPI_DOUBLE, newElementsZ.data(), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		//		MPI_Bcast(&continue_iteration, 1, MPI_C_BOOL, 0, MPI_COMM_WORLD);
		//	} while (continue_iteration);
		//}
		size_t countCount = 0;
		for (int i = 0; i < 100; i++)
		{
			bool continue_iteration = true;
			do
			{
				MPI_Scatter(nullptr, N, MPI_DOUBLE, bufferReceiving.data(), N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

				double z = GKLSFamHard[i]->ComputeFunction({ bufferReceiving });

				MPI_Gather(&z, 1, MPI_DOUBLE, newElementsZ.data(), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

				countCount++;
				MPI_Bcast(&continue_iteration, 1, MPI_C_BOOL, 0, MPI_COMM_WORLD);
			} while (continue_iteration);
			cout << countCount << endl;
			countCount = 0;
		}
	}
	MPI_Finalize();
	return 0;
}
