#include <string.h>
#include <unistd.h>
#include "question1.h"

#define BUFFER_SIZE 256

void concatenate_arguments(char *buffer, char **argv) {
    strncat(buffer, "Host: ", BUFFER_SIZE - strlen(buffer) - 1);
    strncat(buffer, argv[1], BUFFER_SIZE - strlen(buffer) - 1);
    strncat(buffer, "\nFile: ", BUFFER_SIZE - strlen(buffer) - 1);
    strncat(buffer, argv[2], BUFFER_SIZE - strlen(buffer) - 1);
    strncat(buffer, "\n", BUFFER_SIZE - strlen(buffer) - 1);
}

