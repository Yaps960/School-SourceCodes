//kulang: error handling, do while
//mewing bye bye, array error, CHECKED
//parameter, ipapasa pointer ng array

#include <iostream>

using namespace std;

int WaitingTime();
int TurnAroundTime();
int Menu();
void details(int choice, int numProcess);
void banner();
void SRTF();
void PS();
void RR();

int main(){
    int numProcess;
	int choice = Menu();
    if(choice == 1)
		cout << "Shortest Remaining Time First\n";
    else if(choice == 2)
		cout << "Priority Scheduling\n";
    else if(choice == 3)
		cout << "Round Robin\n";
    if(choice == 1 || (choice == 2 || choice == 3)){
        cout << "Number of Processes: ";
        cin >> numProcess;
        int mew[numProcess];
        int arrTime[numProcess];
        int burTime[numProcess];
        int Priority[numProcess];
        details(choice, numProcess);
        for(int i = 0; i < sizeof(mew) / sizeof(mew[0]); i++){
            cout << i << '\n';
        }
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

void details(int choice, int numProcess){
	for(int i = 0; i < numProcess; i++){
		cout << "Process #" << i+1 << '\n';
		cout << "Arrival Time: ";
		cin >> arrTime;
		cout << "Burst Time: ";
		cin >> burTime
		if(choice == 2){
			cout << "Priority: ";
			cin >> Priority;
		}
		cout << '\n';
	}
}

void SRTF(){
}
