#ifndef _HOP_H_
#define _HOP_H_
#define _XOPEN_SOURCE 500
#include<stdio.h>
#include "input.h"
#include "display.h"
#include<stdlib.h>
#include <ftw.h>
#include<string.h>
#include<unistd.h>
#include<sys/utsname.h>
#define buff 4096
#define buff1 100

extern char cwd[buff];
extern char home[buff];
extern char prev[buff];

void gethome();

void updatecwd();

int dohop(char*);

void hop(char* args[]);

void converter(char* b,char* a);

void expand(char* path);



#endif