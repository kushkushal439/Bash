#include "log.h"


void logpurge() {
    char pathtolog[buff + 10];
    snprintf(pathtolog,buff + 10,"%s/log.txt",home);
    FILE* file = fopen(pathtolog,"w");
    if (file == NULL) {
        perror("fopen");
        return;
    }
    fclose(file);
    return;
}

void printlog() {
    char pathtolog[buff + 10];
    snprintf(pathtolog,buff + 10,"%s/log.txt",home);
    char* comms[20];
    FILE* file = fopen(pathtolog,"r");
    if (file == NULL) {
        file = fopen(pathtolog,"w");
        if (file == NULL) {
            perror("fopen");
            return;
        }
    }
    char line[buff];
    int i = 0;
    while(fgets(line,buff,file) != NULL) {
        comms[i] = (char*)malloc(sizeof(char) * (strlen(line) + 100));
        strcpy(comms[i],line);
        i++;
    }
    comms[i] = NULL;
    int len = i;
    fclose(file);
    i = 0;
    while(comms[i] != NULL) {
        printf("%s",comms[i]);
        i++;
    }
    // free comms
    i = 0;
    while(i < 0) {
        free(comms[i]);
        i++;
    }
    return;
}

void logstore(char* command) {
    // first get all commands stored in log.txt into an array of strings, then check if total is less or mroe than 15
    // if latest command in log is same as in command, then dont store it

    char pathtolog[buff + 10];
    snprintf(pathtolog,buff + 10,"%s/log.txt",home);
    char* comms[20];
    FILE* file = fopen(pathtolog,"r");
    if (file == NULL) {
        fclose(file);
        file = fopen(pathtolog,"w");
        if (file == NULL) {
            perror("fopen");
            return;
        }
        fclose(file);
        fopen(pathtolog,"r");
    }
    char line[buff];
    int i = 0;
    while(fgets(line,buff,file) != NULL) {
        comms[i] = (char*)malloc(sizeof(char) * (strlen(line) + 100));
        strcpy(comms[i],line);
        i++;
    }
    comms[i] = NULL;
    fclose(file);
    int tot = i;
    int len = strlen(comms[tot-1]);
    char c = comms[tot-1][len-1];
    comms[tot-1][len-1] = '\0';
    if (strcmp(comms[tot-1],command) == 0) return;
    comms[tot-1][len-1] = c;
    if (tot < maxcommands) {
        file = fopen(pathtolog,"a");
        if (file == NULL) {
            perror("fopen");
            // free comms
            i = 0;
            while(i < tot) {
                free(comms[i]);
                i++;
            }
            return;
        }
        fprintf(file, "%s\n", command);
        fclose(file);
    }
    else {
        file = fopen(pathtolog,"w");
        if (file == NULL) {
            perror("fopen");
            // free comms
            i = 0;
            while(i < tot) {
                free(comms[i]);
                i++;
            }
            return;
        }
        for (i = 1;i < tot;i++) {
            fprintf(file, "%s", comms[i]);
        }
        fprintf(file, "%s\n", command);
        fclose(file);
    }
    // free comms
    i = 0;
    while(i < tot) {
        free(comms[i]);
        i++;
    }
    return;
}

void log1(char* args[]) {
    char pathtolog[buff + 10];
    snprintf(pathtolog,buff + 10,"%s/log.txt",home);
    int len = 0;
    while(args[len] != NULL) len++;
    if (len >= 4) {
        printf("log : too many arguments\n");
        return;
    }
    if (len == 1) {
        printlog();
        return;
    }
    if (strcmp(args[1],"purge") == 0) {
        if (len > 2) {
            printf("log : too many arguments\n");
            return;
        }
        logpurge();
        return;
    }
    if (strcmp(args[1],"execute") == 0) {
        if (len != 3) {
            printf("log : invalid number of arguments\n");
            return;
        }
        int index = atoi(args[2]);
        // now we need to execute the index'th latest command stored in log.txt, they are stored from oldest to latest
        if (index > maxcommands || index < 0) {
            printf("log : index out of range\n");
            return;
        }
        char* comms[20];
        FILE* file = fopen(pathtolog,"r");
        if (file == NULL) {
            file = fopen(pathtolog,"w");
            if (file == NULL) {
                perror("fopen");
                return;
            }
        }
        char line[buff];
        int i = 0;
        while(fgets(line,buff,file) != NULL) {
            comms[i] = (char*)malloc(sizeof(char) * (100 + strlen(line)));
            strcpy(comms[i],line);
            i++;
        }
        comms[i] = NULL;
        int tot = i;
        fclose(file);
        int req = i - index;
        if (index == 0) {
            printf("log : index out of range\n");
            // free comms
            i = 0;
            while(i < tot) {
                free(comms[i]);
                i++;
            }
            return;
        }
        if (req < 0) {
            printf("log : index out of range\n");
            // free commms
            i = 0;
            while(i < tot) {
                free(comms[i]);
                i++;
            }
            return;
        }
        char* command = comms[req];
        int len = strlen(command);
        command[len-1] = '\0';
        splitter(command,1);
        // free comms
        i = 0;
        while(i < tot) {
            free(comms[i]);
            i++;
        }
        return;
    }
    else {
        printf("Invalid command\n");
        return;
    }
 }
