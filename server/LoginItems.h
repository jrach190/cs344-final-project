/***********************************************************************************************************************
 * Jonathan Rach
 * David Bethelmy
 * CS344 C Programing and Unix
 * Final Project
 * 
 * 
 * LoginItems.h
 * This file created to //TODO fill me in with file purpose
 * 
 * 
 * 
 **********************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MENUOPTIONLENGTH 30

#ifndef MENU
#define MENU
typedef struct menu
{
    char line1[MENUOPTIONLENGTH];
    char line2[MENUOPTIONLENGTH];
    char line3[MENUOPTIONLENGTH];
    char line4[MENUOPTIONLENGTH];
} Menu;
#endif
#ifndef USERINFO
#define USERINFO
typedef struct userInfo
{
    char username[31]; //Maximum size of an email address, plus one character for null delimiter
    char password[31]; //Maximum size of a password, plus one character for null delimiter
    char fullname[51]; //Size of first name, last name, and a space between, and a null delimiting character
}UserInfo;
#endif
#ifndef USERNODE
#define USERNODE
typedef struct userNode
{
    struct userNode * next;
    UserInfo * dataPointer;
}UserInfoNodeType;
#endif
#ifndef USERLIST
#define USERLIST
typedef struct userList
{
    UserInfoNodeType * head;
    unsigned int count;
}UserInfoList;
#endif

void appendUser(UserInfoList *, UserInfo *);
UserInfoNodeType * findUser(UserInfoList *, char *);
void readUsersFromFile(UserInfoList *);
int verifyUserInfo(UserInfoList *, char *, char *);
int logInUser(int, UserInfoList *, char *);
int signUpUser(int, UserInfoList *, char *);
void sendLoginMenuAndWaitForResponse(int, char *, char *);
void sendSignUpMenuAndWaitForResponse(int, char *, char *, char *);


