/***********************************************************************************************************************
 * Jonathan Rach
 * David Bethelmy
 * CS344 C Programing and Unix
 * Final Project
 *
 *
 * transmission.c
 * This file created to provide functions for getting information from the server and sending (putting) information to
 * the server
 *
 *
 * This code provided by David Bethelmy in the clientWithMenu folder for use in CS344 C Programming and Unix course.
 **********************************************************************************************************************/
#include <sys/socket.h> /* for recv() and send() */
#include "TCPClient.h"

void get(int sock, void * buffer, unsigned int size)
{
    unsigned int totalBytesRcvd = 0;
    unsigned int bytesRcvd = 0;

    while(totalBytesRcvd < size)
    {
        if((bytesRcvd = recv(sock, buffer, size, 0)) <= 0)
            DieWithError("recv() failed or connection closed prematurely");
        totalBytesRcvd += bytesRcvd;
    }
}

void put(int sock, void * buffer, unsigned int size)
{
    if (send(sock, buffer, size, 0) != size)
        DieWithError("send() failed");
}
