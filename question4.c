#include <sys/wait.h>  // For WIFEXITED, WEXITSTATUS, WIFSIGNALED, WTERMSIG
#include <unistd.h>    
#include <string.h>    
#include <stdio.h>    
#include <stdlib.h>
#include <sys/types.h>

// Driver code


void display_exit_code(int status, long exec_time)
{
    char prompt[100];
    int length = 0;

    if (WIFEXITED(status))
    {
        length = snprintf(prompt, sizeof(prompt), "enseash [exit:%d] %% ", WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status))
    {
        length = snprintf(prompt, sizeof(prompt), "enseash [sign:%d] %% ", WTERMSIG(status));
    }

    write(STDOUT_FILENO, prompt, length);
}


