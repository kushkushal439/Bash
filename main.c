#define buff 4096
// #define SA_RESTART 0x10000000
#define buff1 100
#define _XOPEN_SOURCE 500 // Required for nftw function
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

extern int *timemore;
// hop middle erroneous doing

int main() {
    gethome();
    zombiekiller();
    timemore = malloc(sizeof(int));
    *timemore = 0;
    prevcomm = (char*)malloc(sizeof(char) * (buff+1));
    while(1) {
        if (*timemore) {
            specialprintprompt(prevcomm,*timemore);
            *timemore = 0;
        }
        else {
            *timemore = 0;
            printprompt();
        }
        char input[buff];
        getstr(input);
        splitter(input,0);
    }
}
