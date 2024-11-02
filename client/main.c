//----HEADER---------------------------------------------------------------------------------------
// Author:      Sam Rolfe
// Date:        November 2024
// Script:      main.c 
// Usage:       ./a.out <port>
//*************************************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "client.h"
#include "../shared/message.h"
#include <netinet/in.h> 
#include <sys/socket.h>       
#include <sys/types.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#include <unistd.h>

// ----GLOBAL VARIABLES----------------------------------------------------------------------------
#define MAX_FILENAME_SIZE 20
#define MAX_BUFFER_SIZE 514
#define SERVER_ADDRESS "127.0.0.1"  // Localhost, change as needed

//----FUNCTIONS------------------------------------------------------------------------------------

int main(int argc, char* argv[]) {
    
    // Declare variables
    int SERVER_PORT; 
    char file_name[MAX_FILENAME_SIZE];
    int window_size;
    int socket_fd;
    char* buffer[MAX_BUFFER_SIZE];
    struct sockaddr_in server_addr;
    socklen_t len = sizeof(server_addr);

    // Open socket
    if((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Get port number from argv
    if(argc != 2) {
        printf("Usage: %s <port> \n", argv[0]);
        return -1;
    }
    SERVER_PORT = atoi(argv[1]);

    // Initialize fields of struct for server address
    memset(&server_addr, 0, sizeof(server_addr));  // Set structure to 0's, ensuring sin_zero is all zeros
    server_addr.sin_family = AF_INET;              // Set address family to IPv4
    server_addr.sin_port = htons(SERVER_PORT);     // Set port number

    // Convert the IP address and store it in server_addr
    if (inet_pton(AF_INET, SERVER_ADDRESS, &server_addr.sin_addr) <= 0) {
        perror("Invalid server address");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    printf("\nEnter filename to transfer: \n");
    scanf("%s", file_name);
    printf("\nEnter window size: \n");
    scanf("%d", &window_size);
    printf("Requesting filename: %s, window size: %d", file_name, window_size);

    // Send message request
    Message* message = get_message_read_request(window_size, file_name);
    sendto(socket_fd, (char*) message, sizeof(Message), 0, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_in));

    // Get response from server
    int bytes_received = recvfrom(socket_fd, buffer, sizeof(buffer), 0, (struct sockaddr *) &server_addr, &len);
    while(bytes_received > 0){
        bytes_received = recvfrom(socket_fd, buffer, sizeof(buffer), 0, (struct sockaddr *) &server_addr, &len);
    }

    close(socket_fd);

    return 0;
}

//-------------------------------------------------------------------------------------------------