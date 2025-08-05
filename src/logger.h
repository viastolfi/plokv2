#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <string.h>

#define log_compile_error(filename, col, row, msg, line) \
    do { \
        printf("%s:%d:%d | error: %s\n", filename, (row) + 1, (col) + 1, msg); \
        printf("  || %s\n", line); \
        printf("  || %*s^\n", (col), ""); \
    } while (0)


#endif // LOGGER_H
