#include "hop.h"

char cwd[buff];
char home[buff];
char prev[buff];

void gethome() {
    getcwd(home,buff);
    cwd[0] = '~';
    cwd[1] = '\0';
    prev[0] = '\0';
}

void updatecwd() {
    getcwd(cwd,buff);
    int len = strlen(home);
    int i = 0;
    while(i < len) {
        if (cwd[i] == home[i]) i++;
        else break;
    }
    if (i < len) {
        return;
    }
    else {
        char newcwd[buff] = "~";
        int j = 1;
        while(cwd[len + j - 1] != '\0') {
            newcwd[j] = cwd[len + j - 1];
            j++;
        }
        strcpy(cwd,newcwd);
    }
}

void converter(char* b,char* a) {
    int len = strlen(home);
    int len2 = strlen(a);
    int i = 0;
    while(i < len) {
        if (len2 < len) break;
        if (a[i] == home[i]) i++;
        else break;
    }
    if (i < len) {
        strcpy(b,a);
        return;
    }
    else {
        char newcwd[buff] = "~";
        int j = 1;
        while(a[len + j - 1] != '\0') {
            newcwd[j] = a[len + j - 1];
            j++;
        }
        newcwd[j] = '\0';
        strcpy(b,newcwd);
    }
}

void expand(char* path) {
    int len = strlen(path);
    if (path[0] == '-') {
        strcpy(path,prev);
        if (strlen(path) == 0) return;
    }
    if (path[0] == '~') {
        char newpath[buff];
        int temp = 0;
        while(home[temp] != '\0') {
            newpath[temp] = home[temp];
            temp++;
        }
        newpath[temp] = '\0';
        int i = strlen(newpath);
        int j = 1;
        while(path[j] != '\0') {
            newpath[i] = path[j];
            j++;
            i++;
        }
        newpath[i] = '\0';
        strcpy(path,newpath);
        return;
    }
    else if (path[0] != '~') return;
}


int dohop(char* dir1) {
    char dir[buff];
    strcpy(dir,dir1);
    if (strcmp(dir,"-") == 0) {
        int prevlen = strlen(prev);
        if (prevlen == 0) {
            fprintf(stderr, "bash: hop: OLDPWD not set\n");
            return -1;
        }
        strcpy(dir,prev);
    }
    converter(dir,dir);
    expand(dir);
    int stat = chdir(dir);
    if (stat != 0) {
        perror("chdir");
        return -1;
    }
    return 1;
}

void hop(char* args[buff1]) {
    int i = 0;
    while(args[i] != NULL) i++;
    int len = i;
    i = 1;
    if (len == 1) {
        int stat = dohop(home);
        if (stat != -1) strcpy(prev,cwd);
        if (stat != -1) updatecwd();
    }
    while(args[i] != NULL) {
        int stat = dohop(args[i]);
        if (stat != -1) {
            strcpy(prev,cwd);
            updatecwd();
            char temp[buff];
            getcwd(temp,buff);
            printf("%s\n", temp);
        }
        if (stat != -1) updatecwd();
        i++;
    }
    return;
}