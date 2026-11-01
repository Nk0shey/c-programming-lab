#ifndef C_LAB_CONSOLE_H
#define C_LAB_CONSOLE_H
/* Small console exercises fail fast on malformed or incomplete input.
 * This avoids continuing with uninitialized values. File loaders retain their
 * own error handling. String conversion widths must match destination buffers.
 */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
static inline int lab_scanf(const char *format, ...) {
    int expected = 0;
    for (const char *p = format; *p; ++p) {
        if (*p != '%') continue;
        ++p;
        if (*p == '%') continue;
        int suppressed = *p == '*';
        while (*p && *p != '[' && *p != 'd' && *p != 'i' && *p != 'u' &&
               *p != 'f' && *p != 's' && *p != 'c' && *p != 'n') ++p;
        if (!*p) break;
        if (!suppressed && *p != 'n') ++expected;
        if (*p == '[') { ++p; if (*p == '^') ++p; if (*p == ']') ++p; while (*p && *p != ']') ++p; if (!*p) break; }
    }
    va_list args;
    va_start(args, format);
    int result = vfscanf(stdin, format, args);
    va_end(args);
    if (result != expected) {
        fputs("Input non valido o incompleto.\n", stderr);
        exit(EXIT_FAILURE);
    }
    return result;
}
static inline void lab_discard_line(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}
#endif
