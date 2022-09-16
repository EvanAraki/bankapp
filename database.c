/*****************************************************************
//
//  NAME:        ***Evan Araki***
//  //
//  //  HOMEWORK:    project1
//  //
//  //  CLASS:       ICS 212
//  //
//  //  INSTRUCTOR:  Ravi Narayan
//  //
//  //  DATE:        March 25th, 2022
//  //
//  //  FILE:        database.c
//  //
//  //  DESCRIPTION:
//  //              This is the backend portion of our banking software, it
//  //              handles all of the operations that are called by the user interface
//  //              Adds records, deletes, finds, displays, reads and writes to a file, and
//  //               clears the heap.
//  //
//  //
//  ****************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"


extern int debugmode;
/****************************************************************
//
//  Function name: <addRecord>
//  //  
//  //  DESCRIPTION:   Adds records to the database in descending order, will
//  //                 not add if there is a duplicate.
//  //
//  //  Parameters:    <accountno> (<int>) : <account number>
//  //                 <name> (<char[]>) : <the user's name>
//  //                 <address> (<char[]>) : <the user's address>
//  //                 <start> (record**) : <double pointer to record>                   
//  //
//  //  Return values: 0 : successfully added record
//  //                 -1 : duplicate record in list, not added
//  //
//  ****************************************************************/
int addRecord (struct record **start, int accountno, char name[ ],char address[ ])
{
    int boolean = 1;
    struct record *curr, *temp,  *newRec;
    curr = *start;

    if(debugmode)
    {
        printf("\n**DEBUG** addRecord. accountno: %d,  name: %s, address: %s\n", accountno, name, address);
    }

    if (*start == NULL)
    {
        newRec = (struct record*)malloc(sizeof(struct record));
        newRec->accountno = accountno;
        strcpy((newRec->name), name);
        strcpy((newRec->address), address);  
        newRec->next = NULL;
        *start = newRec;
    }
    else if (curr->accountno > accountno)
    {
        newRec = (struct record*)malloc(sizeof(struct record));
        newRec->accountno = accountno;
        strcpy((newRec->name), name);
        strcpy((newRec->address), address);
        newRec->next = *start;
        *start = newRec;
    }
    else
    {
        curr = *start;
        temp = curr;

        while(boolean == 1 && curr != NULL )
        {
        
            if (curr->accountno > accountno)
            {
                newRec = (struct record*)malloc(sizeof(struct record));
                newRec->accountno = accountno;
                strcpy((newRec->name), name);
                strcpy((newRec->address), address);
                newRec->next = curr;
                temp->next = newRec;
                boolean = 0;
            }

            else if (curr->next == NULL)
            {
                newRec = (struct record*)malloc(sizeof(struct record));
                newRec->accountno = accountno;
                strcpy((newRec->name), name);
                strcpy((newRec->address), address);
                curr->next = newRec;
                newRec->next = NULL;
                boolean = 0;
            }
            else
            {
                temp = curr;
                curr = curr->next;
            }
        }
    }   

return 0;
}

/****************************************************************
//
//  Function name: <findRecord>
//  //  
//  //  DESCRIPTION:    uses provided user account number to locate record
//  //                  associated.
//  //
//  //  Parameters:    <accountno> (<int>) : <user account number>
//  //                 <start> (record*) : <pointer to start of record>
//  //
//  //  Return values: <int> : 0 : record found
//  //                         -1 : record not found
//  //
//  ****************************************************************/
int findRecord (struct record *start, int accountno)
{
    int found = -1;
    struct record *curr;
    curr = start;

    if (debugmode)
    {
        printf("\n**DEBUG** findRecord. accountnumber: %d\n", accountno);
    }

    while (curr != NULL)
    {
        if (accountno == curr->accountno)
        {
            printf("***************************************************************\n");
            printf("%d\n", curr->accountno);
            printf("%s\n", curr->name);
            printf("%s\n", curr->address);
            printf("***************************************************************\n");
            printf("\n");
            found = 0;
        }

    curr = curr->next;
    }

return found;
}

/****************************************************************
//
//  Function name: <printAllRecords>
//  //  
//  //  DESCRIPTION:   Prints all records stored in the database
//  //
//  //  Parameters:    <start> (<record>) : pointer to the start of record
//  //
//  //  Return values: 
//  //
//  ****************************************************************/
void printAllRecords(struct record *start)
{

    struct record *curr;
    curr = start;

    if (debugmode)
    {
    printf("\n**DEBUG** printALlRecords.\n");
    }

    printf("\n**ALL RECORDS**\n");  
    while (curr != NULL)
    {
        printf("***************************************************************\n");
        printf("%d\n", curr->accountno);
        printf("%s\n", curr->name);
        printf("%s\n", curr->address);
        printf("***************************************************************\n");
        printf("\n");
        curr = curr->next;
    }

}

