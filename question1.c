#include <unistd.h>
#include <string.h>
#include "question1.h"

void show_welcome_message()
{
    const char welcome_msg[] = "Welcome to the ENSEA Shell.\nType 'exit' to quit.\n";
    write(STDOUT_FILENO, welcome_msg, strlen(welcome_msg));
}
