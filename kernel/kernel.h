#ifndef KERNEL_H
#define KERNEL_H

#include "scheduler.h" // Incluir el planificador

// Declaraciones generales del kernel
void main();

// Declaración externa de la variable position
extern volatile int position;

#endif