//----HEADER---------------------------------------------------------------------------------------
// Author:      Sam Rolfe
// Date:        November 2024
// Script:      message.c
// Usage:       Implementation file for client
//*************************************************************************************************
#include "message.h"

#include <stdlib.h>
#include <string.h>
// ----GLOBAL VARIABLES----------------------------------------------------------------------------


//----FUNCTIONS------------------------------------------------------------------------------------


Message* get_message_read_request(int window_size, char* file_name) {
    Message* message = malloc(sizeof(Message));
    message->type = 1;
    message->num = window_size;
    strncpy(message->data, file_name, sizeof(message->data)-1);
    return message;
}
// Message* get_message_data();
// Message* get_message_acknowledgement();
// Message* get_message_error();

//-------------------------------------------------------------------------------------------------
