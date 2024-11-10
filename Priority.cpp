#include <iostream>
#include <vector>
using namespace std;

struct Process {
    int id, arrival_time, burst_time, priority, completion_time, waiting_time, turnaround_time;
};

void PriorityNonPreemptive(vector<Process>& processes) {
    int current_time = 0, completed = 0;
    vector<bool> is_completed(processes.size(), false);
    float total_wt=0,total_tat=0;
    
    while (completed != processes.size()) {
        int idx = -1, highest_priority = 1e9;

        for (int i = 0; i < processes.size(); ++i) {
            if (!is_completed[i] && processes[i].arrival_time <= current_time && 
                (processes[i].priority < highest_priority || 
                (processes[i].priority == highest_priority && processes[i].arrival_time < processes[idx].arrival_time))) {
                
                highest_priority = processes[i].priority;
                idx = i;
            }
        }

        if (idx != -1) {
            current_time += processes[idx].burst_time;
            processes[idx].completion_time = current_time;
            processes[idx].turnaround_time = current_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
            
            total_wt = total_wt + processes[idx].waiting_time;
            total_tat = total_tat + processes[idx].turnaround_time;
            is_completed[idx] = true;
            completed++;
        } else {
            current_time++;
        }
    }
	 
     cout << "\nProcess\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n";
     for (int i = 0; i < processes.size(); ++i) {
        cout << "P" << processes[i].id << "\t\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t" 
             << processes[i].priority << "\t\t" << processes[i].completion_time << "\t\t" 
             << processes[i].turnaround_time << "\t\t" << processes[i].waiting_time << endl;
    }
    cout<<"Average Waiting Time : "<<total_wt / processes.size()<<endl;
    cout<<"Avearge Turnaround Time : "<<total_tat / processes.size();
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> processes(n);

    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time, burst time, and priority of process P" << i + 1 << ": ";
        cin >> processes[i].arrival_time >> processes[i].burst_time >> processes[i].priority;
    }

    PriorityNonPreemptive(processes);
    return 0;
}

