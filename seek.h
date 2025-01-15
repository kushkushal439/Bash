#ifndef _SEEK_H_
#define _SEEK_H_

#define buff 4096
// #define SA_RESTART 0x10000000
#define buff1 100
#define _XOPEN_SOURCE 500 // Required for nftw function
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
#include "log.h"
#include "reveal.h"
#include "proclore.h"

extern char *paths[buff];
extern char search[buff];
extern int filecount;


void seek(char* args[]);
void print_seek(char* c, const char* start) ;
int process_file(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf);

#endif