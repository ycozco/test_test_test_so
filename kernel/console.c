#include "console.h"

static uint16_t *video_memory = (uint16_t *)0xB8000;
volatile int position = 0; // Esta definición causaba el problema

void clear_screen() {
    for (int i = 0; i < 80 * 25; i++) {
        video_memory[i] = (0x0F << 8) | ' ';
    }
    position = 0; // Reiniciar la posición
}
