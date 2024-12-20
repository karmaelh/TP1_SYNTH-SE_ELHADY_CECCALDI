#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "question4.h"

// Constants
#define BUFFER_SIZE 516
#define RRQ_OPCODE 1
#define ACK_OPCODE 4
#define MODE "octet"
#define MODE_LEN 6

void send_rrq(int sockfd, const char *filename, const struct sockaddr_in *server_addr) {
    char buffer[BUFFER_SIZE];
    ssize_t buffer_len;
    socklen_t addr_len = sizeof(*server_addr);

    // Build the RRQ packet
    buffer[0] = 0;  // Opcode high byte
    buffer[1] = RRQ_OPCODE;  // Opcode low byte
    strcpy(buffer + 2, filename);  // Add filename
    strcpy(buffer + 2 + strlen(filename) + 1, MODE);  // Add mode ("octet")

    buffer_len = 2 + strlen(filename) + 1 + MODE_LEN + 1;

    // Send the RRQ packet to the server
    if (sendto(sockfd, buffer, buffer_len, 0, (struct sockaddr *)server_addr, addr_len) == -1) {
        write(STDOUT_FILENO, "Error: Failed to send RRQ\n", 26);
        exit(EXIT_FAILURE);
    }
    write(STDOUT_FILENO, "RRQ sent successfully\n", 23);
}

void receive_data_and_ack(int sockfd, const struct sockaddr_in *server_addr) {
    char buffer[BUFFER_SIZE];
    char ack[4];
    ssize_t recv_len;
    socklen_t addr_len = sizeof(*server_addr);

    while (1) {
        // Receive a data packet
        recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)server_addr, &addr_len);
        if (recv_len == -1) {
            write(STDOUT_FILENO, "Error: Failed to receive data\n", 30);
            exit(EXIT_FAILURE);
        }

        // Check for end of transmission (data packet < 512 bytes)
        if (recv_len < BUFFER_SIZE) {
            write(STDOUT_FILENO, "End of file received\n", 22);
            break;
        }

        // Send an acknowledgment (ACK)
        ack[0] = 0;  // Opcode high byte
        ack[1] = ACK_OPCODE;  // Opcode low byte
        ack[2] = buffer[2];  // Block number high byte
        ack[3] = buffer[3];  // Block number low byte

        if (sendto(sockfd, ack, sizeof(ack), 0, (struct sockaddr *)server_addr, addr_len) == -1) {
            write(STDOUT_FILENO, "Error: Failed to send ACK\n", 26);
            exit(EXIT_FAILURE);
        }
    }
}

