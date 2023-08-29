#include <iostream>
using namespace std;

int main()
{
	//defining n and m
	const int numP = 5; //n
	const int numR = 3; //m

	//current system snapshot
	int available[numR] = { 3, 3, 2 };
	int max[numP][numR] = {
		{7, 5, 3},
		{3, 2, 2},
		{9, 0, 2},
		{2, 2, 2},
		{4, 3, 3} };
	int allocation[numP][numR] = {
		{0, 1, 0},
		{2, 0, 0},
		{3, 0, 2},
		{2, 1, 1},
		{0, 0, 2} };

	//populating need
	int need[numP][numR];
	for (int i = 0; i < numP; i++)
	{
		for (int k = 0; k < numR; k++)
		{
			need[i][k] = max[i][k] - allocation[i][k];
		}
	}

	//setting up safety algorithm
	int index = 0;
	int order[numP] = { -1, -1, -1, -1, -1 };
	int work[numR];
	bool interlock = 1;
	bool finish[numP];

	for (int i = 0; i < numR; i++)
	{
		work[i] = available[i];
	}
	for (int i = 0; i < numP; i++)
	{
		finish[i] = 0;
	}

	//implementing safety algorithm
	for (int y = 0; y < numP; y++) //looping numP times ensures that even in worse case, the safe order can be found
	{
		for (int i = 0; i < numP; i++)
		{
			cout << "Testing P" << i << endl;

			for (int j = 0; j < numR; j++)
			{
				//ensure that this process has not been chosen yet
				if (finish[i] == 0)
				{
					interlock = 0;

					for (int k = 0; k < numR; k++)
					{
						cout << "	Testing R" << j << endl;

						//ensure that need < avaiable
						if (need[i][k] > available[k])
						{
							cout << "		P" << i << " R" << j << " requires more resources" << endl;
							interlock = 1;
							break;
						}
					}

					if (interlock == 0)
					{
						order[index++] = i;

						cout << "		Process " << i << " completed." << endl;

						for (int k = 0; k < numR; k++)
						{
							available[k] += allocation[i][k];
							finish[i] = 1;
						}
					}
				}
			}
		}
	}	

	//testing the decided order for safeness
	for (int i = 0; i < numP; i++)
	{
		if (finish[i] == 0)
		{
			cout << "The system is not safe" << endl;
			interlock = 0;
			break;
		}
	}

	if (interlock == 0)
	{
		cout << "The system has a safe order of proccesses." << endl;
		for (int i = 0; i < numP; i++)
		{
			cout << order[i] << ", ";
		}
	}

	return 0;
}