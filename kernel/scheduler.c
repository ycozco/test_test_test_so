#include "scheduler.h"
#include "serial.h"

#define QUANTUM 2  // Definir el tiempo de quantum (número de veces que se ejecuta cada tarea antes de cambiar)

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
    int remaining_time[3] = {QUANTUM, QUANTUM, QUANTUM};  // Array para controlar el tiempo restante de ejecución de cada tarea

    while (1) {
        // Ejecutar la tarea actual
        tasks[current_task]();

        // Decrementar el tiempo restante de ejecución de la tarea actual
        remaining_time[current_task]--;

        // Si el quantum de la tarea actual ha terminado, moverla al final de la cola
        if (remaining_time[current_task] <= 0) {
            remaining_time[current_task] = QUANTUM;  // Resetear el tiempo de quantum para la tarea que acaba de pasar al final
            serial_debug("Quantum de Task completado. Moviendo a la siguiente tarea.");
        }

        // Avanzar al siguiente proceso (circular)
        current_task = (current_task + 1) % total_tasks;
    }
}
