//kulang: error handling, do while
//mewing bye bye, array error

#include <iostream>

using namespace std;

int WaitingTime();
int TurnAroundTime();
int Menu();
void details(int choice);
void banner();
void SRTF();
void PS();
void RR();

struct ProcessDetails{
	int numProcess;
	int arrTime;
	int burTime;
	int Priority;
}pro;

int main(){
	int *mew;
	int choice = Menu();
	switch(choice){
		case 1:
			cout << "Shortest Remaining Time First\n";
			cout << "Number of Processes: ";
			cin >> pro.numProcess;
			mew = new int[pro.numProcess];
			details(choice);
			break;
		case 2:
			cout << "Number of Processes: ";
			cin >> pro.numProcess;
			mew[pro.numProcess];
			cout << "Priority Scheduling\n";
			details(choice);
			break;
		case 3:
			cout << "Number of Processes: ";
			cin >> pro.numProcess;
			mew[pro.numProcess];
			cout << "Round Robin\n";
			details(choice);
			break;
	}
	
	for(int i = 0; i < sizeof(mew) / sizeof(mew[0]); i++){
		cout << i << '\n';
	}
	return 0;
}

int Menu(){
	banner();
	int choice;
	cout << "1. Shortest Remaining Time First\n2. Priority Scheduling\n3. Round Robin\nEnter your option: ";
	cin >> choice;
	cout << '\n';
	return choice;
}

void banner(){	
	cout << ".d8888.  .o88b. db   db d88888b d8888b. db    db db      d888888b d8b   db  d888b  \n";
	cout << "88'  YP d8P  Y8 88   88 88'     88  `8D 88    88 88        `88'   888o  88 88' Y8b \n";
	cout << "`8bo.   8P      88ooo88 88ooooo 88   88 88    88 88         88    88V8o 88 88      \n";
	cout << "  `Y8b. 8b      88~~~88 88~~~~~ 88   88 88    88 88         88    88 V8o88 88  ooo \n";
	cout << "db   8D Y8b  d8 88   88 88.     88  .8D 88b  d88 88booo.   .88.   88  V888 88. ~8~ \n";
	cout << "`8888Y'  `Y88P' YP   YP Y88888P Y8888D' ~Y8888P' Y88888P Y888888P VP   V8P  Y888P  \n\n";
}

void details(int choice){
	for(int i = 0; i < pro.numProcess; i++){
		cout << "Process #" << i+1 << '\n';
		cout << "Arrival Time: ";
		cin >> pro.arrTime;
		cout << "Burst Time: ";
		cin >> pro.burTime;
		if(choice == 2){
			cout << "Priority: ";
			cin >> pro.Priority;
		}
		cout << '\n';
	}
}

void SRTF(){
}
