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
//  //  DATE:        March 25, 2022
//  //
//  //  FILE:        record.h
//  //
//  //  DESCRIPTION:
//  //   ***A header file to declare record***
//  //
//  //
//  ****************************************************************/

struct record
{
    int                accountno;
    char               name[30];
    char               address[50];
    struct record*     next;
};
