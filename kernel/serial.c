#include "serial.h"
#include "io.h"

#define SERIAL_PORT 0x3F8

void init_serial() {
    outb(SERIAL_PORT + 1, 0x00);
    outb(SERIAL_PORT + 3, 0x80);
    outb(SERIAL_PORT + 0, 0x03);
    outb(SERIAL_PORT + 1, 0x00);
    outb(SERIAL_PORT + 3, 0x03);
    outb(SERIAL_PORT + 2, 0xC7);
    outb(SERIAL_PORT + 4, 0x0B);
}

void serial_write_char(char c) {
    while ((inb(SERIAL_PORT + 5) & 0x20) == 0);
    outb(SERIAL_PORT, c);
}

void serial_write(const char *str) {
    while (*str) {
        serial_write_char(*str++);
    }
}

void serial_debug(const char *str) {
    serial_write("[DEBUG] ");
    serial_write(str);
    serial_write("\n");
}
