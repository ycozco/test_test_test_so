
#ifndef IO_H
#define IO_H

#include <stdint.h>

// Escribir un byte en un puerto
void outb(uint16_t port, uint8_t value);

// Leer un byte de un puerto
uint8_t inb(uint16_t port);

// Declarar las funciones de serialización
void init_serial();
void serial_write_char(char c);
void serial_write(const char *str);
void serial_debug(const char *str);

#endif // IO_H
