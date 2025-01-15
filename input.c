#include "input.h"


char* prevcomm;
struct timespec start,end;
int *timemore;

void runcommmand(char* input, int mode) {
    if (strcmp("break", input) == 0) {
        free(timemore);
        free(prevcomm);
        // also free path
        int i = 0;
        while(paths[i] != NULL) {
            free(paths[i]);
            i++;
        }
        exit(0);
    }
    char * cmd = strtok(input, " ");
    char * args[buff];
    int i = 0;
    while(cmd != 0) {
        args[i] = (char*)malloc(sizeof(char) * strlen(cmd));
        strcpy(args[i],cmd);
        i++;
        cmd = strtok(NULL," ");
    }
    args[i] = NULL;
    int len = i;
    i = 0;
    if (strcmp(args[0],"hop") == 0) {
        hop(args);
    }
    else if (strcmp(args[0],"reveal") == 0) {
        reveal(args);
    }
    else if (strcmp(args[0],"proclore") == 0) {
        proclore(args);
    }
    else if (strcmp(args[0],"seek") == 0) {
        seek(args);
    }
    else if (strcmp(args[0],"log") == 0) {
        log1(args);
    }
    else {
        if (mode == 0) {
            int pid = fork();
            if (pid == 0) {
                int stat = execvp(args[0], args);
                if (stat == -1) {
                    if (errno == 2) {
                        printf("\'%s\' : command not found\n", args[0]);
                        exit(127);
                    }
                    else perror("execvp");
                    exit(0);
                }
                exit(0);
            }
            else  if (pid < 0) {
                perror("fork");
            }
            else if (pid > 0){
                waitpid(pid,NULL,0);
            }
        }
        else if (mode == 1) {
            int pid = fork();
            if (pid < 0) {
                perror("fork");
            }
            else if (pid == 0) {
                char* filename = (char*)malloc(buff * 2 * sizeof(char));
                snprintf(filename,buff * 2,"%s/%d", home, getpid());
                FILE* file = fopen(filename,"w");
                if (file == NULL) {
                    perror("fopen");
                    exit(EXIT_FAILURE);
                }
                fprintf(file, "%s", args[0]);
                fclose(file);
                free(filename);
                int stat = execvp(args[0], args);
                if (stat == -1) {
                    if (errno == 2) {
                        printf("\'%s\' : command not found\n", args[0]);
                        exit(127);
                    }
                    else perror("execvp");
                    exit(0);
                }
                exit(0);
            }
            else if (pid > 0) {
                printf("pid : %d\n",pid);
            }
        }
    }
    // free args
    i = 0;
    while(args[i] != NULL) {
        free(args[i]);
        i++;
    }
    return;
}

int checker(char* input) {
    // if & appears just before ; then it is invalid, there can be spaces in between
    int len = strlen(input);
    int i = 0;
    int flag = 0;
    while(i < len) {
        if (flag == 0) {
            if (input[i] == '&') {
                flag = 1;
            }
        }
        else if (flag == 1) {
            if (input[i] == ';') {
            printf("bash: syntax error near unexpected token `;`\n");
                return 1;
            }
            if (input[i] == '&') {
                flag = 0;
                printf("bash: syntax error near unexpected token `&'\n");
                return 1;
            }
            else if (input[i] != ' ') flag = 0;
        }
        i++;
    }
    return 0;
}

void splitter(char* input,int mode) {
    char originalinput[buff];
    strcpy(originalinput,input);
    strcpy(prevcomm,input);
    strip(input);
    if (strstr(originalinput,"log") == NULL && mode == 0) logstore(originalinput);
    int in = checker(input);
    if (in) return;
    int totlen = strlen(input);
    int last = -1;
    if (input[totlen-1] == '&') {
        last = 1;
    }
    else last = 0;
    char delim1[] = ";";
    char delim2[] = "&";
    char* tok1;
    char * commands[buff1];
    tok1 = strtok(input,delim1);
    int i = 0;
    while(tok1 != 0) {
        strip(tok1);
        commands[i] = (char*)malloc(sizeof(char) * (strlen(tok1)+1));
        strcpy(commands[i],tok1);
        i++;
        tok1 = strtok(NULL,delim1);
    }
    commands[i] = NULL;
    int len2 = i;
    i = 0;
    int j = 0;
    clock_gettime(CLOCK_REALTIME, &start);
    while(commands[j] != NULL) {
        char* tok = strtok(commands[j],delim2);
        char* args[buff1];
        i = 0;
        while(tok != 0) {
            strip(tok);
            args[i] = (char*)malloc(sizeof(char) * (strlen(tok)+1));
            strcpy(args[i],tok);
            tok = strtok(NULL,delim2);
            i++;
        }
        // args malloc
        int len = i;
        args[i] = NULL;
        i = 0;
        while(args[i] != NULL) {
            //  include & ; in readme
            if (j != len2 - 1) {
                if (i == len-1) runcommmand(args[i],0);
                else runcommmand(args[i],1);
            }
            else {
                if (i != len - 1) {
                    runcommmand(args[i],1);
                }
                else {
                    if (last == 1) {
                        runcommmand(args[i],1);
                    }
                    else runcommmand(args[i],0);
                }
            }
            i++;
        }
        // free args
        i = 0;
        while(args[i] != NULL) {
            free(args[i]);
            i++;
        }
        j++;
    }
    // free commmands
    i = 0;
    while(commands[i] != NULL) {
        free(commands[i]);
        i++;
    }
    clock_gettime(CLOCK_REALTIME, &end);
    *timemore = end.tv_sec - start.tv_sec;
    if (*timemore < 2) *timemore = 0;
}

void getstr(char* input) {
    char c;
    int i = 0;
    scanf("%c", &c);
    input[0] = c;
    while(c != '\n') {
        input[i] = c;
        scanf("%c", &c);
        i++;
    }
    input[i] = '\0';
    return;
}

void strip(char* input) {
    int len = strlen(input);
    int i = 0;
    while(i < len && input[i] == ' ') {
        i++;
    }
    int first = i;
    i = len-1;
    while(i >= 0 && input[i] == ' ') {
        i--;
    }
    int last = i;
    int totlen = len - first - (len - last - 1);
    i = 0;
    while(i < totlen) {
        input[i] = input[first+i];
        i++;
    }
    input[i] = '\0';
    return;
}

void clear_screen() {
    printf("\033[H\033[J");
}
