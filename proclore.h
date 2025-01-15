#ifndef _PROCLORE_H_
#define _PROCLORE_H_
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
#include<signal.h>
#include<time.h>
#include <sys/stat.h>
#include<sys/resource.h>
#include<pwd.h>
#include <ftw.h>
#include "reveal.h"
#define buff 4096

void proclore(char* args[]);

#endif