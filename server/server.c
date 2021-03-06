/***********************************************************************************************************************
 * Jonathan Rach
 * David Bethelmy
 * CS344 C Programing and Unix
 * Final Project
 *
 *
 * server.c
 * This file created to accept incoming connections, launch a new thread to handle the connection, and wait for more
 * connections
 *
 * Code for this file adapted from TCPEchoServer-Thread.c file provided by David Bethelmy for CS344 use
 **********************************************************************************************************************/

#include "TCPServer.h"
#include <pthread.h>

void *ThreadMain(void *arg);

struct ThreadArgs{
    int clntSock; //Socket descriptor for client
};

int main(int argc, char * argv[])
{
    int serverSocket;
    int clientSocket;
    unsigned short serverPort;
    pthread_t threadID;
    struct ThreadArgs *threadArgs;

    if (argc != 2) //Test for correct number of arguments
    {
        fprintf(stderr,"Usage:  %s <SERVER PORT>\n", argv[0]);
        exit(1);
    }

    serverPort = atoi(argv[1]); //First argument: local port

    serverSocket = CreateTCPServerSocket(serverPort);

    for ( ; ; )
    {
        clientSocket = AcceptTCPConnection(serverSocket);

        /* Create separate memory for client argument */
        if ((threadArgs = (struct ThreadArgs *) malloc(sizeof(struct ThreadArgs)))
            == NULL)
            DieWithError("malloc() failed");
        threadArgs -> clntSock = clientSocket;

        if (pthread_create(&threadID, NULL, ThreadMain, (void *) threadArgs) != 0)
            DieWithError("pthread_create() failed");
        printf("with thread %ld\n", (long int) threadID);
    }
}

void *ThreadMain(void *threadArgs)
{
    int clientSocket; //Socket descriptor for client connection

    /* Guarantees that thread resources are deallocated upon return */
    pthread_detach(pthread_self());

    /* Extract socket file descriptor from argument */
    clientSocket = ((struct ThreadArgs *) threadArgs) -> clntSock;
    free(threadArgs);              /* Deallocate memory for argument */

    HandleTCPClient(clientSocket);

    return (NULL);
}