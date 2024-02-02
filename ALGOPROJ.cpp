#include <iostream>

using namespace std;

void print(int numProcess, char Process[], int arrTime[], int burTime[], int Priority[], int quantumTime, int CTime[], int TurnTime[], int WaitTime[], int choice);
void details(int choice, int numProcess, int arrTime[], int burTime[], int Priority[], int *quantumTime);
void calculateTurn(int arrTime[], int CTime[], int TurnTime[], int numProcess, int index);
void calculateWait(int TurnTime[], int burTime[], int WaitTime[], int numProcess, int index);
void SortArrival(int Process[], int arrTime[], int numProcess);
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
            int quantumTime, lowest, done, gantt[30];
            char Process[numProcess];
            for(int i = 0; i <numProcess; i++){
                if(65+i > 90)
                Process[i] = 71 + i;
                else
                Process[i] = 65 + i;
            }
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
            calculateTurn(arrTime, CTime, TurnTime, numProcess, 0);
            calculateWait(TurnTime, burTime, WaitTime, numProcess, 0);
            print(numProcess, Process, arrTime, burTime, Priority, quantumTime, CTime, TurnTime, WaitTime, choice);
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
            calculateTurn(arrTime, CTime, TurnTime, numProcess, 0);
            calculateWait(TurnTime, burTime, WaitTime, numProcess, 0);
            print(numProcess, Process, arrTime, burTime, Priority, quantumTime, CTime, TurnTime, WaitTime, choice);
            break;
        case 3:
            SortArrival(Process, arrTime, numProcess);
            
            break;
        case 4:
            exitFlag = 1;
            break;
        }
    } while (exitFlag != 1);

    return 0;
}




void print(int numProcess, char Process[], int arrTime[], int burTime[], int Priority[], int quantumTime, int CTime[], int TurnTime[], int WaitTime[], int choice){
    double aveWait, aveTurn;
    if(choice == 3)
        cout << "Quantum_Time = " << quantumTime << endl;
    cout << "Process" << "\t" << "Arrival_Time" << "\t" << "Burst_Time" << "\t";
    if(choice == 2)
        cout << "Priority_Level" << "\t";
    cout << "Waiting_Time" << "\t" << "Turnaround_Time" << "\t"<<"Completion_Time" << endl;
    for(int i=0; i<numProcess; i++)
    {
        cout << Process[i] << "\t\t" << arrTime[i] << "\t\t" << burTime[i] << "\t\t";
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




void calculateTurn(int arrTime[], int CTime[], int TurnTime[], int numProcess, int index){
    if(index==numProcess)
        return;
    TurnTime[index] = CTime[index] - arrTime[index];
    calculateTurn(arrTime, CTime, TurnTime, numProcess, ++index);
}




void calculateWait(int TurnTime[], int burTime[], int WaitTime[], int numProcess, int index){
    if(index==numProcess)
        return;
    WaitTime[index] = TurnTime[index] - burTime[index];
    calculateWait(TurnTime, burTime, WaitTime, numProcess, ++index);
}




void SortArrival(int Process[], int arrTime[], int numProcess){
    for (int i = 0; i < numProcess-1; i++){
        int min = i;
        for (int j = i+1; j< numProcess; j++){
            if (arrTime[j]<arrTime[min])
                min=j;
        }
        if (min!=i){
            int temp=arrTime[min];
            int temp2=Process[min];
            arrTime[min] = arrTime[i];
            Process[min] = Process[i];
            arrTime[i] = temp;
            Process[i] = temp2;
        }
    }
}
