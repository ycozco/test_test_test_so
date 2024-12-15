#include "scheduler.h"
#include "console.h"
#include "serial.h"

void main() {
    init_serial();     // Inicializar el puerto serie
    serial_debug("Beinvenido a mi OS");

    clear_screen();    // Limpiar la pantalla
    serial_debug("Pantalla limpiada.");

    schedule();        // Iniciar el planificador
}
