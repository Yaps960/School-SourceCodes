#include <iostream>
#include <conio.h>
#define MAX_INT 2147483647

using namespace std;

// CHECKLIST
// Loop - Done
// User Inputs - DONE
// SRTF
// PS
// Round Robin
void details(int choice, int numProcess, int *arrTime, int *burTime, int *Priority, int *quantumTime);
void print(int numProcess, int *arrTime, int *burTime, int *Priority, int *quantumTime, int *CTime, int *TurnTime, int *WaitTime, int choice);

int main()
{
    bool exitFlag = false;
    int choice;
    do
    {
        cout << "1. Shortest Remaining Time First\n2. Priority Scheduling\n3. Round Robin\n4. Exit\nEnter your option: ";
        cin >> choice;
        if (choice < 1 || choice > 4 || !choice)
        {
            cout << "Invalid Input\n";
            cin.clear();
            cin.ignore();
        }
        cout << '\n';
        int numProcess;

        do{
        cout << "Number of Processes: ";
        cin >> numProcess;
        }while(!numProcess || numProcess <= 0);

        int arrTime[numProcess];
        int burTime[numProcess];
        int Priority[numProcess];
        int CTime[numProcess];
        int TurnTime[numProcess];
        int WaitTime[numProcess];
        int quantumTime;
        int burstRemaining, lowest, done;
        int tick = 0;
        details(choice, numProcess, arrTime, burTime, Priority, &quantumTime);
        int copyBurTime[numProcess];
        for(int i = 0; i < numProcess; i++){
            copyBurTime[i] = burTime[i];
        }
        switch (choice)
        {
        case 1:
            do{
                burstRemaining = 0;
                lowest = MAX_INT;
                for(int i=0; i<numProcess; i++)
                {
                    if(arrTime[i]<=tick && copyBurTime[i]<lowest && copyBurTime[i]>0 )
                        lowest=i;
                }
                copyBurTime[lowest]--;
                
                if(copyBurTime[lowest] == 0){
                    done = tick + 1;
                    CTime[lowest] = end;
                    TurnTime[lowest] = CTime[lowest] - arrTime[lowest];
                    WaitTime[lowest] = TurnTime[lowest] - burTime[lowest];
                }

                for(int i = 0; i < numProcess; i++){
                    burstRemaining += copyBurTime[i];
                }
            }while(burstRemaining != 0);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            exitFlag = true;
            break;
        }
    } while (!exitFlag);

    return 0;
}

void details(int choice, int numProcess, int *arrTime, int *burTime, int *Priority, int *quantumTime)
{
    for (int i = 0; i < numProcess; i++)
    {
        cout << "Process #" << i + 1 << '\n';
        cout << "Arrival Time: ";
        cin >> arrTime[i];
        cout << "Burst Time: ";
        cin >> burTime[i];
        if (choice == 2)
        {
            cout << "Priority: ";
            cin >> Priority[i];
        }
        cout << '\n';
    }
    if (choice == 3)
    {
        int highestBurTime = burTime[0];
        for (int i = 1; i < numProcess; i++)
        {
            if (highestBurTime < burTime[i])
                highestBurTime = burTime[i];
        }
        do
        {
            cout << "Quantum Time: ";
            cin >> *quantumTime;
            if (*quantumTime > highestBurTime)
            {
                cout << "Invalid Input\n";
                cin.clear();
                cin.ignore();
            }
        } while (!*quantumTime || *quantumTime > highestBurTime);
    }
}

void print(int numProcess, int *arrTime, int *burTime, int *Priority, int *quantumTime, int *CTime, int *TurnTime, int *WaitTime, int choice){
    int aveWait = 0, aveTurn = 0;
    cout<<"Process"<<"\t"<< "Burst Time"<<"\t"<<"Arrival Time" <<"\t";
    if(choice == 2){
        cout << "Priority Level";
    }
    cout << "\t" << "Waiting Time" <<"\t"<<"Turnaround Time"<< "\t"<<"Completion Time"<<endl;
    if(choice == 3){
        cout << "Quantum Time = " << quantumTime;
    }
    for(i=0; i<numProcess; i++)
    {
        cout<<"p"<<i<<"\t\t"<<burTime[i]<<"\t\t"<<arrTime[i]<<"\t\t"<<WaitTime[i]<<"\t\t"<<TurnTime[i]<<"\t\t"<<CTime[i]<<endl;
        aveWait = aveWait + WaitTime[i];
        aveTurn = aveTurn + TurnTime[i];
    }
    cout
}




/*
GENERAL ALGORITHM
1. Search for the lowest and second lowest arrival time
2. Compare the burst time with those arrival times
3. If second arrival time is more than burst time, burst time set to 0
4. Else, burst time - (second lowest arrival - lowest arrival)
5. If arrival time not completely traversed, Completion Time += arrival time
6. Else, Comlpetion time += burst time
7. If burst time is 0, completion time of that process = current value of completion time
8. Repeat step 1 where second lowest is the lowest now
9. Turn Around Time = Completion Time - Arrival Time
10. Waiting Time = Turn Around Time - Burst Time
11. Average step 9 and 10 individually
*/

//ALGORITHM SRTF

//First Lowest
int minArr(int arrTime[], int numProcess)
{
    int lowest = arrTime[0];
    for(int i; i < numProcess; i++){
        if(lowest > arrTime[i]){
            lowest = arrTime[i];
        }
    }
    return lowest;
}

//Second Lowest
int secondMin(int arrTime[], int numProcess, int lowest){
    int secondLowest = arrTime[0];
    for(int i; i < numProcess; i++){
        if(secondLowest > arrTime[i] && arrTime[i] > lowest){
            secondLowest = arrTime[i];
        }
    }
    return secondLowest;
}

int maxArr(int arrTime[], int numProcess)
{
    int highest = arrTime[0];
    for(int i; i < numProcess; i++){
        if(highest < arrTime[i]){
            highest = arrTime[i];
        }
    }
    return highest;
}


void PS()
{
}

void RR(int *arrTime, int *burTime, int *Ctime,int *WTime, int *TATime, int numProcess, int *quantum, int time, int lowest, int highest) {
    int executeTime;

    while (true) {
        bool processComplete = true;

        for (int i = 0; i < numProcess; i++) {
            if (burTime[i] > 0) {
                processComplete = false;

                if (burTime[i] < *quantum) {
                    executeTime = burTime[i];
                } else {
                    executeTime = *quantum;
                }

                burTime[i] -= executeTime;

                time += executeTime;
                Ctime[i] = time;

                if (lowest == -1) {
                    lowest = minArr(arrTime, numProcess);
                    highest = maxArr(arrTime, numProcess);
                }

                int secondLowest = secondMin(arrTime, numProcess, lowest);

                if (arrTime[secondLowest] >= burTime[lowest]) {
                    executeTime = burTime[secondLowest];
                    burTime[lowest] = 0;
                } else {
                    executeTime = arrTime[secondLowest] - time;
                    burTime[lowest] -= executeTime;
                }

                WTime[i] = time - arrTime[i] - executeTime;
                TATime[i] = time - arrTime[i];

                RR(arrTime, burTime, Ctime, WTime, TATime, numProcess, quantum, time, lowest, highest);

                
            }
        }

        if (processComplete) {
            break;
        }
    }
}
