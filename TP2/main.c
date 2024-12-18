#include <unistd.h>
#include <string.h>  // Ajout pour strlen
#include "question1.h"
#include "question2.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        write(STDOUT_FILENO, "Usage: ./program host file\n", 27);
        return 1;
    }

    char buffer[256] = "Arguments received:\n";
    concatenate_arguments(buffer, argv);
    write(STDOUT_FILENO, buffer, strlen(buffer));  // strlen est maintenant reconnu

    resolve_host(argv[1]);

    return 0;
}



