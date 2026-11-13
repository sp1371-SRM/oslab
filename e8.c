#include <stdio.h>
#define N 20

int safe(int n, int m, int alloc[N][N], int max[N][N], int avail[N], int seq[N]) {
    int work[N], done[N] = {0}, count = 0;
    for (int j = 0; j < m; j++) work[j] = avail[j];
    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (done[i]) continue;
            int possible = 1;
            for (int j = 0; j < m; j++)
                if (max[i][j] - alloc[i][j] > work[j]) possible = 0;
            if (possible) {
                for (int j = 0; j < m; j++) work[j] += alloc[i][j];
                seq[count++] = i;
                done[i] = found = 1;
            }
        }
        if (!found) return 0;
    }
    return 1;
}

int main(void) {
    int n, m, alloc[N][N], max[N][N], avail[N], seq[N];
    printf("Processes and resource types: ");
    if (scanf("%d%d", &n, &m) != 2 || n < 1 || n > N || m < 1 || m > N) return 1;
    printf("Allocation matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) scanf("%d", &alloc[i][j]);
    printf("Maximum matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
            if (max[i][j] < alloc[i][j] || alloc[i][j] < 0) return 1;
        }
    printf("Available resources: ");
    for (int j = 0; j < m; j++) {
        scanf("%d", &avail[j]);
        if (avail[j] < 0) return 1;
    }
    printf("Need matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) printf("%d ", max[i][j] - alloc[i][j]);
        printf("\n");
    }
    if (!safe(n, m, alloc, max, avail, seq)) {
        printf("Unsafe state\n");
    } else {
        printf("Safe state. Sequence: ");
        for (int i = 0; i < n; i++) printf("P%d%s", seq[i], i == n - 1 ? "\n" : " -> ");
    }
    int p, req[N];
    printf("Process to request resources (-1 to skip): ");
    if (scanf("%d", &p) != 1 || p == -1) return 0;
    if (p < 0 || p >= n) return 1;
    printf("Request vector: ");
    for (int j = 0; j < m; j++) scanf("%d", &req[j]);
    for (int j = 0; j < m; j++) {
        if (req[j] < 0 || req[j] > max[p][j] - alloc[p][j]) {
            printf("Request exceeds need\n");
            return 0;
        }
        if (req[j] > avail[j]) {
            printf("Request must wait: resources unavailable\n");
            return 0;
        }
    }
    for (int j = 0; j < m; j++) {
        avail[j] -= req[j];
        alloc[p][j] += req[j];
    }
    if (safe(n, m, alloc, max, avail, seq)) {
        printf("Request granted. Safe sequence: ");
        for (int i = 0; i < n; i++) printf("P%d%s", seq[i], i == n - 1 ? "\n" : " -> ");
    } else {
        for (int j = 0; j < m; j++) {
            avail[j] += req[j];
            alloc[p][j] -= req[j];
        }
        printf("Request denied: would make system unsafe\n");
    }
    return 0;
}
