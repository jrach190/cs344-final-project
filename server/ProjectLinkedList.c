/***********************************************************************************************************************
 * Jonathan Rach
 * David Bethelmy
 * CS344 C Programing and Unix
 * Final Project
 * 
 * 
 * ProjectLinkedList.c
 * This file created to handle all linked list aspects related to the project information as defined in the rubric
 * 
 * This file adapted from previously submitted homeworks and linked list files provided by David Bethelmy for the course
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
int readProjectsFromFile(ProjectList *);

void traverseMembers(PersonNode *);
void appendMembers(ProjectInfo *, PersonInfo *);

int main(int argc, char *argv[])
{
    NodeType * head = 0;
    ProjectList projectList;

    projectList.head = head;
    projectList.count = 0;

    readProjectsFromFile(&projectList);
    traverseProjects(projectList.head);
}

void traverseProjects(NodeType * head)
{
    ProjectInfo * dataPointer;

    if (head == 0)
    {
        printf("Project list is empty.\n");
        return; //nothing to find
    }

    while (head != 0)
    {
        dataPointer = head -> projectInfoPtr;
        printf("\n\n------------------------------------------------------------------------\n\n");
        printf("Project name: %s\n", dataPointer -> ProjectName);
        printf("Project description: %s\n", dataPointer -> Description);
        printf("Project creation date: %s\n",dataPointer->DateCreated);
        printf("Project due date: %s\n", dataPointer->DueDate);
        printf("Project members:\t");
        traverseMembers(dataPointer->personListHead);
        head = head -> next;
    }
    printf("\n\n------------------------------------------------------------------------\n\n");

}

void appendProjects(ProjectList *linkedList, ProjectInfo *newDataPointer)
{
    NodeType * newNodePointer;
    NodeType * pointer = linkedList -> head;
    NodeType * previousPointer = 0;

    if (newDataPointer == 0)
    {
        return; //nothing to add
    }

    //Create new node
    newNodePointer = (NodeType *) malloc(sizeof(NodeType));
    //assign data to new node
    newNodePointer -> projectInfoPtr = newDataPointer;
    newNodePointer -> next = 0;

    //If this is the first data point on the list, add the node to the linked list, increment the count, and exit
    if (linkedList -> head == 0)
    {
        linkedList -> head = newNodePointer;
        linkedList -> count = 1;
        return;
    }

    //Traverse through the list and find the last node
    while (pointer != 0)
    {
        previousPointer = pointer;
        pointer = pointer -> next;
    }
    previousPointer -> next = newNodePointer;
    linkedList -> count ++;
}

void traverseMembers(PersonNode * head)
{
    PersonInfo * personInfo;

    if (head == 0)
    {
        printf("Member list is empty\n");
        return;
    }

    while (head != 0)
    {
        personInfo = head->personInfoPtr;
        printf("%s\t", personInfo->PersonName);
        head = head -> next;
    }
}

void appendMembers(ProjectInfo * projectInfo, PersonInfo * newPersonInfo)
{
    PersonNode * newPersonPointer;
    PersonNode * personPointer = projectInfo -> personListHead;
    PersonNode * previousPersonPointer = 0;

    if (newPersonInfo == 0)
    {
        return; //Nothing to add
    }

    //create a node to put the data in
    newPersonPointer = (PersonNode *) malloc(sizeof(PersonInfo));
    //assign data to the node
    newPersonPointer -> personInfoPtr = newPersonInfo;
    newPersonPointer -> next = 0;

    //check to see if this is the first item on the list, set head to be new node if it is
    if (projectInfo->personListHead == 0)
    {
        projectInfo->personListHead = newPersonPointer;
        projectInfo->MembersOnProject=1;
        return;
    }

    //if not the first item, locate the end of the list
    while(personPointer != 0)
    {
        previousPersonPointer = personPointer;
        personPointer = personPointer -> next;
    }
    //attach the new node to the end of the list
    previousPersonPointer -> next = newPersonPointer;
    projectInfo ->MembersOnProject++;
}

int readProjectsFromFile(ProjectList *projectList)
{
    FILE * fp;
    fp = fopen("projects.txt", "r");

    int stopFlag = 0;

    if (fp == NULL)
    {
        printf("Error: file does not exist.");
        fclose(fp);
        return 1;
    }

    PersonInfo * newPersonInfo;
    ProjectInfo * newProjectInfo;

    while (!feof(fp))
    {
        newProjectInfo = (ProjectInfo *) malloc(sizeof(ProjectInfo));

        fgets(newProjectInfo->ProjectName, 101, fp);
        fgets(newProjectInfo -> Description,1001,fp);
        fscanf(fp,"%s", newProjectInfo->DateCreated);
        fscanf(fp,"%s", newProjectInfo->DueDate);

        PersonNode * newPersonNode = 0;

        newProjectInfo -> personListHead = newPersonNode;

        stopFlag = 0;

        while (!stopFlag)
        {
            newPersonInfo = (PersonInfo *) malloc(sizeof(PersonInfo));
            fscanf(fp, "%s", newPersonInfo->PersonName);
            if (strcmp(newPersonInfo->PersonName, "0\0\n") == 0) {
                stopFlag = 1;
                break;
            }
            appendMembers(newProjectInfo, newPersonInfo);
        }
        fgetc(fp); //clear fget buffer before next action
        appendProjects(projectList,newProjectInfo);
    }
    fclose(fp);
    return 0;
}