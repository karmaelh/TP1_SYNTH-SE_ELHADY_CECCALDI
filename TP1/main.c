#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "question1.h"
#include "question2.h"
#include "question4.h"
#include "question5.h"
#include "question7.h"

#define BUFFSIZE 1024
#define NB_ARG_MAX 20
#define NbOfCaract 11

int main() {
    char buf[BUFFSIZE];
    char *args[NB_ARG_MAX];
    ssize_t command_size;
    int status = 0;
    long exec_time = 0;
    struct timespec start, end;
    pid_t pid;

    const char commandNotFound[] = "Command not found\n";

    // Display welcome message
    show_welcome_message();

    // Display the initial prompt
    write(STDOUT_FILENO, "enseash % ", NbOfCaract);

    while (1) {
        // Read the command entered by the user
        command_size = read(STDIN_FILENO, buf, BUFFSIZE);
        if (command_size <= 0) {
            continue;
        }

        // Replace the final \n with \0
        buf[command_size - 1] = '\0';

        // Split the command into arguments
        args[0] = strtok(buf, " ");
        for (int i = 1; i < NB_ARG_MAX; i++) {
            args[i] = strtok(NULL, " ");
            if (args[i] == NULL)
                break;
        }

        // If no command is entered, display the prompt again
        if (args[0] == NULL) {
            write(STDOUT_FILENO, "enseash % ", NbOfCaract);
            continue;
        }

        // Measure the start time
        clock_gettime(CLOCK_MONOTONIC, &start);

        // Create a child process
        if ((pid = fork()) == -1) {
            // Handle fork error
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { // Child process
            // Handle input/output redirection before execution
            handle_redirection(args);

            // Execute the command with its arguments
            execvp(args[0], args);

            // If the command fails
            write(STDOUT_FILENO, commandNotFound, strlen(commandNotFound));
            exit(EXIT_FAILURE);
        } else { // Parent process
            // Wait for the child process to finish
            wait(&status);
        }

        // Measure the end time
        clock_gettime(CLOCK_MONOTONIC, &end);

        // Calculate the execution time
        measure_execution_time(&start, &end, &exec_time);

        // Display the return code and execution time
        display_exit_code_with_time(status, exec_time);
    }

    return 0;
}




