#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

struct Slot {
    int pid;
    int start;
    int end;
};

int compare_arrival(const void *x, const void *y) {
    const struct Process *p = x;
    const struct Process *q = y;

    if (p->arrival_time != q->arrival_time)
        return p->arrival_time - q->arrival_time;
    return p->pid - q->pid;
}

void finish(struct Process *p, int start) {
    int completion = start + p->burst_time;

    p->turnaround_time = completion - p->arrival_time;
    p->waiting_time = p->turnaround_time - p->burst_time;
    p->response_time = start - p->arrival_time;
}

void print_gantt(struct Slot *slots, int count) {
    printf("Gantt Chart: ");

    for (int i = 0; i < count; i++) {
        if (slots[i].pid == 0)
            printf("| IDLE ");
        else
            printf("| P%d ", slots[i].pid);
    }
    printf("|\n");
}

void print_table(struct Process *procs, int n) {
    double total_wt = 0, total_tat = 0, total_rt = 0;

    printf("PID\tAT\tBT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               procs[i].pid, procs[i].arrival_time, procs[i].burst_time,
               procs[i].waiting_time, procs[i].turnaround_time,
               procs[i].response_time);
        total_wt += procs[i].waiting_time;
        total_tat += procs[i].turnaround_time;
        total_rt += procs[i].response_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Response Time: %.2f\n\n", total_rt / n);
}

void fcfs(struct Process *input, int n) {
    struct Process *procs = malloc(n * sizeof(struct Process));
    struct Slot *slots = malloc(2 * n * sizeof(struct Slot));
    int count = 0;
    int time = 0;

    memcpy(procs, input, n * sizeof(struct Process));
    qsort(procs, n, sizeof(struct Process), compare_arrival);

    for (int i = 0; i < n; i++) {
        if (time < procs[i].arrival_time) {
            slots[count++] = (struct Slot){0, time, procs[i].arrival_time};
            time = procs[i].arrival_time;
        }

        finish(&procs[i], time);
        slots[count++] = (struct Slot){procs[i].pid, time, time + procs[i].burst_time};
        time += procs[i].burst_time;
    }

    printf("=== First Come First Served (FCFS) ===\n");
    print_gantt(slots, count);
    print_table(procs, n);

    free(procs);
    free(slots);
}

void sjf(struct Process *input, int n) {
    struct Process *order = malloc(n * sizeof(struct Process));
    struct Slot *slots = malloc(2 * n * sizeof(struct Slot));
    int *done = calloc(n, sizeof(int));
    int count = 0;
    int time = 0;

    for (int completed = 0; completed < n; completed++) {
        int best = -1;

        /* Shortest burst among arrived processes; ties: earlier arrival, then lower PID */
        for (int i = 0; i < n; i++) {
            if (done[i] || input[i].arrival_time > time)
                continue;
            if (best == -1 ||
                input[i].burst_time < input[best].burst_time ||
                (input[i].burst_time == input[best].burst_time &&
                 input[i].arrival_time < input[best].arrival_time))
                best = i;
        }

        if (best == -1) {
            int next = -1;

            for (int i = 0; i < n; i++) {
                if (!done[i] && (next == -1 || input[i].arrival_time < next))
                    next = input[i].arrival_time;
            }
            slots[count++] = (struct Slot){0, time, next};
            time = next;
            completed--;
            continue;
        }

        done[best] = 1;
        order[completed] = input[best];
        finish(&order[completed], time);
        slots[count++] = (struct Slot){input[best].pid, time, time + input[best].burst_time};
        time += input[best].burst_time;
    }

    printf("=== Shortest Job First (SJF) ===\n");
    print_gantt(slots, count);
    print_table(order, n);

    free(order);
    free(slots);
    free(done);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid number of processes\n");
        return 1;
    }

    struct Process *procs = malloc(n * sizeof(struct Process));
    if (procs == NULL) {
        perror("malloc");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter the arrival time and burst time for process %d: ", i + 1);
        if (scanf("%d %d", &procs[i].arrival_time, &procs[i].burst_time) != 2 ||
            procs[i].arrival_time < 0 || procs[i].burst_time <= 0) {
            fprintf(stderr, "Invalid input for process %d\n", i + 1);
            free(procs);
            return 1;
        }
        procs[i].pid = i + 1;
    }

    printf("\n");
    fcfs(procs, n);
    sjf(procs, n);

    free(procs);
    return 0;
}
