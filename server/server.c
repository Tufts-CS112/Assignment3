//----HEADER---------------------------------------------------------------------------------------
// Author:      Sam Rolfe
// Date:        November 2024
// Script:      message.c
// Usage:       Implementation file for server
//*************************************************************************************************
#include "server.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>  // For socket        
#include <sys/socket.h> 
#include <netinet/in.h> // Provides sockaddr_in struct
#include <arpa/inet.h>
#include <errno.h>      // Allows for printing of perror()
#include <string.h>



// ----GLOBAL VARIABLES----------------------------------------------------------------------------
#define MAX_MESSAGE_SIZE 535

//----FUNCTIONS------------------------------------------------------------------------------------
// Given port number, open socket for listening
int initialize_server(int LISTENING_PORT) {
    
    // Declare variables
    int listening_socket;
    struct sockaddr_in client_addr, server_addr;
    socklen_t addr_length = sizeof(client_addr);
    char buffer[MAX_MESSAGE_SIZE];

    // Create listening socket
    listening_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if(listening_socket < 0) {
        perror("Error creating listening socket");
        return -1;
    }

    // Initialize fields of struct for server address
    memset(&server_addr, 0, sizeof(server_addr)); // Set structure to 0's, ensuring sin_zero is all zeros
    server_addr.sin_family = AF_INET;             // Set address family to IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;     // Set IP address to all IP addresses of machine
    server_addr.sin_port = htons(LISTENING_PORT); // Set port number

    // Set socket options to allow reuse of the address (fixes "address already in use" bug)
    int opt = 1;
    if (setsockopt(listening_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("Error setting socket options");
        close(listening_socket);
        return -1;
    }   

    // Bind socket to IP address and port
    if(bind(listening_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0 ){
        perror("Error binding socket");
        return -1;
    }

    // Listen for incoming connections requests on "listening socket"
    printf("Listening for incoming connection requests on port %d...\n\n", LISTENING_PORT);
    int bytes_received = recvfrom(listening_socket, buffer, MAX_MESSAGE_SIZE, 0, 
                                  (struct sockaddr *) &client_addr, &addr_length);
    printf("Received %d bytes from client\n", bytes_received);

    // Close socket
    close(listening_socket);

    return 0;
}



//-------------------------------------------------------------------------------------------------
