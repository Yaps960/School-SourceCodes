#include <iostream>
#include <fstream>

using namespace std;

void print(int numProcess, char Process[], int arrTime[], int burTime[], int Priority[], int quantumTime, int CTime[], int TurnTime[], int WaitTime[], int choice, char ganttProcess[], int ganttValue[], int count);
void details(int choice, int numProcess, int arrTime[], int burTime[], int Priority[], int &quantumTime);
void calculateTurn(int arrTime[], int CTime[], int TurnTime[], int numProcess, int index);
void calculateWait(int TurnTime[], int burTime[], int WaitTime[], int numProcess, int index);
void roundRobin(char Process[], char ganttProcess[], int ganttValue[], int quantum, int n, int arrTime[], int burTime[], int copyBurTime[], int WaitTime[], int TurnTime[], int CTime[], int tick, int time, int count, int& counter);
void SortArrival(char Process[], int arrTime[], int burTime[], int copyBurTime[], int numProcess);
void SortProcess(char Process[], int arrTime[], int burTime[], int numProcess);
void writeArraysToFile(string filename, char process[], int arrival[], int burst[], int priority[], int quantum, int n, int choice);
void readArraysFromFile(string filename);

int main()
{
    int exitFlag = 0;
    int choice;
    do
    {
        cout << "1. Shortest Remaining Time First\n2. Priority Scheduling\n3. Round Robin\n4. History File\n5. Exit\nEnter your option: ";
        cin >> choice;
        if (choice < 1 || choice > 5 || !choice)
        {
            cout << "Invalid Input\n";
            cin.clear();
            cin.ignore();
        }
        cout << '\n';
        int numProcess;
        if (choice >= 1 && choice <= 3)
        {
            do
            {
                cout << "Number of Processes: ";
                cin >> numProcess;
            } while (!numProcess || numProcess <= 0);
        }
        int arrTime[numProcess], burTime[numProcess], Priority[numProcess], CTime[numProcess], TurnTime[numProcess], WaitTime[numProcess];
        int quantumTime, lowest, done, completion[numProcess], count = 0, ganttValue[100];
        char Process[numProcess], ganttProcess[100];
        string filename[] = {"srtf.txt", "priority.txt", "roundrobin.txt"};
        int filenum;
        for (int i = 0; i < numProcess; i++)
        {
            if (65 + i > 90)
                Process[i] = 71 + i;
            else
                Process[i] = 65 + i;
        }
        int tick = 0, mew = 0;
        int copyBurTime[numProcess];
        if (choice >= 1 && choice <= 3)
        {
            details(choice, numProcess, arrTime, burTime, Priority, quantumTime);
            for (int i = 0; i < numProcess; i++)
                copyBurTime[i] = burTime[i];
        }
        copyBurTime[numProcess] = 9999;
        switch (choice)
        {
            case 1:
                do
                {
                    lowest = numProcess;
                    for (int i = 0; i < numProcess; i++)
                    {
                        if (arrTime[i] <= tick && copyBurTime[i] < copyBurTime[lowest] && copyBurTime[i] > 0){
                            lowest = i;
                        }else if(tick < arrTime[i])
                            break;
                    }
                    copyBurTime[lowest]--;

                    if (copyBurTime[lowest] == 0)
                    {
                        mew++;
                        done = tick + 1;
                        CTime[lowest] = done;
                    }
                    tick++;
                    if(lowest!=numProcess){
                        ganttValue[count] = tick; 
                        ganttProcess[count] = Process[lowest];
                        count++;
                    }
                } while (mew != numProcess);
                calculateTurn(arrTime, CTime, TurnTime, numProcess, 0);
                calculateWait(TurnTime, burTime, WaitTime, numProcess, 0);
                print(numProcess, Process, arrTime, burTime, Priority, quantumTime, CTime, TurnTime, WaitTime, choice, ganttProcess, ganttValue, count);
                writeArraysToFile("srtf.txt", Process, arrTime, burTime, Priority, quantumTime, numProcess, choice);
                break;
            case 2:
                do
                {
                    lowest = numProcess;
                    for (int i = 0; i < numProcess; i++)
                    {
                        if (arrTime[i] <= tick && Priority[i] < Priority[lowest] && copyBurTime[i] > 0)
                            lowest = i;
                    }
                    copyBurTime[lowest]--;

                    if (copyBurTime[lowest] == 0)
                    {
                        mew++;
                        done = tick + 1;
                        CTime[lowest] = done;
                    }
                    tick++;
                    if(lowest!=numProcess){
                        ganttValue[count] = tick; 
                        ganttProcess[count] = Process[lowest];
                        count++;
                    }
                } while (mew != numProcess);
                calculateTurn(arrTime, CTime, TurnTime, numProcess, 0);
                calculateWait(TurnTime, burTime, WaitTime, numProcess, 0);
                print(numProcess, Process, arrTime, burTime, Priority, quantumTime, CTime, TurnTime, WaitTime, choice, ganttProcess, ganttValue, count);
                writeArraysToFile("priority.txt", Process, arrTime, burTime, Priority, quantumTime, numProcess, choice);
                break;
            case 3:
                SortArrival(Process, arrTime, burTime, copyBurTime, numProcess);
                roundRobin(Process, ganttProcess, ganttValue, quantumTime, numProcess, arrTime, burTime, copyBurTime, WaitTime, TurnTime, CTime, tick, 0, 0, count);
                SortProcess(Process, arrTime, burTime, numProcess);
                print(numProcess, Process, arrTime, burTime, Priority, quantumTime, CTime, TurnTime, WaitTime, choice, ganttProcess, ganttValue, count);
                writeArraysToFile("roundrobin.txt", Process, arrTime, burTime, Priority, quantumTime, numProcess, choice);
                break;
            case 4:
                cout << "From File\n1 - SRTF\n2 - Priority\n3 - Round Robin\nEnter your option: ";
                cin >> filenum;
                readArraysFromFile(filename[filenum-1]);
                break;
            
            case 5:
                cout << "\nMembers:\nColoma, Carl Joshua\nMercado, Raphael Andre\nVillarina, Dinah Chrishalei\nYapan, Von Emil\nThank you!";
                exitFlag = 1;
                break;
        }
    }while(exitFlag != 1);

    return 0;
}

