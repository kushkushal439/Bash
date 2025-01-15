#ifndef _REVEAL_H_
#define _REVEAL_H_

#define _XOPEN_SOURCE 500
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/utsname.h>
#include <dirent.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<ftw.h>
#include<sys/types.h>
#include "hop.h"
#include<sys/stat.h>
#include<pwd.h>
#include<time.h>
#include "input.h"
#include "display.h"
#define buff1 100
#define buff 4096

extern char cwd[buff];
extern char home[buff];
extern char prev[buff];

void reveal(char* args[]);
void print_permissions(int mode);
void printextra(char* file,char* fileperu,int l);
void reveal(char * args[]);


#endif