#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include "question1.h"
#include "question2.h"
#include "question4.h"
#include "question5.h"

#define BUFFSIZE 1024
#define NB_ARG_MAX 20

int main()
{
    char buf[BUFFSIZE];
    char *args[NB_ARG_MAX];
    ssize_t command_size;
    int status = 0;
    long exec_time = 0;
    struct timespec start, end;
    pid_t pid;

    const char commandNotFound[]="Command not found\n";

    show_welcome_message();
    write(STDOUT_FILENO, "enseash % ", 11);

    while (1)
    {
        command_size = read(STDIN_FILENO, buf, BUFFSIZE);
        if (command_size <= 0){
            continue;
        }

        buf[command_size - 1] = '\0'; // Remplace \n par \0 pour détecter la fin de chaine de caractere 
        
        args[0] = strtok(buf, " ");
        for (int i = 1; i < NB_ARG_MAX; i++)
        {
            args[i] = strtok(NULL, " ");
            if (args[i] == NULL)
                break;
        }

        clock_gettime(CLOCK_MONOTONIC, &start);
        //handle_redirection(args);
        //execute_command(args, command_size);
        if((pid=fork())==-1){
            // gestion en cas d'erreur de fork
            exit(EXIT_FAILURE);
        }

        if(pid == 0){//son process
            execvp(args[0],args);            // Command not found
            write(STDOUT_FILENO, commandNotFound, strlen(commandNotFound));
            exit(EXIT_FAILURE);
        }
        else{ // father
            wait(&status);
        }
        clock_gettime(CLOCK_MONOTONIC, &end);

        measure_execution_time(&start, &end, &exec_time);

        display_exit_code(status, exec_time);
    }

    return 0;
}



