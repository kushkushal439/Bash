#ifndef _DISPLAY_H
#define _DISPLAY_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define _XOPEN_SOURCE 500
#include <ftw.h>
#define buff 4096

extern char cwd[buff];
extern char home[buff];

void getprompt(char* prompt);
void printprompt();
void getsysname(char *sysname);
void specialprintprompt(char* ,int );
void getspecialprompt(char* prompt,int tot,char * name);

#endif