#include <unistd.h>
#include <string.h>
#include "question3.h"

void exit_shell()
{
    const char *bye_msg = "Bye bye...\n";
    write(STDOUT_FILENO, bye_msg, strlen(bye_msg));
}
