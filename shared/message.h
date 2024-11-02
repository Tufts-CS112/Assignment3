//----HEADER---------------------------------------------------------------------------------------
// Author:      Sam Rolfe
// Date:        November 2024
// Script:      message.h 
// Usage:       Header file for client
//*************************************************************************************************
#ifndef MESSAGE_H
#define MESSAGE_H

// ----GLOBAL VARIABLES----------------------------------------------------------------------------
#define MAX_DATA_SIZE 512
// ----STRUCT--------------------------------------------------------------------------------------
typedef struct __attribute__((__packed__)) Message{
    char type;
    char num;
    char data[MAX_DATA_SIZE];
} Message;
//----FUNCTIONS------------------------------------------------------------------------------------

Message* get_message_read_request(int window_size, char* file_name);
// Message* get_message_data();
// Message* get_message_acknowledgement();
// Message* get_message_error();

#endif
//-------------------------------------------------------------------------------------------------
