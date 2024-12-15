#include "miniprintf.h"
#include <stdarg.h>
#include <stddef.h>

static void print_char(char *buffer, size_t *pos, char c) {
    if (buffer) {
        buffer[*pos] = c;
    }
    (*pos)++;
}

static void print_string(char *buffer, size_t *pos, const char *str) {
    while (*str) {
        print_char(buffer, pos, *str++);
    }
}

static void print_number(char *buffer, size_t *pos, int value, int base) {
    char digits[] = "0123456789ABCDEF";
    char temp[32];
    int i = 0;

    if (value < 0 && base == 10) {
        print_char(buffer, pos, '-');
        value = -value;
    }

    do {
        temp[i++] = digits[value % base];
        value /= base;
    } while (value);

    while (i--) {
        print_char(buffer, pos, temp[i]);
    }
}

int mini_snprintf(char *buffer, size_t size, const char *format, ...) {
    va_list args;
    size_t pos = 0;

    va_start(args, format);

    while (*format) {
        if (*format == '%') {
            format++;
            if (*format == 's') {
                print_string(buffer, &pos, va_arg(args, const char *));
            } else if (*format == 'd') {
                print_number(buffer, &pos, va_arg(args, int), 10);
            } else if (*format == 'x') {
                print_number(buffer, &pos, va_arg(args, int), 16);
            } else {
                print_char(buffer, &pos, '%');
                print_char(buffer, &pos, *format);
            }
        } else {
            print_char(buffer, &pos, *format);
        }
        format++;
    }

    va_end(args);

    if (buffer && pos < size) {
        buffer[pos] = '\0';
    }

    return pos;
}
