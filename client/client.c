/***********************************************************************************************************************
 * Jonathan Rach
 * David Bethelmy
 * CS344 C Programing and Unix
 * Final Project
 *
 *
 * client.c
 * This file created to //TODO fill me in with file purpose
 *
 *
 * This file adapted from provided ClientWithMenu folder provided by David Bethelmy for use in CS344 C Programming and
 * Unix class
 **********************************************************************************************************************/

#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

#include "TCPClient.h"


#define RCVBUFSIZE 100   /* Size of receive buffer */
#define NAME_SIZE 21 /*Includes room for null */

typedef char BYTE;

void communicateWithServer(int);

int main(int argc, char * argv)
{
    int socket;
    struct sockaddr_in serverAddress;
    unsigned short serverPort;
    char * serverIP;

    if (argc!=3)    //Test for correct number of arguments
    {
        fprintf(stderr, "Usage: %s <Server IP> <Echo Port>\n",
                argv[0]);
        exit(1);
    }

    serverIP = argv[1]; //Set the server IP to the passed value
    serverPort = atoi(argv[2]); //Set the server port to the passed value

    socket = CreateTCPClientSocket(&serverAddress, serverIP, serverPort);

    communicateWithServer(socket);

    close(socket);
    return 0;
}