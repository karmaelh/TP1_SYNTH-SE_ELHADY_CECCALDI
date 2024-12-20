#ifndef QUESTION4_H
#define QUESTION4_H

#include <netinet/in.h>

// Functions for TFTP RRQ and data reception
void send_rrq(int sockfd, const char *filename, const struct sockaddr_in *server_addr);
void receive_data_and_ack(int sockfd, const struct sockaddr_in *server_addr);

#endif
