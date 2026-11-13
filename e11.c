#include <stdio.h>
#define N 200
#define F 50

void run(int type, int n, int pages[], int frames) {
    int mem[F], freq[F] = {0}, inserted[F] = {0}, recent[F] = {0};
    int faults = 0, hits = 0;
    for (int j = 0; j < frames; j++) mem[j] = -1;
    printf("\n%s\n", type == 0 ? "FIFO" : type == 1 ? "LRU" : "LFU");
    for (int i = 0; i < n; i++) {
        int slot = -1;
        for (int j = 0; j < frames; j++) if (mem[j] == pages[i]) slot = j;
        int hit = slot >= 0;
        if (hit) {
            hits++;
            freq[slot]++;
            recent[slot] = i;
        } else {
            faults++;
            for (int j = 0; j < frames; j++) if (mem[j] == -1) { slot = j; break; }
            if (slot == -1) {
                slot = 0;
                for (int j = 1; j < frames; j++) {
                    int replace = type == 0 ? inserted[j] < inserted[slot] :
                                  type == 1 ? recent[j] < recent[slot] :
                                  freq[j] < freq[slot] ||
                                  (freq[j] == freq[slot] && inserted[j] < inserted[slot]);
                    if (replace) slot = j;
                }
            }
            mem[slot] = pages[i];
            inserted[slot] = recent[slot] = i;
            freq[slot] = 1;
        }
        printf("Page %-3d: ", pages[i]);
        for (int j = 0; j < frames; j++) {
            if (mem[j] == -1) printf("- ");
            else printf("%d ", mem[j]);
        }
        printf("  %s\n", hit ? "HIT" : "FAULT");
    }
    printf("Hits = %d, Page faults = %d\n", hits, faults);
}

int main(void) {
    int n, pages[N], frames;
    printf("Number of page references: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > N) return 1;
    printf("Reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
        if (pages[i] < 0) return 1;
    }
    printf("Number of frames: ");
    if (scanf("%d", &frames) != 1 || frames < 1 || frames > F) return 1;
    for (int type = 0; type < 3; type++) run(type, n, pages, frames);
    return 0;
}