void print(int numProcess, char Process[], int arrTime[], int burTime[], int Priority[], int quantumTime, int CTime[], int TurnTime[], int WaitTime[], int choice, char ganttProcess[], int ganttValue[], int count)
{
    double aveWait = 0, aveTurn = 0;
    if (choice == 3)
        cout << "Quantum_Time = " << quantumTime << endl;
    cout << "*=======*===============*===============*===============*===============*===============*";
    if(choice == 2)
        cout << "===============*\n";
    else
        cout << "\n";
    cout << "|Process|  Arrival Time |   Burst Time  |  Waiting Time |Turnaround Time|Completion Time|";
    if(choice == 2)
        cout << " Priority Level|";
    cout << endl;
    for (int i = 0; i < numProcess; i++)
    {
        cout << "|-------|---------------|---------------|---------------|---------------|---------------|";
        if(choice == 2)
        cout << "---------------|\n";
        else
        cout << "\n";
        cout << "|   " 
             << Process[i]
             << " \t| \t"
             << arrTime[i]
             << " \t| \t"
             << burTime[i]
             << " \t| \t";
        cout << WaitTime[i]
             << " \t| \t"
             << TurnTime[i]
             << " \t| \t"
             << CTime[i]
             << " \t| \t";
        if (choice == 2)
            cout << Priority[i] << " \t|\n";
        else
            cout << "\n";
        aveWait = aveWait + WaitTime[i];
        aveTurn = aveTurn + TurnTime[i];
    }
    cout << "*=======*===============*===============*===============*===============*===============*";
    if(choice == 2)
        cout << "===============*";
    cout << "\nAverage Turnaround Time = " << aveTurn / numProcess << "m/s";
    cout << "\nAverage Waiting Time = " << aveWait / numProcess << "m/s\n\n";
    cout<<"Gantt Chart: "<<endl;
    for (int i=0; i<count; i++){
        if((ganttProcess[i] == ganttProcess[i+1] && i != count -1))
            continue;
        cout<<"\t|\t"<<ganttProcess[i];
    }
    cout<<"\t|"<<endl;
    cout<<"\t" << arrTime[0];
    for (int i=0; i<count; i++){
        if(ganttProcess[i] == ganttProcess[i+1] && i != count -1)
            continue;
        cout<<"\t\t"<<ganttValue[i];
    }
    cout << "\n\n";
}

void details(int choice, int numProcess, int arrTime[], int burTime[], int Priority[], int &quantumTime)
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
            cin >> quantumTime;
            if (quantumTime > highestBurTime)
            {
                cout << "Invalid Input\n";
                cin.clear();
                cin.ignore();
            }
        } while (!quantumTime || quantumTime > highestBurTime);
    }
}

