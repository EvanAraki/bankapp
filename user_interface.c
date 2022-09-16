/*****************************************************************
//
//  NAME:        Evan Araki
//  //
//  //  HOMEWORK:    project 1
//  //
//  //  CLASS:       ICS 212
//  //
//  //  INSTRUCTOR:  Ravi Narayan
//  //
//  //  DATE:        March 25, 2022
//  //
//  //  FILE:        user_interface.c
//  //
//  //  DESCRIPTION:
//  //   This file handles all the UI functions like prompting the user, 
//  //   scanning for input, and handling any user errors while inputting.
//  //
//  ****************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"

int debugmode = 0;


/****************************************************************
//
//  Function name: <getAddress>
//  //  
//  //  DESCRIPTION:   <this function takes user input to be passed as a
//  //                  char array to the database functions. Accepts multi
//  //                  line strings until char limit defined in record.h >
//  //
//  //  Parameters:    <address> (<char[]>) : <char array that will be passed>
//  //                 <max>     (<int>) : int that marks how long the address
//  //                           can be
//  //
//  //  Return values: 
//  //
//  ****************************************************************/
void getAddress(char address[], int max)
{
    char c;
    int i = 0;
    while((c=getchar()) != ';')
    {
        address[i++] = c;
    
    }
    address[i] = '\0';
}

/****************************************************************
//
//  Function name: <main>
//  //  
//  //  DESCRIPTION:   <the main function of user_interface.c this function
//  //                  does a lot. it checks if the user would like to go into
//  //                  debug or not, it takes input from the user to determine
//  //                  what menu option they would like, and it also handles
//  //                  all of the potential user misinput so only valid values
//  //                  are passed to the database functions>
//  //
//  //  Parameters:    <argc> (<int>) : <argument count>
//  //                 <argv[]> (<char array>) : <arguments the user inputs>
//  //
//  //  Return values: <int> : <does not actually return anything>
//  //
//  ****************************************************************/

int main(int argc, char *argv[])
{
    struct record * start = NULL;

    char choice[9];
    int debugerror = 0;
    int boolean = 0;
    char uname[30];
    char uaddress[50];
    int uaccountno;

    if (argc > 1)
    {
        if (argc == 2 && strcmp("debug", argv[1])==0)
        {
            printf("\n**ENTERING DEBUG**\n");
            debugmode = 1;
        }
        else if (argc >= 2 || strcmp("debug", argv[1])!=0 )
        {
            debugerror = 1;
        }
    }

    if(debugerror == 1)
    {
        printf("error, command line misinput\n");
        boolean = 1;
    }

    readfile(&start, "database.txt");

    while (boolean != 1)
    {

        printf("\nPlease select a menu option\n");
        printf("add: add a new record in the database\n");
        printf("printall: print all records in the database\n");
        printf("find: find record(s) with a specified account #\n");
        printf("delete: delete existing record(s) from the database using the account # as a key\n");
        printf("quit: quit the program\n");
        printf("\n");
        scanf("%s", choice);

    if (strncmp(choice, "add", strlen(choice)) == 0)
    {
        printf("\nEnter the account number: ");
        scanf("%d", &uaccountno);
        getchar();
        printf("\nEnter name for acount: ");
        fgets(uname, 30, stdin);
        uname[strlen(uname) - 1] = '\0';
        printf("\nEnter address(end input with a semicolon):\n");
        getAddress(uaddress, 50);
    
        if (addRecord(&start, uaccountno, uname, uaddress) == 0)
        {
            printf("\nRecord added\n");
        }
    } 

    else if (strncmp(choice, "printall", strlen(choice)) == 0)
    {
        printAllRecords(start);
    }

    else if (strncmp(choice, "find", strlen(choice)) == 0)
    {
        printf("\nEnter the account number: ");
        scanf("%d", &uaccountno);

        if (findRecord(start, uaccountno) == -1)
        {
            printf("\nThe record with that account number could not be found\n");
        }
    
    }

    else if (strncmp(choice, "delete", strlen(choice)) == 0)
    {
        printf("\nEnter the account number: ");
        scanf("%d", &uaccountno);

        if (deleteRecord(&start, uaccountno) == -1)
        {
            printf("\nThe record with that account number could not be found\n");
        }
        else
        {
            printf("\nRecord deleted\n");
        }
    
    }

    else if (strncmp(choice, "quit", strlen(choice)) == 0)
    {
        writefile(start, "database.txt");
        cleanup(&start);
        boolean = 1;
    }

    else
    {
        printf("\nInvalid option, enter a valid choice\n");
    }

    }
return 0;
}
