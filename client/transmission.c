/***********************************************************************************************************************
 * Jonathan Rach
 * David Bethelmy
 * CS344 C Programing and Unix
 * Final Project
 * 
 * 
 * transmission.c
 * This file created to //TODO fill me in with file purpose
 * 
 * 
 * This code provided by David Bethelmy in the serverWithMenu folder for use in CS344 C Programming and Unix course.
 **********************************************************************************************************************/
#include <sys/socket.h> /* for recv() and send() */
void DieWithError(char *errorMessage);  /* Error handling function */

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