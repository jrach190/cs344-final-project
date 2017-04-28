/***********************************************************************************************************************
 * Jonathan Rach
 * David Bethelmy
 * CS344 C Programing and Unix
 * Final Project
 * 
 * 
 * ProjectsFunctions.h
 * This file created to //TODO fill me in with file purpose
 * 
 * 
 * 
 **********************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char BYTE;

typedef struct personinfo {
    char PersonName[51]; //Name of person on project, max 50 characters, plus space for '\0'
}PersonInfo;

typedef struct personnode {
    PersonInfo * personInfoPtr;
    struct personnode * next;
}PersonNode;

typedef struct projectnode {
    char ProjectName[101]; //Project name, max 100 characters, plus space for '\0'
    char Description[1001]; //Project description, max 1000 characters, plus space for '\0'
    char DateCreated[9]; //Project creation date, max 8 characters, plus space for '\0'
    char DueDate[9]; //Project due date, max 8 characters, plus space for '\0'
    BYTE MembersOnProject; //byte containing number of members on a project
    PersonNode * personListHead; //Head of linked list of all persons on a project
}ProjectInfo;

typedef struct node
{
    ProjectInfo * projectInfoPtr;
    struct node * next;
}NodeType;

typedef struct ProjectList {
    NodeType * head;
    unsigned int count;
}ProjectList;

void traverseProjects(NodeType *);
void appendProjects(ProjectList *, ProjectInfo *);
int readProjectsFromFile(ProjectList *, char *userName, size_t lengthOfUserName);

void traverseMembers(PersonNode *);
void appendMembers(ProjectInfo *, PersonInfo *);
