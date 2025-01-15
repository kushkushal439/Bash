#include "syscommand.h"


void zombiekiller() {
    struct sigaction sa;
    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;


    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }
}

void getcomm(int pid,char* s) {
    char path[buff * 2];
    snprintf(path,buff * 2,"%s/%d",home,pid);
    FILE* file = fopen(path,"r");
    if (file == NULL) {
        strcpy(s,"not_background");
        return;
    }
    fscanf(file,"%s",s);
    fclose(file);
    remove(path);
}

void sigchld_handler(int signum) {
    int status;
    pid_t pid;

    // Wait for all dead child processes and retrieve their status
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        // printf("Child process %d ", pid);
        char* s = (char*)malloc(buff * 2 * sizeof(char));
        getcomm(pid,s);
        if (strcmp(s,"not_background") == 0) {
            free(s);
            continue;
        }
        int exitstat = WEXITSTATUS(status);
        if (exitstat == 127) {
            printf("%s : Command not found ; Exit 127\n", s);
            free(s);
            continue;
        }
        if (WIFEXITED(status)) {
            printf("%s exited normally (%d) \n", s,pid);
        } else if (WIFSIGNALED(status)) {
            printf("%s exited abnormally by signal %d (%d)", s,WTERMSIG(status),pid);
        } else if (WIFSTOPPED(status)) {
            printf("%s stopped by signal %d (%d)", s,WSTOPSIG(status),pid);
        }
        free(s);
    }
}
