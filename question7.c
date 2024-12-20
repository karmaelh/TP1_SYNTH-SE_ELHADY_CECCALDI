#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "question7.h"

#define NB_OF_CARACT 42
#define NB_OF_CARACT2 41
#define DEFAULT_FILE_PERMISSIONS 0644

void handle_redirection(char *args[]) {
    int i = 0;
    int fd;

    // Iterate through the arguments to find '>' or '<'
    while (args[i] != NULL) {
        if (strcmp(args[i], ">") == 0) {
            // Output redirection ('>')
            if (args[i + 1] == NULL) {
                write(STDERR_FILENO, "No file specified for output redirection\n", NB_OF_CARACT);
                exit(EXIT_FAILURE);
            }

            // Open the file in write mode
            fd = open(args[i + 1], O_CREAT | O_WRONLY | O_TRUNC, DEFAULT_FILE_PERMISSIONS);
            if (fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }

            // Redirect stdout to the file
            dup2(fd, STDOUT_FILENO);
            close(fd);

            // Remove '>' and the file name from the arguments
            args[i] = NULL;
            args[i + 1] = NULL;
            break;
        } else if (strcmp(args[i], "<") == 0) {
            // Input redirection ('<')
            if (args[i + 1] == NULL) {
                write(STDERR_FILENO, "No file specified for input redirection\n", NB_OF_CARACT2);
                exit(EXIT_FAILURE);
            }

            // Open the file in read mode
            fd = open(args[i + 1], O_RDONLY);
            if (fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }

            // Redirect stdin to the file
            dup2(fd, STDIN_FILENO);
            close(fd);

            // Remove '<' and the file name from the arguments
            args[i] = NULL;
            args[i + 1] = NULL;
            break;
        }
        i++;
    }
}
