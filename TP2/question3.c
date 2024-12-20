#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>

#define ERROR_MESSAGE "Error: Unable to create the socket\n"
#define ERROR_MESSAGE_LEN 35
#define SUCCESS_MESSAGE "Socket successfully created\n"
#define SUCCESS_MESSAGE_LEN 29
#define DEFAULT_PORT "69" // Port par défaut pour TFTP

// Reserve a socket and connect to the server
int reserve_socket(const char *host) {
    struct addrinfo hints, *res;
    int sockfd;
    int status;

    // Initialize the hints structure for getaddrinfo
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;       // IPv4 only
    hints.ai_socktype = SOCK_DGRAM;  // UDP socket

    // Resolve the host address using getaddrinfo
    status = getaddrinfo(host, DEFAULT_PORT, &hints, &res);
    if (status != 0) {
        write(STDOUT_FILENO, ERROR_MESSAGE, ERROR_MESSAGE_LEN);
        return -1; // Indicate failure
    }

    // Create the socket
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd == -1) {
        write(STDOUT_FILENO, ERROR_MESSAGE, ERROR_MESSAGE_LEN);
        freeaddrinfo(res); // Free the linked list
        return -1; // Indicate failure
    }

    // Connect the socket to the server
    status = connect(sockfd, res->ai_addr, res->ai_addrlen);
    if (status == -1) {
        write(STDOUT_FILENO, ERROR_MESSAGE, ERROR_MESSAGE_LEN);
        close(sockfd);     // Close the socket
        freeaddrinfo(res); // Free the linked list
        return -1; // Indicate failure
    }

    // Free the address information
    freeaddrinfo(res);

    // Write a success message
    write(STDOUT_FILENO, SUCCESS_MESSAGE, SUCCESS_MESSAGE_LEN);

    return sockfd; // Return the socket file descriptor
}
