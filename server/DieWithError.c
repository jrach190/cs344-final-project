/***********************************************************************************************************************
 * Jonathan Rach
 * David Bethelmy
 * CS344 C Programing and Unix
 * Final Project
 * 
 * 
 * DieWithError.c
 * This file created to //TODO fill me in with file purpose
 * 
 * 
 * This file provided by David Bethelmy for use in CS344 C Programming and Unix class
 **********************************************************************************************************************/
#include <stdio.h>  /* for perror() */
#include <stdlib.h> /* for exit() */

void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}
