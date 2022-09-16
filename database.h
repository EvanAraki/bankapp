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
//  //   ***this is an header file to declare the database function***
//  //
//  //
//  ****************************************************************/

#include "record.h"

int addRecord (struct record **, int, char [ ],char [ ]);
void printAllRecords(struct record *);
int findRecord (struct record *, int);
int deleteRecord(struct record **, int);
int readfile(struct record **, char []);
int writefile(struct record *, char []);
void cleanup(struct record **);
