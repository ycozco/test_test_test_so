#include <stdint.h>
#include "io.h"

#define PIC1 0x20 // Controlador de interrupciones maestro
#define PIC2 0xA0 // Controlador de interrupciones esclavo

void init_idt() {
    // Implementación básica para inicializar la IDT
    // Aquí deberías configurar la tabla de descriptores de interrupciones (IDT).
}

void remap_pic() {
    outb(PIC1 + 1, 0x20); // Línea base del PIC maestro
    outb(PIC2 + 1, 0x28); // Línea base del PIC esclavo
}

void setup_interrupts() {
    remap_pic();
    init_idt();
}
