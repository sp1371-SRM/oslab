// Experiment 9: CPU Scheduling
// FCFS and Non-Preemptive SJF

#include <stdio.h>
#define N 100

void show(const char *name, int n, int id[], int bt[]) {
    int time = 0;
    double total_wt = 0, total_tat = 0;
    printf("\n%s (all arrivals = 0)\n", name);
    printf("PID  BT  WT  TAT\n");
    for (int i = 0; i < n; i++) {
        int wt = time, tat = wt + bt[i];
        printf("P%-3d %-3d %-3d %d\n", id[i], bt[i], wt, tat);
        total_wt += wt;
        total_tat += tat;
        time = tat;
    }
    printf("Average WT = %.2f, Average TAT = %.2f\n", total_wt / n, total_tat / n);
}

int main(void) {
    int n, bt[N], order[N], sorted_bt[N], sorted_id[N];
    printf("Number of processes: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > N) return 1;
    printf("Burst times: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
        if (bt[i] < 1) return 1;
        order[i] = sorted_id[i] = i + 1;
        sorted_bt[i] = bt[i];
    }
    show("FCFS", n, order, bt);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (sorted_bt[j] < sorted_bt[i]) {
                int t = sorted_bt[i]; sorted_bt[i] = sorted_bt[j]; sorted_bt[j] = t;
                t = sorted_id[i]; sorted_id[i] = sorted_id[j]; sorted_id[j] = t;
            }
    show("SJF (non-preemptive)", n, sorted_id, sorted_bt);
    return 0;
}
