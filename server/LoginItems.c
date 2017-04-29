/***********************************************************************************************************************
 * Jonathan Rach
 * David Bethelmy
 * CS344 C Programing and Unix
 * Final Project
 * 
 * 
 * LoginItems.c
 * This file created to //TODO fill me in with file purpose
 * 
 * 
 * 
 **********************************************************************************************************************/
#include "LoginItems.h"
#include "TCPServer.h"

void sendLoginMenuAndWaitForResponse(int clntSocket, char * usernamePointer, char * passwordPointer)
{
    Menu loginMenu;

    memset(&loginMenu, 0, sizeof(Menu));
    strcpy(loginMenu.line1, "Please log in.\n\n");
    strcpy(loginMenu.line2, "Enter your username: ");
    strcpy(loginMenu.line3, "\nEnter your password: ");

    put(clntSocket, &loginMenu, sizeof(Menu));
    get(clntSocket, usernamePointer, 31);
    get(clntSocket, passwordPointer, 31);
}

void sendSignUpMenuAndWaitForResponse(int clntSocket, char * usernamePointer, char * passwordPointer, char * fullNamePointer)
{
    Menu signUpMenu;

    memset(&signUpMenu, 0, sizeof(Menu));
    strcpy(signUpMenu.line1, "Please sign up.\n\n");
    strcpy(signUpMenu.line2, "Create your username: ");
    strcpy(signUpMenu.line3, "\nCreate your password: ");
    strcpy(signUpMenu.line4, "\nEnter your full name: ");

    put(clntSocket, &signUpMenu, sizeof(Menu));
    get(clntSocket,usernamePointer, 31);
    get(clntSocket, passwordPointer, 31);
    get(clntSocket, fullNamePointer, 51);
}

int verifyUserInfo(UserInfoList * userInfoList, char * username, char * password)
{
    UserInfoNodeType * head = userInfoList->head;
    UserInfo * dataPointer;

    if (head == 0)
    {
        return 2; //no users in users.txt
    }

    while (head != 0)
    {
        dataPointer = head->dataPointer;
        if (!strcmp(dataPointer->username, username))
        {
            if (!strcmp(dataPointer->password,password))
            {
                printf("Client successfully logged in.\n");
                return 1; //Successful login
            }
            printf("Client entered correct username but not password.\n");
            return 4; //Correct username but incorrect password
        }
        head = head->next;
    }
    printf("Client provided incorrect username");
    return 2; //Entered username does not exist
}

int logInUser(int clntSocket, UserInfoList * userInfoList, char * username)
{
    char userName[31];
    char passWord[31];

    sendLoginMenuAndWaitForResponse(clntSocket, userName, passWord);

    strcpy(username,userName);
    return verifyUserInfo(userInfoList, userName, passWord);
}

int signUpUser(int clntSocket, UserInfoList * userInfoList, char * username)
{
    char userName[31];
    char passWord[31];
    char fullName[51];

    UserInfo * newUserInfo;

    sendSignUpMenuAndWaitForResponse(clntSocket, userName, passWord, fullName);

    if (findUser(userInfoList,userName) != 0)
    {
        printf("Client tried to sign up already existing user.\n");
        return 4;
    }

    newUserInfo = (UserInfo *) malloc(sizeof(UserInfo));
    strcpy(newUserInfo->username,userName);
    strcpy(newUserInfo->password,passWord);
    strcpy(newUserInfo->fullname, fullName);

    appendUser(userInfoList, newUserInfo);

    strcpy(username,userName);
    return 1;
}

void readUsersFromFile(UserInfoList * linkedList)
{
    FILE * fp;
    UserInfo * newUserInfo;

    char * userName;
    char * passWord;
    char * fullName;

    fp = (FILE *) fopen("users.txt", "r");

    printf("file open successful.\nchecking if file null\n");

    if (fp == NULL)
    {
        printf("Error: file not found. Exiting");
        fclose(fp);
        return;
    }
    printf("File opened. Trying to scan...");

    while (fscanf(fp,"%s", userName) != EOF && fscanf(fp,"%s", passWord) != EOF && fscanf(fp,"%s", fullName !=EOF))
    {
        newUserInfo = (UserInfo *) malloc(sizeof(UserInfo));
        strcpy(newUserInfo -> username,userName);
        strcpy(newUserInfo -> password,passWord);
        strcpy(newUserInfo->fullname, fullName);
        appendUser(linkedList, newUserInfo);
    }

    fclose(fp);
}

void appendUser(UserInfoList * linkedList, UserInfo * newUserInfo)
{
    UserInfoNodeType * newNodePointer;
    UserInfoNodeType * pointer = linkedList -> head;
    UserInfoNodeType * prevPtr = 0;

    if (newUserInfo == 0)
    {
        return; //nothing to add
    }

    /* create a node to put the data in */
    newNodePointer = (UserInfoNodeType *) malloc(sizeof(UserInfoNodeType));
    /* assign data to the node*/
    newNodePointer -> dataPointer = newUserInfo;
    newNodePointer -> next = 0;

    /* check to see if this is the first item on the list */
    if (linkedList -> head == 0)
    {
        linkedList -> head = newNodePointer;
        linkedList -> count = 1;
        return;
    }

    /* If not the first item, locate the end of the list */
    while(pointer != 0)
    {
        prevPtr = pointer;
        pointer = pointer -> next;
    }

    /*now attach item to the end of the list*/
    prevPtr -> next = newNodePointer;
    linkedList -> count++;
}

UserInfoNodeType * findUser(UserInfoList * linkedList, char * userName)
{
    UserInfoNodeType * head = linkedList -> head;
    UserInfoNodeType * nullNode = 0;
    UserInfo * dataPointer;

    if (head == 0)
    {
        return nullNode; //linked list empty, nothing to find
    }

    dataPointer = (UserInfo *) malloc(sizeof(UserInfo));


    while (head != 0)
    {
        dataPointer = head -> dataPointer;
        if (!strcmp(dataPointer -> username, userName))
        {
            //user exists
            return head;
        }
        head = head -> next;
    }
    return  nullNode; //no match found, return a null node
}