void calculateTurn(int arrTime[], int CTime[], int TurnTime[], int numProcess, int index)
{
    if (index == numProcess)
        return;
    TurnTime[index] = CTime[index] - arrTime[index];
    calculateTurn(arrTime, CTime, TurnTime, numProcess, ++index);
}

void calculateWait(int TurnTime[], int burTime[], int WaitTime[], int numProcess, int index)
{
    if (index == numProcess)
        return;
    WaitTime[index] = TurnTime[index] - burTime[index];
    calculateWait(TurnTime, burTime, WaitTime, numProcess, ++index);
}

void roundRobin(char Process[], char ganttProcess[], int ganttValue[], int quantum, int n, int arrTime[], int burTime[], int copyBurTime[], int WaitTime[], int TurnTime[], int CTime[], int tick, int time, int count, int& counter){
    int queue[100];
    int front = 0, rear = 0;
    while (front != rear || count < n){
        for (int i = count; i < n ; i++){
            if (arrTime[i] <= tick){
                queue[rear] = i;
                rear = rear+1;
                count++;
            }
        }
    
    if (front != rear){
        int index = queue[front];
        front = front + 1;
        if (copyBurTime[index]<quantum){
            time=copyBurTime[index];
        }else{
            time=quantum;
        }
        copyBurTime[index] -= time;
        tick += time;
        ganttValue[counter] = tick;
        ganttProcess[counter] = Process[index];
        counter++;
        for (int i = count; i<n; i++){
            if (arrTime[i]<=tick){
                queue[rear] = i;
                rear = rear + 1;
                count++;
            }
        }
        if (copyBurTime[index]>0){
            queue[rear] = index;
            rear = rear + 1;
        }else if (copyBurTime[index] == 0){
            CTime[index] = tick;
            TurnTime[index] = CTime[index] - arrTime[index];
            WaitTime[index] = TurnTime[index] - burTime[index];            
        }
    }else{
        tick = arrTime[count];
        }
    }
}

void SortArrival(char Process[], int arrTime[], int burTime[], int copyBurTime[], int numProcess)
{
    for (int i = 0; i < numProcess - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < numProcess; j++)
        {
            if (arrTime[j] < arrTime[min])
                min = j;
        }
        if (min != i)
        {
            int temp = arrTime[min];
            int temp2 = Process[min];
            int temp3 = burTime[min];
            int temp4 = copyBurTime[min];
            arrTime[min] = arrTime[i];
            Process[min] = Process[i];
            burTime[min] = burTime[i];
            copyBurTime[min] = copyBurTime[i];
            arrTime[i] = temp;
            Process[i] = temp2;
            burTime[i] = temp3;
            copyBurTime[i] = temp4;
        }
    }
}

void SortProcess(char Process[], int arrTime[], int burTime[], int numProcess)
{
        for (int i = 0; i < numProcess - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < numProcess; j++)
        {
            if (int(Process[j]) < (Process[min]))
                min = j;
        }
        if (min != i)
        {
            int temp = arrTime[min];
            int temp2 = Process[min];
            int temp3 = burTime[min];
            arrTime[min] = arrTime[i];
            Process[min] = Process[i];
            burTime[min] = burTime[i];
            arrTime[i] = temp;
            Process[i] = temp2;
            burTime[i] = temp3;
        }
    }
}

void writeArraysToFile(string filename, char process[], int arrival[], int burst[], int priority[], int quantum, int n, int choice) {
    ofstream outputFile(filename.c_str(), ios::out | ios_base::app);
    if (outputFile.is_open()) {
        if (choice == 3)
            outputFile << "Quantum   ";
        outputFile << "Process   ArrivalTime   BurstTime";
        if (choice == 2)
            outputFile << " Priority";
        outputFile << endl;
        if(choice == 3)
            outputFile << quantum;
        for (int i = 0; i < n; i++) {
            if(choice == 3)
                outputFile << "           ";
            outputFile << process[i] << "         " << arrival[i] << "             " << burst[i];
            if (choice == 2)
                outputFile << "         " << priority[i];
            outputFile << endl;
        }
        outputFile.close();
        cout << "Arrays have been written to " << filename << endl;
    } else {
        cout << "Unable to open file " << filename << endl;
    }
}

void readArraysFromFile(string filename){
    ifstream inputFile(filename.c_str());

    if (!inputFile) {
        cerr << "Unable to open file." << endl;
        return;
    }

    string line;

    cout << endl;
    cout << "History of: " << filename << endl;
    while (getline(inputFile, line)) {
        cout << line << endl;
    }

    inputFile.close();
}
