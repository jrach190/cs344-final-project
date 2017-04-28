/***********************************************************************************************************************
 * Jonathan Rach
 * David Bethelmy
 * CS344 C Programing and Unix
 * Final Project
 *
 *
 * CreateTCPClient.c
 * This file created to make a TCP Client socket and connect it to the TCP server
 *
 *
 * This file adapted from provided clientWithMenu.c file and CreateTCPServerSocket.c file as provided by David Bethelmy
 * for use in CS344 C Programming and Unix class
 **********************************************************************************************************************/
#include "TCPClient.h"

int CreateTCPClientSocket(struct sockaddr_in * serverAddress, char * serverIP, unsigned short port)
{
    int sock;
    struct sockaddr_in servAddress = *serverAddress;

    //Create a stream socket that uses TCP
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");

    //Construct the server address structure
    memset(&servAddress, 0, sizeof(servAddress));     /* Zero out structure */
    servAddress.sin_family = AF_INET;             /* Internet address family */
    servAddress.sin_addr.s_addr = inet_addr(serverIP);   /* Server IP address */
    servAddress.sin_port = htons(port); /* Server port */

    //Establish the connection with the server
    if (connect(sock, (struct sockaddr *) &servAddress, sizeof(servAddress)) < 0)
        DieWithError("connect() failed");

    return sock;
}