/****************************************************************
//
//  Function name: <deleteRecord>
//  //  
//  //  DESCRIPTION:    deletes record from database using user input account num
//  //                  to find the record and frees heap space. 
//  //
//  //  Parameters:    <accountno> (<int>) : <account number from user>
//  //                 <start> (record**) : double pointer to the start of record
//  //
//  //  Return values: <int> : 0 : record deleted 
//  //                         -1 : record not found 
//  //
//  ****************************************************************/
int deleteRecord(struct record **start, int accountno)
{
    int deleted = -1;
    struct record *prev, *curr, *temp;
    prev = *start;
    curr = *start;

    if (debugmode)
    {
        printf("\n**DEBUG** deleteRecord. accountnum: %d\n", accountno);
    }

    while (curr != NULL)
    {
        if (curr == *start)
        {
            if (accountno == curr->accountno)
            {
                temp = curr;
                *start = curr->next;
                curr = curr->next;
                prev = prev->next;
                free(temp);
                deleted = 0;
            }
            else
            {
                curr = curr->next;
            }
        }
        else if (accountno == curr->accountno)
        {
            temp = curr;
            prev->next = curr->next;
            curr = curr->next;
            free(temp);
            deleted = 0;
        }
        else
        {
            prev = prev->next;
            curr = curr->next;
        }
    }
return deleted;
}





/*****************************************************************
//
//  Function name: <readfile>
//  //  
//  //    DESCRIPTION:   reads file using provided filename
//  //                    
//  //  
//  //    Parameters:    <filename> (char[]): name of file to be read
//  //                   <start>    (record**): double pointer to start of record
//  //  
//  //    Return values: <int> : 0: file has been read
//  //                           -1: File has not ben read
//  //  
//  //  ****************************************************************/

int readfile (struct record ** start, char filename[])
{
    int read = 0;
    int accountno;
    char name[30];
    char address[50];
    FILE *fp;

    if (debugmode)
    {
    printf("\n**DEBUG** readfile. filename: %s\n", filename);
    }  

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        read = -1;
    }
    else
    {
        while (fscanf(fp, "%d\n", &accountno) != EOF)
        {
            fgets(name, 30, fp);
            name[strlen(name) - 1] = '\0';
        
            fgets(address, 50, fp);
            address[strlen(address) - 1] = '\0'; 
        
            addRecord (start, accountno, name, address);

    }

    fclose(fp);

}
return read;

}
/*****************************************************************
//
//  Function name: writefile
//  //  
//  //   DESCRIPTION:    writes to file using filename provided, if the file cannot be
//  //                   opened or does not exist a new file is created.
//  //  
//  //    Parameters:    start (record*) : pointer to start of record
//  //                   filename (char[]) : name of file
//  // 
//  //    Return values:  0 : success
//  //                    -1 : failure
//  //  
//    ****************************************************************/
int writefile (struct record *start, char filename[])
{
    int wrote = 0;
    struct record * node;
    FILE *fp;
    node = start;

    if (debugmode)
    {
        printf("\n**DEBUG** writefile. filename: %s\n", filename);
    }


    if ((fp = fopen(filename, "w")) == NULL)
    {
        wrote = -1;
    }
    else
    {
        while (node != NULL)
        {
        fprintf(fp, "%d\n", node->accountno);
        fprintf(fp, "%s\n", node->name);
        fprintf(fp, "%s\n", node->address);
        fprintf(fp, "\n");
        node = node->next;
        }
        fclose(fp);
    }

return wrote;
}



/*****************************************************************
//
//  Function name: cleanup
//  // 
//  //  DESCRIPTION:    clears all heap space and if start still holds a record, sets tp null
//  // 
//  //   Parameters:    start (record**) double pointer to start of record
//  //
//  //   Return values: 
//  //                   
//  // 
//   ****************************************************************/

void cleanup (struct record **start)
{
struct record *curr, *prev;
curr = NULL;
prev = NULL;
curr = *start;

if (debugmode)
{
    printf("\n**DEBUG** cleanup. \n");
}

while (curr != NULL)
{
    prev = curr;
    curr = curr->next;
    free(prev);
}

if (start != NULL)
{
    *start = NULL;
}

}

