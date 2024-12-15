#include <stdint.h>
#include "io.h"

#define VIDEO_MEMORY (char *)0xb8000
#define KEYBOARD_DATA_PORT 0x60
#define WHITE_ON_BLACK 0x07

extern volatile int position;

void keyboard_handler() {
    uint8_t scancode = inb(KEYBOARD_DATA_PORT);
    char key;

    if (scancode >= 0x10 && scancode <= 0x19) key = 'a' + (scancode - 0x10); 
    else if (scancode >= 0x1E && scancode <= 0x26) key = 'a' + (scancode - 0x1E) + 8; 
    else if (scancode >= 0x2C && scancode <= 0x32) key = 'a' + (scancode - 0x2C) + 16; 
    else key = '?';

    char *video_memory = VIDEO_MEMORY + position;
    *video_memory = key;
    *(video_memory + 1) = WHITE_ON_BLACK;
    position += 2;
}
