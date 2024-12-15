#include "scheduler.h"
#include "serial.h"

void task1() {
    serial_debug("Task 1 ejecutada.");
}

void task2() {
    serial_debug("Task 2 ejecutada.");
}

void task3() {
    serial_debug("Task 3 ejecutada.");
}

void schedule() {
    void (*tasks[])() = { task1, task2, task3 };
    int total_tasks = 3;
    int current_task = 0;

    while (1) {
        tasks[current_task]();
        current_task = (current_task + 1) % total_tasks;
    }
}
