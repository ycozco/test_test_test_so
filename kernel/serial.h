#ifndef SERIAL_H
#define SERIAL_H

void init_serial();
void serial_write_char(char c);
void serial_write(const char *str);
void serial_debug(const char *str);

#endif // SERIAL_H
