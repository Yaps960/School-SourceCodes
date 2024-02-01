#include <iostream>

using namespace std;

void print(int numProcess, int arrTime[], int burTime[], int Priority[], int quantumTime, int CTime[], int TurnTime[], int WaitTime[], int choice);
void details(int choice, int numProcess, int arrTime[], int burTime[], int Priority[], int *quantumTime);
void calculateTurnAndWait(int arrTime[], int burTime[], int CTime[], int WaitTime[], int TurnTime[], int numProcess);
int HighestBurtime(int *burTime, int numProcess);

int main()
{
    int exitFlag = 0;
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
        if(choice >= 1 && choice <=3){
            do{
            cout << "Number of Processes: ";
            cin >> numProcess;
            }while(!numProcess || numProcess <= 0);
        }
            int arrTime[numProcess], burTime[numProcess], Priority[numProcess], CTime[numProcess], TurnTime[numProcess], WaitTime[numProcess];
            int quantumTime, lowest, done;
            int tick = 0, mew = 0;
            int copyBurTime[numProcess];
        if(choice >= 1 && choice <=3){
            details(choice, numProcess, arrTime, burTime, Priority, &quantumTime);
            for(int i = 0; i < numProcess; i++){
                copyBurTime[i] = burTime[i];
            }
        }
        copyBurTime[numProcess] = 9999;
        switch (choice)
        {
        case 1:
            do
            {
                lowest = numProcess;
                for(int i=0; i<numProcess; i++)
                {
                    if(arrTime[i]<=tick && copyBurTime[i]< copyBurTime[lowest] && copyBurTime[i]>0 )
                        lowest=i;
                }
                copyBurTime[lowest]--;
                
                if(copyBurTime[lowest] == 0){
                    mew++;
                    done = tick + 1;
                    CTime[lowest] = done;
                }
                tick++;
            }while(mew!=numProcess);
            calculateTurnAndWait(arrTime, burTime, CTime, WaitTime, TurnTime, numProcess);
            print(numProcess, arrTime, burTime, Priority, quantumTime, CTime, TurnTime, WaitTime, choice);
            break;
        case 2:
            do{
                lowest = numProcess;
                for(int i=0; i<numProcess; i++)
                {
                    if(arrTime[i] <= tick && Priority[i]<Priority[lowest] && copyBurTime[i]>0 )
                        lowest=i;
                }
                copyBurTime[lowest]--;

                if(copyBurTime[lowest]==0)
                {
                    mew++;
                    done=tick + 1;
                    CTime[lowest] = done;
                }
                tick++;
            }while(mew != numProcess);
            calculateTurnAndWait(arrTime, burTime, CTime, WaitTime, TurnTime, numProcess);
            print(numProcess, arrTime, burTime, Priority, quantumTime, CTime, TurnTime, WaitTime, choice);
            break;
        case 3:
            break;
        case 4:
            exitFlag = 1;
            break;
        }
    } while (exitFlag != 1);

    return 0;
}




void print(int numProcess, int arrTime[], int burTime[], int Priority[], int quantumTime, int CTime[], int TurnTime[], int WaitTime[], int choice){
    double aveWait, aveTurn;
    cout << "Process" << "\t" << "Arrival Time" << "\t" << "Burst Time" << "\t";
    if(choice == 2)
        cout << "Priority Level";
    cout << "\t" << "Waiting Time" << "\t" << "Turnaround Time" << "\t"<<"Completion Time" << endl;
    if(choice == 3)
        cout << "Quantum Time = " << quantumTime;
    for(int i=0; i<numProcess; i++)
    {
        cout << "p" << i << "\t\t" << arrTime[i] << "\t\t" << burTime[i] << "\t\t";
        if(choice == 2)
            cout << Priority[i] << "\t\t";
        cout << WaitTime[i] << "\t\t" << TurnTime[i] << "\t\t" << CTime[i] << endl;
        aveWait = aveWait + WaitTime[i];
        aveTurn = aveTurn + TurnTime[i];
    }
    cout << "\nAverage Turnaround Time = " << aveTurn/numProcess << "m/s";
    cout << "\nAverage Waiting Time = " << aveWait/numProcess << "m/s\n\n";
}




void details(int choice, int numProcess, int arrTime[], int burTime[], int Priority[], int *quantumTime){
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




void calculateTurnAndWait(int arrTime[], int burTime[], int CTime[], int WaitTime[], int TurnTime[], int numProcess){
    for(int i = 0; i < numProcess; i++)
        TurnTime[i] = CTime[i] - arrTime[i];
    for(int i = 0; i < numProcess; i++)
        WaitTime[i] = TurnTime[i] - burTime[i];
}
