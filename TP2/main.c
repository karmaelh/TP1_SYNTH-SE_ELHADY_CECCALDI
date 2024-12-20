#include <unistd.h>
#include <string.h>  // For strlen
#include <arpa/inet.h>
#include "question1.h"
#include "question2.h"
#include "question3.h"
#include "question4.h"

int main(int argc, char *argv[]) {
    // Check that the user provides enough arguments
    if (argc < 3) {
        write(STDOUT_FILENO, "Usage: ./program host file\n", 27);
        return 1;
    }

    // Display received arguments
    char buffer[256] = "Arguments received:\n";
    concatenate_arguments(buffer, argv);  // Call from question1.h
    write(STDOUT_FILENO, buffer, strlen(buffer));

    // Resolve host and display its IP address
    write(STDOUT_FILENO, "Resolving host...\n", 18);
    resolve_host(argv[1]);  // Call from question2.h

    // Reserve a socket
    write(STDOUT_FILENO, "Reserving socket...\n", 21);
    int sockfd = reserve_socket(argv[1]);  // Call from question3.h
    if (sockfd == -1) {
        write(STDOUT_FILENO, "Socket reservation failed\n", 26);
        return 1;
    }

    // Define and initialize the server address
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(69);  // Default TFTP port
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);

    // Send a Read Request (RRQ) to the server
    write(STDOUT_FILENO, "Sending RRQ...\n", 15);
    send_rrq(sockfd, argv[2], &server_addr);  // Call from question4.h

    // Receive data and send acknowledgments
    write(STDOUT_FILENO, "Receiving data...\n", 18);
    receive_data_and_ack(sockfd, &server_addr);  // Call from question4.h

    // Close the socket after usage
    write(STDOUT_FILENO, "Closing socket...\n", 19);
    close(sockfd);

    return 0;
}
