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

#include "ProjectsFunctions.h"

//Main for testing the projects functions, not required for use of full program
//int main(int argc, char *argv[])
//{
//    NodeType * head = 0;
//    ProjectList projectList;
//
//    projectList.head = head;
//    projectList.count = 0;
//
//    readProjectsFromFile(&projectList, "rachj@my.erau.edu", strlen("rachj@my.erau.edu"));
//    traverseProjects(projectList.head);
//}

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
        printf("%d Project members:\t",dataPointer->MembersOnProject);
        traverseMembers(dataPointer->personListHead);
        head = head -> next;
    }
    printf("\n\n------------------------------------------------------------------------\n\n");
}

NodeType * findProjectByUserName(ProjectList * linkedList, char * projectToFind)
{
    NodeType * head = linkedList->head;
    NodeType * nullNode = 0;
    ProjectInfo * dataPointer;

    if (head == 0)
    {
        return nullNode; //linked list empty, nothing to find
    }

    dataPointer = (ProjectInfo *) malloc(sizeof(ProjectInfo));

    while (head != 0)
    {
        dataPointer = head->projectInfoPtr;

        if (!strcmp(dataPointer->ProjectName,projectToFind))
        {
            return head;
        }
        head = head -> next;
    }
    printf("Client searched for %s but %s was not found.\n", projectToFind, projectToFind);
    return  nullNode; //Node not found
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

int readProjectsFromFile(ProjectList *projectList, char *userName, size_t lengthOfUserName)
{
    lengthOfUserName+=1; //Account for the '\0' character in further operators
    char fileExtension[36];
    strncpy(fileExtension, userName, lengthOfUserName);
    puts(fileExtension);
    strcat(fileExtension,".proj");
    puts(fileExtension);

    FILE * fp;
    fp = fopen(fileExtension, "r");


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

        fgets(newProjectInfo->ProjectName, 101, fp); //size of project name
        fgets(newProjectInfo -> Description, 1001,fp); //size of description of project
        fscanf(fp,"%s", newProjectInfo->DateCreated);
        fscanf(fp,"%s", newProjectInfo->DueDate);

        PersonNode * newPersonNode = 0;

        newProjectInfo -> personListHead = newPersonNode;

        stopFlag = 0;

        while (!stopFlag)
        {
            newPersonInfo = (PersonInfo *) malloc(sizeof(PersonInfo));
            fgets(newPersonInfo->PersonName, 51,fp); //size of name of person on project
            if (newPersonInfo->PersonName[0] == '0')
            {
                newProjectInfo->MembersOnProject--; //decrement count to accurately reflect number of members in project
                stopFlag = 1;
                break;
            }
            appendMembers(newProjectInfo, newPersonInfo);
        }
        appendProjects(projectList,newProjectInfo);
    }
    fclose(fp);
    return 0;
}