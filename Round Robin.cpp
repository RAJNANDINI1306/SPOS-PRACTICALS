#include <iostream> 
using namespace std; 

void findWaitingTime(int processes[], int n, int bt[], int wt[], int quantum) 
{  
    int rem_bt[n]; 
    for (int i = 0; i < n; i++) 
        rem_bt[i] = bt[i]; 
    int t = 0; 

    while (true) 
    { 
        bool done = true; 
        for (int i = 0; i < n; i++) 
        { 
            if (rem_bt[i] > 0) 
            { 
                done = false; 
                if (rem_bt[i] > quantum) 
                { 
                    t += quantum; 
                    rem_bt[i] -= quantum; 
                } 
                else
                { 
                    t = t + rem_bt[i]; 
                    wt[i] = t - bt[i]; 
                    rem_bt[i] = 0; 
                } 
            } 
        } 
        if (done == true) 
            break; 
    } 
} 

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) 
{ 
    for (int i = 0; i < n; i++) 
    {
        tat[i] = bt[i] + wt[i]; 
    }
} 
 
void findavgTime(int processes[], int n, int bt[], int quantum) 
{ 
    int wt[n], tat[n], total_wt = 0, total_tat = 0; 
    findWaitingTime(processes, n, bt, wt, quantum); 
    findTurnAroundTime(processes, n, bt, wt, tat); 

    cout << "PN\t" << "BT\t" << "WT\t" << "TAT\n"; 
    for (int i = 0; i < n; i++) 
    { 
        total_wt += wt[i]; 
        total_tat += tat[i]; 
        cout << " " << i + 1 << "\t" << bt[i] << "\t" << wt[i] << "\t" << tat[i] << endl; 
    } 
    cout << "Average waiting time = " << (float)total_wt / n << endl; 
    cout << "Average turn around time = " << (float)total_tat / n << endl; 
} 

int main() 
{ 
    int n, quantum;
    cout << "Enter the number of processes: ";
    cin >> n;

    int processes[n], burst_time[n];
    for (int i = 0; i < n; i++) 
    {
        processes[i] = i + 1;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> burst_time[i];
    }

    cout << "Enter the quantum time: ";
    cin >> quantum;

    findavgTime(processes, n, burst_time, quantum); 
    return 0; 
}

