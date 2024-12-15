#ifndef DEBUG_H
#define DEBUG_H

#include <stdint.h>

void init_serial();
void serial_write(char c);
void serial_write_str(const char *str);

#endif
