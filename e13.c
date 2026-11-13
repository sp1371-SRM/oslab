// Experiment 13: Disk Scheduling
// FCFS, SCAN and C-SCAN

#include <stdio.h>
#include <stdlib.h>
#define N 100

int compare(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

void move(int *head, int next, int *total) {
    if (*head == next) return;
    *total += abs(*head - next);
    *head = next;
    printf(" -> %d", next);
}

int main(void) {
    int n, req[N], sorted[N], head, cylinders, direction;
    printf("Number of requests: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > N) return 1;
    printf("Requests: ");
    for (int i = 0; i < n; i++) scanf("%d", &req[i]);
    printf("Initial head and total cylinders: ");
    if (scanf("%d%d", &head, &cylinders) != 2 || cylinders < 2 || head < 0 || head >= cylinders) return 1;
    printf("Direction (1 = towards larger cylinders, 0 = smaller): ");
    if (scanf("%d", &direction) != 1 || (direction != 0 && direction != 1)) return 1;
    for (int i = 0; i < n; i++) {
        if (req[i] < 0 || req[i] >= cylinders) return 1;
        sorted[i] = req[i];
    }
    qsort(sorted, n, sizeof(int), compare);
    for (int mode = 0; mode < 3; mode++) {
        int current = head, total = 0;
        printf("\n%s: %d", mode == 0 ? "FCFS" : mode == 1 ? "SCAN" : "C-SCAN", head);
        if (mode == 0) {
            for (int i = 0; i < n; i++) move(&current, req[i], &total);
        } else if (direction == 1) {
            int first = 0;
            while (first < n && sorted[first] < head) first++;
            for (int i = first; i < n; i++) move(&current, sorted[i], &total);
            if (first > 0) {
                move(&current, cylinders - 1, &total);
                if (mode == 2) move(&current, 0, &total);
                if (mode == 1)
                    for (int i = first - 1; i >= 0; i--) move(&current, sorted[i], &total);
                else
                    for (int i = 0; i < first; i++) move(&current, sorted[i], &total);
            }
        } else {
            int first = 0;
            while (first < n && sorted[first] <= head) first++;
            for (int i = first - 1; i >= 0; i--) move(&current, sorted[i], &total);
            if (first < n) {
                move(&current, 0, &total);
                if (mode == 2) move(&current, cylinders - 1, &total);
                if (mode == 1)
                    for (int i = first; i < n; i++) move(&current, sorted[i], &total);
                else
                    for (int i = n - 1; i >= first; i--) move(&current, sorted[i], &total);
            }
        }
        printf("\nTotal head movement = %d cylinders\n", total);
    }
    return 0;
}
