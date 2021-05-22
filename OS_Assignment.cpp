#include <iostream>
#include <vector>

#define Vect2D vector<vector<int>>
int NumOfProcesses;
int NumOfResources;

using namespace std;


void input2DMatrix(Vect2D& vect)
{
	for (int row = 0; row < NumOfProcesses; row++)
	{
		for (int col = 0; col < NumOfResources; col++)
			cin >> vect[row][col];
	}
}


void print(const Vect2D v)
{
	for (int i = 0; i < NumOfProcesses; i++)
	{
		cout << "P" << i << "   ";
		for (int j = 0; j < NumOfResources; j++)
			cout << v[i][j] << "  ";
		cout << endl;
	}
}


void CalcNeed(Vect2D & need, Vect2D max, Vect2D allocation)
{
	for (int i = 0; i < NumOfProcesses; i++)
	{
		for (int j = 0; j < NumOfResources; j++)
			need[i][j] = max[i][j] - allocation[i][j];
	}
}


bool CheckSafe(Vect2D need, Vect2D allocation, vector<int> work, vector<int> &Sequence)
{
	int count = 0;
	vector<bool> finish(NumOfProcesses, false);			//Each P init. to false
	bool column_flag;

	while (count < NumOfProcesses) {

		for (int i = 0; i < NumOfProcesses; i++) {
			if (finish[i] == true)
				continue; 				// Process already finished

			column_flag = true;
			for (int j = 0; j < NumOfResources; j++) {
				if (need[i][j] > work[j]) {
					column_flag = false;
					break;
				}
			}

			if (column_flag == true) {
				finish[i] = true;
				Sequence.push_back(i);
				for (int col = 0; col < NumOfResources; col++)
					work[col] += allocation[i][col];
			}
		}
		count++;
	}

	for (int i = 0; i < NumOfProcesses - 1; i++) {
		if (finish[i] == false) {
			cout << " No , Not in a safe state \n";
			return false;
		}
	}

	return true;
}

void Request(int Process, vector<int> REQ, vector<int> available, Vect2D need, Vect2D allocation , vector<int> &Sequence )
{
	for (int col = 0; col < NumOfResources; col++)
	{
		if (REQ[col] > need[Process][col])
		{
			cout << "Process exceeds maximum claim \n";
			return;
		}

		if (REQ[col] > available[col]) 		// Wait state --> UNSAFE
		{
			cout << "Request can't be granted \n";
			return;
		}
	}


	for (int col = 0; col < NumOfResources; col++)
	{
		available[col] -= REQ[col];
		allocation[Process][col] += REQ[col];
		need[Process][col] -= REQ[col];
	}

	if (CheckSafe(need, allocation, available, Sequence))
	{
			cout << "Yes request can be granted with safe state, Safe state <P"<<Process<<" req, ";
			for (int i = 0; i < NumOfProcesses - 1; i++)
				cout << "P" << Sequence[i] << ",";
			cout << "P" << Sequence[NumOfProcesses - 1] << "> \n";
	}
}


int main()
{
	int NewInput;
	do {
		cout << "Enter number of Processes\n";
		cin >> NumOfProcesses;

		cout << "Enter number of Resources\n";
		cin >> NumOfResources;

		/*	Allocated Resources for each process  */
		vector <vector<int>> Allocation(NumOfProcesses, vector<int>(NumOfResources, 0));

		/*	Max Resources need for each process	 */
		vector <vector<int>> Max(NumOfProcesses, vector<int>(NumOfResources, 0));

		vector<int> Available(NumOfResources);

		cout << "Enter Allocated Matrix : \n";
		input2DMatrix(Allocation);

		cout << "Enter Max Matrix : \n";
		input2DMatrix(Max);

		cout << "Enter Available Matrix : \n";
		for (int col = 0; col < NumOfResources; col++)
			cin >> Available[col];



		/* Needed amount of resources for each process */
		vector<vector<int>> Need(NumOfProcesses, vector<int>(NumOfResources, 0));
		cout << "NEED Matrix : \n     ";
		for (int i = 0; i < NumOfResources; i++)
			cout << "R" << i << " ";
		cout << "\n";
		CalcNeed(Need, Max, Allocation);
		print(Need);

		vector<int> Sequence;

		cout << "Enter '1' to enquire if the system is in a safe state \n";
		cout << "Enter '2' to enquire if a certain immediate request by one of the processes can be granted \n ";

		int option;
		cin >> option;
		if (option == 1) {
			/* Check Safe condition */
			if (CheckSafe(Need, Allocation, Available, Sequence))
			{
				cout << "Yes , Safe state <";
				for (int i = 0; i < NumOfProcesses - 1; i++)
					cout << "P" << Sequence[i] << ",";
				cout << "P" << Sequence[NumOfProcesses - 1] << "> \n";
			}
		}

		else if (option == 2) {
			int Process;
			vector <int> Req(4);
			cout << "Enter Process No. \n";
			cin >> Process;
			cout << "Enter instances of Resources needed for request \n";
			for (int i = 0; i < NumOfResources; i++)
				cin >> Req[i];
			Request(Process, Req, Available, Need, Allocation, Sequence);
		}
		cout << "Enter 1 for new input and 0 if you'd like to exit \n";
		cin >> NewInput;

	} while (NewInput == 1);


	system("pause");
	return 0;
}
