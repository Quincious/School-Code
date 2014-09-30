
// Jonathan Hart
// cs620 Assignment2 Part 2
// myhistory.h

#ifndef MYHISTORY_H
#define MYHISTORY_H

#define CMD_MAX_LENGTH 256

char history[100][80];
int historycount;

void executecmd();
void shifthistory();
void printhistory();

#endif
