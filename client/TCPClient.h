/***********************************************************************************************************************
 * Jonathan Rach
 * David Bethelmy
 * CS344 C Programing and Unix
 * Final Project
 *
 *
 * TCPClient.h
 * This file created to //TODO fill me in with file purpose
 *
 *
 * This file adapted from TCPServer.h as provided by David Bethelmy
 **********************************************************************************************************************/

#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

void DieWithError(char *errorMessage);  /* Error handling function */
int CreateTCPClientSocket(struct sockaddr_in *, char *, unsigned short); /*Create TCP client socket*/
void communicateWithServer(int); /*Handle server connection*/