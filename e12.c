// Experiment 12: Memory Allocation
// First Fit, Best Fit and Worst Fit

#include <stdio.h>
#define N 100

void fit(const char *name, int type, int nb, int blocks[], int np, int process[]) {
    int used[N] = {0}, total_waste = 0;
    printf("\n%s\nProcess  Size  Block  Wasted\n", name);
    for (int i = 0; i < np; i++) {
        int choice = -1;
        for (int j = 0; j < nb; j++) {
            if (used[j] || blocks[j] < process[i]) continue;
            if (choice == -1 || (type == 1 && blocks[j] < blocks[choice]) ||
                (type == 2 && blocks[j] > blocks[choice])) choice = j;
            if (type == 0) break;
        }
        if (choice == -1) printf("P%-7d %-5d Not allocated\n", i + 1, process[i]);
        else {
            used[choice] = 1;
            int waste = blocks[choice] - process[i];
            total_waste += waste;
            printf("P%-7d %-5d %-6d %d\n", i + 1, process[i], choice + 1, waste);
        }
    }
    printf("Total internal fragmentation = %d\n", total_waste);
}

int main(void) {
    int nb, np, blocks[N], process[N];
    printf("Number of memory blocks: ");
    if (scanf("%d", &nb) != 1 || nb < 1 || nb > N) return 1;
    printf("Block sizes: ");
    for (int i = 0; i < nb; i++) {
        scanf("%d", &blocks[i]);
        if (blocks[i] <= 0) return 1;
    }
    printf("Number of processes: ");
    if (scanf("%d", &np) != 1 || np < 1 || np > N) return 1;
    printf("Process sizes: ");
    for (int i = 0; i < np; i++) {
        scanf("%d", &process[i]);
        if (process[i] <= 0) return 1;
    }
    fit("FIRST FIT", 0, nb, blocks, np, process);
    fit("BEST FIT", 1, nb, blocks, np, process);
    fit("WORST FIT", 2, nb, blocks, np, process);
    return 0;
}
