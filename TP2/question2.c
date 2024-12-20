#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>  // Pour inet_ntop

#define BUFFER_SIZE 256
#define DEFAULT_PORT "69"
#define ERROR_MESSAGE "Error: Unable to resolve the address\n"
#define ERROR_LEN 35
#define RESOLVED_MSG "Host resolved successfully\n"

// Resolve the host and print its IP address
void resolve_host(const char *host) {
    struct addrinfo hints, *res, *p;
    char ip_str[INET_ADDRSTRLEN]; // Buffer for IPv4 address
    int status;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;     // IPv4
    hints.ai_socktype = SOCK_DGRAM; // UDP

    // Perform getaddrinfo to resolve the host
    status = getaddrinfo(host, DEFAULT_PORT, &hints, &res);
    if (status != 0) {
        write(STDOUT_FILENO, ERROR_MESSAGE, ERROR_LEN);
        return;
    }

    // Loop through the results and get the IP address
    for (p = res; p != NULL; p = p->ai_next) {
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
        inet_ntop(AF_INET, &(ipv4->sin_addr), ip_str, INET_ADDRSTRLEN);
        write(STDOUT_FILENO, "Server IP: ", 11);
        write(STDOUT_FILENO, ip_str, strlen(ip_str));
        write(STDOUT_FILENO, "\n", 1);
        break; // Print the first IP found
    }

    freeaddrinfo(res); // Free the linked list
    write(STDOUT_FILENO, RESOLVED_MSG, strlen(RESOLVED_MSG));
}
