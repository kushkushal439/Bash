#ifndef _SYSCOMM_H_
#define _SYSCOMM_H_

#define _XOPEN_SOURCE 500
#include <stdio.h>
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
#include <ftw.h>
#include<signal.h>
#include<time.h>
#include <sys/stat.h>
#include<sys/resource.h>
#include<pwd.h>
#include "reveal.h"
#include "proclore.h"
#define buff 4096
#define buff1 100
#define SA_RESTART 0x10000000
extern char home[buff];

void zombiekiller();
void getcomm(int pid,char* s);
void sigchld_handler(int signum);

#endif