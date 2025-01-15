#include "proclore.h"


void proclore(char* args[]) {
    int len = 0;
    int i = 0;
    while(args[i] != NULL) {
        i++;
    }
    len = i;
    i = 0;
    int pid = 0;
    if (len > 2) {
        printf("Too many arguments\n");
        return;
    }
    if (len == 1) pid = getpid();
    else {
        pid = atoi(args[1]);
    }
    char path[buff * 2];
    snprintf(path,buff * 2,"/proc/%d/stat", pid);
    FILE* file = fopen(path,"r");
    if (file == NULL) {
        perror("fopen");
        return;
    }
    i = 1;
    char exe_stat[256];
    char status_file[256];
    char pid_string[256];
    char state[10];
    char groupid[50];
    char virtual_size[50];
    char foregroupid[50];
    char tmp[buff];
    while(i <= 24) {
        fscanf(file,"%s",tmp);
        if (i == 1) {\
            strcpy(pid_string,tmp);
        }
        else if (i == 3) {
            strcpy(state,tmp);
        }
        else if (i == 5) {
            strcpy(groupid,tmp);
        }
        else if (i == 23) {
            strcpy(virtual_size,tmp);
        }
        else if (i == 8) {
            strcpy(foregroupid,tmp);
        }
        i++;
    }
    fclose(file);
    snprintf(path,buff*2,"/proc/%d/exe",pid);
    int len1 = readlink(path,exe_stat,256);
    if (len1 == -1) {
        perror("readlink");
        return;
    }
    exe_stat[len1] = '\0';
    printf("PID : %s\n\n",pid_string);
    if (strcmp(foregroupid,groupid) == 0) {
        printf("Process Status : %s+\n\n",state);
    }
    else {
        printf("Process Status : %s\n\n",state);
    }
    printf("Process group : %s\n\n",groupid);
    printf("Virtual Memory : %s\n\n",virtual_size);
    printf("Executable path : %s\n\n",exe_stat);
}