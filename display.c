#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/utsname.h>
#include "display.h"
#define buff 4096

void getsysname(char *sysname) {
    struct utsname sysinfo;
    if (uname(&sysinfo) == 0) {
        strcpy(sysname, sysinfo.sysname);
    } else {
        perror("error");
        exit(1);
    }
    return;
}

void getspecialprompt(char* prompt,int tot,char* name) {
    char *username = getlogin();
    char sysname[100];
    getsysname(sysname);
    sprintf(prompt, "<\x1b[1m\x1b[92m%s@%s\x1b[0m:\x1b[1;94m%s\x1b[0m %s : %ds>", username, sysname,cwd,name,tot);
    return;
}

void getprompt(char* prompt) {
    char *username = getlogin();
    char sysname[100];
    getsysname(sysname);
    sprintf(prompt, "<\x1b[1m\x1b[92m%s@%s\x1b[0m:\x1b[1;94m%s\x1b[0m>", username, sysname,cwd);
    return;
}

void specialprintprompt(char* name,int tot) {
    char prompt[buff];
    getspecialprompt(prompt,tot,name);
    printf("%s ", prompt);
    return;
}

void printprompt() {
    char prompt[buff];
    getprompt(prompt);
    printf("%s ", prompt);
    return;
}