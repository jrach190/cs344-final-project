/***********************************************************************************************************************
 * Jonathan Rach
 * David Bethelmy
 * CS344 C Programing and Unix
 * Final Project
 *
 * HandleTCPClient.c
 * This file created to handle the TCP Clients once they have connected to the server
 * The function sendMenuAndWaitForResponse sends the initial login/signup menu to the client
 * The sendSignUp function sends a sign up menu to the client and verifies to ensure the new user does not already exist
 * The sendLogIn function sends a log in menu to the client and ensures the connecting client is authorized
 *
 *
 * This file is adapted from the provided HandleTCPClient.c file in order to handle the specific behavior relevant to
 * this specific project.
 **********************************************************************************************************************/

#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <string.h>
#include "ProjectsFunctions.h"
#include "TCPServer.h"
#include "LoginItems.h"

typedef struct ProjectMenu
{
    char create[MENUOPTIONLENGTH];
    char edit[MENUOPTIONLENGTH];
    char delete[MENUOPTIONLENGTH];
    char save[MENUOPTIONLENGTH];
    char display[MENUOPTIONLENGTH];
    char exit[MENUOPTIONLENGTH];
}ProjectMenu;

void handleProjects(int);
unsigned int sendMenuAndWaitForResponse(int);
void displayProject(int);
void createNewProject(int);
void editProject(int);
void deleteProject(int);
void saveProject(int);
unsigned int sendNewProjectMenu(int);
unsigned int sendEditProjectMenu(int);



void HandleTCPClient(int clientSocket)
{
    int recvMessageSize;
    unsigned int menuResponse = 0;
    int logInSignUpResult = 0;
    unsigned char errorMessage[] = "Invalid selection";
    unsigned char endMessage[] = "Session Terminated. Goodbye";
    char * username;
    unsigned int systemStatusNotifier = 0;

    //Create and initialize a user info list for password verification use
    UserInfoList userInfoList;
    UserInfoNodeType * userInfoHead = 0;
    userInfoList.head = userInfoHead;
    userInfoList.count = 0;

    printf("Connection made with client %d. Trying to read in users from file now...\n",clientSocket);
    //read in all users that exist in the file "users.txt"
    readUsersFromFile(&userInfoList);

    printf("users successfully read.\nSending menu...\n");
    menuResponse = sendMenuAndWaitForResponse(clientSocket);

    //Handle menu response
    while (menuResponse!=3)
    {
        switch(menuResponse)
        {
            case 1:
                printf("Login selected");
                logInSignUpResult = logInUser(clientSocket, &userInfoList, username);
                break;
            case 2:
                printf("Sign up selected");
                logInSignUpResult = signUpUser(clientSocket, &userInfoList, username);
                break;
            default:
                put(clientSocket, errorMessage, sizeof(errorMessage));
                break;
        }
        if (logInSignUpResult == 1)
        {
            systemStatusNotifier = htonl(logInSignUpResult);
            put(clientSocket, &systemStatusNotifier, sizeof(unsigned int));
            handleProjects(clientSocket);
            menuResponse = sendMenuAndWaitForResponse(clientSocket);
        } else if (logInSignUpResult == 2)
        {
            systemStatusNotifier = htonl(logInSignUpResult);
            put(clientSocket, &systemStatusNotifier, sizeof(unsigned int));
            menuResponse = 2;
        }
        else if (logInSignUpResult == 4)
        {
            systemStatusNotifier = htonl(logInSignUpResult);
            put(clientSocket, &systemStatusNotifier, sizeof(unsigned int));
            menuResponse = 1;
        }
    }

    //Close connection after all operations cease
    put(clientSocket, endMessage, sizeof(endMessage));
    close(clientSocket);
    printf("Connection with client %d closed.\n", clientSocket);
}

unsigned int sendMenuAndWaitForResponse(int clntSocket)
{
    Menu mainMenu;
    unsigned int response = 0;
    memset(&mainMenu, 0, sizeof(Menu));   /* Zero out structure */
    strcpy(mainMenu.line1, "1)Log in\n");
    strcpy(mainMenu.line2, "2)Sign up\n");
    strcpy(mainMenu.line3, "3) Exit\n");
    printf("Sending initial Menu");
    put(clntSocket, &mainMenu, sizeof(Menu));
    get(clntSocket, &response, sizeof(unsigned int));
    return ntohl(response);
}

unsigned int sendProjectMenuAndWaitForResponse(int clntSocket)
{
    ProjectMenu projectMenu;
    unsigned int response = 0;
    memset(&projectMenu, 0, sizeof(ProjectMenu));
    strcpy(projectMenu.create, "1)Create new project\n");
    strcpy(projectMenu.edit, "2)Edit existing project\n");
    strcpy(projectMenu.delete, "3)Delete existing project\n");
    strcpy(projectMenu.save, "4)Save project\n");
    strcpy(projectMenu.display, "5)Display project\n");
    strcpy(projectMenu.exit, "6)Exit\n");
    put(clntSocket,&projectMenu, sizeof(ProjectMenu));
    get(clntSocket, &response, sizeof(unsigned int));
    return ntohl(response);
}

void handleProjects(int clientSocket)
{
    unsigned int response = 0;
    response = sendProjectMenuAndWaitForResponse(clientSocket);
    while (response != 6) {
        switch (response) {
            case 1:
             createNewProject(clientSocket);
                break;
            case 2:
             editProject(clientSocket);
                break;
            case 3:
             deleteProject(clientSocket);
                break;
            case 4:
             saveProject(clientSocket);
                break;
            case 5:
             displayProject(clientSocket);
                break;
            default:
                break;
        }
        response = sendProjectMenuAndWaitForResponse(clientSocket);
    }
}

void displayProject(int clientSocket)
{

}

void createNewProject(int clientSocket)
{
    ProjectInfo * newProject;

    sendNewProjectMenu(clientSocket);
}

void editProject(int clientSocket)
{
    sendEditProjectMenu(clientSocket);
}

void deleteProject(int clientSocket)
{

}

void saveProject(int clientSocket)
{

}

unsigned int sendNewProjectMenu(int clientSocket)
{

}

unsigned int sendEditProjectMenu(int clientSocket)
{

}


