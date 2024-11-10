#include <iostream>
using namespace std;

int main() {
    int A[100][4];
    int i, j, n, total = 0, index, temp;
    float avg_wt, avg_tat;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter Burst Time:" << endl;
    for (i = 0; i < n; i++) {
        cout << "P" << i + 1 << ": ";
        cin >> A[i][1];
        A[i][0] = i + 1;
    }

    // Sorting the processes based on Burst Time
    for (i = 0; i < n; i++) {
        index = i;
        for (j = i + 1; j < n; j++) {
            if (A[j][1] < A[index][1]) {
                index = j;
            }
        }
        // Swapping Burst Time and process number
        temp = A[i][1];
        A[i][1] = A[index][1];
        A[index][1] = temp;

        temp = A[i][0];
        A[i][0] = A[index][0];
        A[index][0] = temp;
    }

    // Calculating Waiting Time
    A[0][2] = 0;  // First process has zero waiting time
    for (i = 1; i < n; i++) {
        A[i][2] = 0;
        for (j = 0; j < i; j++) {
            A[i][2] += A[j][1];
        }
        total += A[i][2];
    }
    avg_wt = (float)total / n;

    // Reset total for Turnaround Time calculation
    total = 0;
    cout << "P\tBT\tWT\tTAT" << endl;
    
    // Calculating Turnaround Time and displaying results
    for (i = 0; i < n; i++) {
        A[i][3] = A[i][1] + A[i][2];
        total += A[i][3];
        cout << "P" << A[i][0] << "\t" << A[i][1] << "\t" << A[i][2] << "\t" << A[i][3] << endl;
    }
    avg_tat = (float)total / n;

    cout << "Average Waiting Time : " << avg_wt << endl;
    cout << "Average Turnaround Time : " << avg_tat << endl;

    return 0;
}

