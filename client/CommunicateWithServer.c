/***********************************************************************************************************************
 * Jonathan Rach
 * David Bethelmy
 * CS344 C Programing and Unix
 * Final Project
 *
 *
 * CommunicateWithServer.c
 * This file created to //TODO fill me in with file purpose
 *
 *
 *
 **********************************************************************************************************************/
#include "TCPClient.h"

#define MENUOPTIONLENGTH 30

typedef char BYTE;

typedef struct menu
{
    char line1[MENUOPTIONLENGTH];
    char line2[MENUOPTIONLENGTH];
    char line3[MENUOPTIONLENGTH];
    char line4[MENUOPTIONLENGTH];
}Menu;

typedef struct ProjectMenu
{
    char create[MENUOPTIONLENGTH];
    char edit[MENUOPTIONLENGTH];
    char delete[MENUOPTIONLENGTH];
    char save[MENUOPTIONLENGTH];
    char display[MENUOPTIONLENGTH];
    char exit[MENUOPTIONLENGTH];
}ProjectMenu;

typedef struct project
{
    char ProjectName[101]; //Project name, max 100 characters, plus space for '\0'
    char Description[1001]; //Project description, max 1000 characters, plus space for '\0'
    char DateCreated[9]; //Project creation date, max 8 characters, plus space for '\0'
    char DueDate[9]; //Project due date, max 8 characters, plus space for '\0'
    BYTE MembersOnProject; //byte containing number of members on a project
}Project;

unsigned int signInDialog(int);
unsigned int signUpDialog(int);
unsigned int getProjectsMenuDialogResult(int);
unsigned int displayMenuAndSendSelection(int);
unsigned int displayProject(int);



void communicateWithServer(int socket)
{
    unsigned int selection = 0;
    unsigned int systemStatusNotifier = 0;
    while(1)
    {
        selection = displayMenuAndSendSelection(socket);
        get(socket, &systemStatusNotifier, sizeof(unsigned int));

        systemStatusNotifier = ntohl(systemStatusNotifier);

        switch(selection)
        {
            case 1:
                systemStatusNotifier = 4;
                break;
            case 2:
                systemStatusNotifier = 2;
                break;
            default:
                break;
        }

        printf("\n%d selected.\n", selection);
        switch (systemStatusNotifier)
        {
            case 1:
                getProjectsMenuDialogResult(socket);
                break;
            case 2:
                signUpDialog(socket);
                break;
            case 4:
                signInDialog(socket);
                break;
        }
        if (selection==3) break;
    }
}

unsigned int displayMenuAndSendSelection(int sock)
{
    Menu menuBuffer;     //Buffer for main menu
    unsigned int response = 0;
    unsigned int output;

    get(sock, &menuBuffer, sizeof(Menu));  //in this case server is also sending null
    printf("%s\n", menuBuffer.line1);
    printf("%s\n", menuBuffer.line2);
    printf("%s\n", menuBuffer.line3);
    scanf("%d", &response);
    output = htonl(response);
    put(sock, &output, sizeof(unsigned int));
    return response;
}

unsigned int displayProjectMenuAndSendSelection(int sock)
{
    ProjectMenu menuBuffer; //Buffer for project menu
    unsigned int response = 0;
    unsigned int output;
    get(sock, &menuBuffer, sizeof(ProjectMenu));
    printf("%s\n",menuBuffer.create);
    printf("%s\n",menuBuffer.edit);
    printf("%s\n",menuBuffer.delete);
    printf("%s\n",menuBuffer.save);
    printf("%s\n",menuBuffer.display);
    scanf("%d", &response);
    output = htonl(response);
    put(sock, &output, sizeof(unsigned int));
    return response;
}

unsigned int signInDialog(int sock)
{
    Menu menuBuffer;

    char * username;
    char * password;

    memset(&menuBuffer, 0, sizeof(Menu));

    get(sock, &menuBuffer, sizeof(Menu));
    printf("%s\n", menuBuffer.line1);
    printf("%s\n", menuBuffer.line2);
    scanf(username);
    printf("%s\n", menuBuffer.line3);
    scanf(password);
    put(sock, username, strlen(username));
    put(sock, password, strlen(password));
}

unsigned int signUpDialog(int sock)
{
    Menu menuBuffer;

    char * username;
    char * password;
    char * fullname;

    memset(&menuBuffer, 0, sizeof(Menu));
    get(sock, &menuBuffer, sizeof(Menu));
    printf("%s\n", menuBuffer.line1);
    printf("%s\n", menuBuffer.line2);
    scanf(username);
    printf("%s\n", menuBuffer.line3);
    scanf(password);
    printf("%s\n", menuBuffer.line4);
    put(sock, username, strlen(username));
    put(sock, password, strlen(password));
    put(sock, fullname, strlen(fullname));
}

unsigned int getProjectsMenuDialogResult(int sock)
{
    ProjectMenu projectMenu;
    unsigned int response = 0;
    unsigned int output;

    memset(&projectMenu, 0, sizeof(projectMenu));
    get(sock,&projectMenu, sizeof(projectMenu));
    printf("%s\n", projectMenu.create);
    printf("%s\n",projectMenu.edit);
    printf("%s\n",projectMenu.delete);
    printf("%s\n",projectMenu.save);
    printf("%s\n",projectMenu.display);
    printf("%s\n",projectMenu.exit);

    scanf("%d",&response);
    output = htonl(response);
    put(sock, output, sizeof(unsigned int));

    return response;
}

unsigned int displayProject(int sock)
{
    Project project;
    unsigned int output = 1;

    memset(&project, 0, sizeof(Project));

    get(sock, &project, sizeof(Project));
    printf("%s\n", project.ProjectName);
    printf("%s\n",project.Description);
    printf("%s\n",project.DateCreated);
    printf("%s\n",project.DueDate);
    printf("%d\n",project.MembersOnProject);

    output = htonl(output);
    put(sock, &output, sizeof(unsigned int));
}