/***********************************************************************************************************************
 * Jonathan Rach
 * David Bethelmy
 * CS344 C Programing and Unix
 * Final Project
 *
 *
 * CommunicateWithServer.c
 * This file created to //TODO fill me in with file purpose
 *
 *
 *
 **********************************************************************************************************************/
#include "TCPClient.h"

typedef char BYTE;

void communicateWithServer(int socket)
{
    unsigned int selection = 0;


}

unsigned int displayMenuAndSendSelection(int sock)
{
    struct menu menuBuffer;     /* Buffer for echo string */
    unsigned int response = 0;
    unsigned int output;

    printf("Inside client display menu\n");
    get(sock, &menuBuffer, sizeof(struct menu));  //in this case server is also sending null
    printf("%s\n", menuBuffer.line1);
    printf("%s\n", menuBuffer.line2);
    printf("%s\n", menuBuffer.line3);
    scanf("%d", &response);
    output = htonl(response);
    put(sock, &output, sizeof(unsigned int));
    return response;
}
