#ifndef _INPUT_H_
#define _INPUT_H_
#define buff 4096
// #define SA_RESTART 0x10000000
#define _XOPEN_SOURCE 500 // Required for nftw function
#define buff1 100
#define maxcommands 15
#include <stdio.h>
#include <ftw.h>
#include <sys/utsname.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "input.h"
#include "display.h"
#include "hop.h"
#include <sys/wait.h>
#include <sys/types.h>
#include "colors.h"
#include <dirent.h>
#include<signal.h>
#include<time.h>
#include <sys/stat.h>
#include<sys/resource.h>
#include "syscommand.h"
#include<pwd.h>
#include "reveal.h"
#include "proclore.h"
#include "seek.h"
#include "log.h"

extern char* prevcomm;
extern struct timespec start,end;
extern int *timemore;
extern char *paths[buff];

void getstr(char* input);
void strip(char*);
void clear_screen();
void splitter(char* input,int mode);
void runcommmand(char* input, int mode);

#endif