#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "question2.h"

int process_command()
{
    char buffer[50];
    const char *prompt = "enseash % ";
    const char *unknown_cmd = "Unknown command...\n";

    // Afficher le prompt
    write(STDOUT_FILENO, prompt, strlen(prompt));

    // Lire la commande
    ssize_t bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);

    if (bytes_read > 0)
    {
        buffer[bytes_read - 1] = '\0'; // Remplacer le retour à la ligne par un terminateur

        // Vérifier la commande "exit"
        if (strcmp(buffer, "exit") == 0)
        {
            return 0; // Signaler la fin du shell
        }
        else
        {
            write(STDOUT_FILENO, unknown_cmd, strlen(unknown_cmd));
        }
    }

    return 1; // Continuer le shell
}
