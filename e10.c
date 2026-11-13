// Experiment 10: CPU Scheduling
// Non-Preemptive Priority and Round Robin

#include <stdio.h>
#define N 100

int main(void) {
    int n, bt[N], priority[N], id[N], rem[N], complete[N] = {0};
    printf("Number of processes: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > N) return 1;
    printf("Burst time and priority for each process (smaller priority = higher):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &bt[i], &priority[i]);
        if (bt[i] < 1) return 1;
        id[i] = i + 1;
        rem[i] = bt[i];
    }
    int order[N];
    for (int i = 0; i < n; i++) order[i] = i;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (priority[order[j]] < priority[order[i]]) {
                int t = order[i]; order[i] = order[j]; order[j] = t;
            }
    int time = 0;
    double total_wt = 0, total_tat = 0;
    printf("\nPRIORITY (non-preemptive, all arrivals = 0)\nPID  BT  PR  WT  TAT\n");
    for (int k = 0; k < n; k++) {
        int i = order[k], wt = time;
        time += bt[i];
        printf("P%-3d %-3d %-3d %-3d %d\n", id[i], bt[i], priority[i], wt, time);
        total_wt += wt;
        total_tat += time;
    }
    printf("Average WT = %.2f, Average TAT = %.2f\n", total_wt / n, total_tat / n);
    int quantum;
    printf("\nRound Robin time quantum: ");
    if (scanf("%d", &quantum) != 1 || quantum < 1) return 1;
    time = 0;
    int left = n;
    while (left) {
        for (int i = 0; i < n; i++) {
            if (rem[i] == 0) continue;
            int slice = rem[i] < quantum ? rem[i] : quantum;
            rem[i] -= slice;
            time += slice;
            if (rem[i] == 0) {
                complete[i] = time;
                left--;
            }
        }
    }
    total_wt = total_tat = 0;
    printf("\nROUND ROBIN (all arrivals = 0)\nPID  BT  WT  TAT\n");
    for (int i = 0; i < n; i++) {
        int tat = complete[i], wt = tat - bt[i];
        printf("P%-3d %-3d %-3d %d\n", id[i], bt[i], wt, tat);
        total_wt += wt;
        total_tat += tat;
    }
    printf("Average WT = %.2f, Average TAT = %.2f\n", total_wt / n, total_tat / n);
    return 0;
}
