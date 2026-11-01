#ifndef C_LAB_RECORDS_H
#define C_LAB_RECORDS_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>
/* One bounded nonblank record per line. 0=EOF, -1=I/O or oversized line. */
static inline int lab_read_record(FILE *file, char *line, size_t size) {
    while (fgets(line, (int)size, file)) {
        if (!strchr(line, '\n') && !feof(file)) return -1;
        const unsigned char *p = (const unsigned char *)line;
        while (*p && isspace(*p)) ++p;
        if (*p) return 1;
    }
    return ferror(file) ? -1 : 0;
}
#endif
