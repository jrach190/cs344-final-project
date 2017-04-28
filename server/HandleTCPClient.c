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

struct Menu {
    char line1[20];
    char line2[20];
    char line3[20];
}Menu;

struct UserInfo{
    char username[31]; //Maximum size of an email address, plus one character for null delimiter
    char password[31]; //Maximum size of a password, plus one character for null delimiter
    char fullname[51]; //Size of first name, last name, and a space between, and a null delimiting character
}UserInfo;

void DieWithError(char * errorMessage); //Error handling function
void get(int, void *, unsigned int);
void put(int, void *, unsigned int);
unsigned int sendMenuAndWaitForResponse(int);
unsigned int sendLogin(int);
unsigned int sendSignUp(int);
int verifyUserInfo(char *, char *);
int verifySignUp(char *, char *, char *);
void runProgram();

void HandleTCPClient(int clntSocket)
{
    int recvMessageSize;
    unsigned int response = 0;
    unsigned char errorMessage[] = "Invalid selection";
    unsigned char endMessage[] = "Session Terminated. Goodbye";
    response = sendMenuAndWaitForResponse(clntSocket);

    //Handle menu response
    while (response!=3)
    {
        if (response == 1)
        {

        }
        else if (response == 2)
        {

        }
        else
        {
            put(clntSocket, errorMessage, sizeof(errorMessage));
        }
        response = sendMenuAndWaitForResponse(clntSocket);
    }

    //Close connection after all operations cease
    put(clntSocket, endMessage, sizeof(endMessage));
    close(clntSocket);
    printf("Connection with client %d closed.\n", clntSocket);
}

unsigned int sendMenuAndWaitForResponse(int clntSocket)
{
    struct Menu mainMenu;
    unsigned int response = 0;
    memset(&mainMenu, 0, sizeof(struct Menu));   /* Zero out structure */
    strcpy(mainMenu.line1, "1)Log in\n");
    strcpy(mainMenu.line2, "2)Sign up\n");
    strcpy(mainMenu.line3, "3) Exit\n");
    printf("Sending initial Menu");
    put(clntSocket, &mainMenu, sizeof(struct Menu));
    get(clntSocket, &response, sizeof(unsigned int));
    return ntohl(response);
}

//unsigned int sendLogin(int clntSocket)
//{
//    int userVerified;
//    struct Menu loginMenu;
//    char username[31];
//    char password[31];
//    memset(&username, 0, sizeof(username)); //zero out username array
//    memset(&password, 0, sizeof(password)); //zero out password array
//    memset(&loginMenu, 0, sizeof(struct Menu)); //zero out structure
//    strcpy(loginMenu.line1, "Please log in.\n");
//    strcpy(loginMenu.line2, "Enter your username:");
//
//    put(clntSocket, &loginMenu, sizeof(struct Menu)); //send login menu to client
//    get(clntSocket, &username, sizeof(username)); //get username from client
//    memset(&loginMenu, 0, sizeof(struct Menu)); //zero out structure again for password message
//    strcpy(loginMenu.line1, "\nEnter your password:");
//
//    put(clntSocket,&loginMenu, sizeof(struct Menu)); //send login menu part 2 to client
//    get(clntSocket, &password, sizeof(password)); //get password from client
//
//    userVerified = verifyUserInfo(username,password);
//
//    if (userVerified == 1) //Return 1 if the user is successfully verified
//    {
//        return 1;
//    }
//    if (userVerified == 2) //Return 2 if the user does not exist
//    {
//        return 2;
//    }
//
//    return 0;
//}

//unsigned int sendSignUp(int clntSocket)
//{
//    return 0;
//}

//int verifyUserInfo(char * username, char * password)
//{
//    FILE *fp;
//    char fileUserName[31];
//    char filePassWord[31];
//
//    fp = fopen("users.txt","r");
//
//    while (fscanf(fp, "%s%s",fileUserName,filePassWord) != EOF)
//    {
//        if ((strcmp(fileUserName,username) == 0)){
//            if ((strcmp(filePassWord,password) == 0))
//            {
//                fclose(fp);
//                return 1; //User successfully verified, exit and return 1
//            }
//        }
//        fclose(fp);
//        return 2; //Username did not exist in file, exit returning 2 so client knows to send sign up information instead
//    }
//
//
//    fclose(fp);
//    return 0;
//}