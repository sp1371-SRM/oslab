# OS Lab: Experiments 8–13

Short, standalone C solutions adapted to the topics in the supplied 21CSC202J lab manual. Each file contains all algorithms for its experiment.

| File | Experiment | Algorithms |
|---|---|---|
| `e8.c` | 8 | Banker's safety and resource request |
| `e9.c` | 9 | FCFS, non-preemptive SJF |
| `e10.c` | 10 | Non-preemptive Priority, Round Robin |
| `e11.c` | 11 | FIFO, LRU, LFU page replacement |
| `e12.c` | 12 | First Fit, Best Fit, Worst Fit |
| `e13.c` | 13 | FCFS, SCAN, C-SCAN disk scheduling |

All programs use interactive stdin. Scheduling assumes all arrival times are zero, as the manual does. In priority scheduling, smaller numeric values mean higher priority. Disk SCAN/C-SCAN accepts a direction and the total cylinder count. Memory allocation treats blocks as fixed-size partitions, with each block assigned to at most one process.

## Compile and run

```sh
gcc e8.c -o e8 && ./e8
# Replace 8 with any number through 13.
```

## Download with curl

Repository: https://github.com/sp1371-SRM/oslab (public, branch `main`).

Download one file; change `e8.c` to any filename through `e13.c`:

```sh
curl -fLO https://sp1371-srm.github.io/oslab/e8.c
```

Download all six files in Bash (Linux, macOS, WSL, or Git Bash):

```sh
for n in 8 9 10 11 12 13; do
  curl -fL "https://sp1371-srm.github.io/oslab/e${n}.c" -o "e${n}.c" || break
done
```

In Windows PowerShell:

```powershell
8..13 | ForEach-Object {
  curl.exe -fL "https://sp1371-srm.github.io/oslab/e$_.c" -o "e$_.c"
  if ($LASTEXITCODE -ne 0) { throw "Download failed for e$_.c" }
}
```

### Direct download URLs

- [e8.c](https://sp1371-srm.github.io/oslab/e8.c)
- [e9.c](https://sp1371-srm.github.io/oslab/e9.c)
- [e10.c](https://sp1371-srm.github.io/oslab/e10.c)
- [e11.c](https://sp1371-srm.github.io/oslab/e11.c)
- [e12.c](https://sp1371-srm.github.io/oslab/e12.c)
- [e13.c](https://sp1371-srm.github.io/oslab/e13.c)

No GitHub authentication is required for these public download URLs.
