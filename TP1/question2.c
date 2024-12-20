#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "question2.h"

int process_command(void)
{
    char buffer[50];
    const char *prompt = "enseash % ";
    const char *unknown_cmd = "Unknown command...\n";

    // Display the prompt
    write(STDOUT_FILENO, prompt, strlen(prompt));

    // Read the user command
    ssize_t bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);

    if (bytes_read > 0)
    {
        buffer[bytes_read - 1] = '\0'; // Replace newline with null terminator

        // Check for the "exit" command
        if (strcmp(buffer, "exit") == 0)
        {
            exit(EXIT_SUCCESS); // Exit the shell
        }
        else
        {
            write(STDOUT_FILENO, unknown_cmd, strlen(unknown_cmd));
        }
    }

    return 1; // Continue the shell loop
}
