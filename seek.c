#include "seek.h"

char *paths[buff];
char search[buff];
int filecount = 0;


int process_file(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
    // printf("fileprocess is %s\seekn", fpath);
    int lens = strlen(search);
    char in[buff];
    strcpy(in,fpath + ftwbuf->base);
    // printf("in is %s\n", in);
    if (strncmp(in,search,lens) == 0) {
        paths[filecount] = (char*) malloc(sizeof(char) * buff);
        strcpy(paths[filecount],fpath);
        // printf("inside is %s\n", paths[filecount]);
        filecount++; 
    }
    return 0;
}

void print_seek(char* c, const char* start) {
    // if file at c is directory, print in blue else print in green
    struct stat fileStat;
    if (stat(c, &fileStat) == -1) {
        perror("stat");
        return;
    }
    if (S_ISDIR(fileStat.st_mode)) {
        printf("\x1b[94m");
    } else {
        printf("\x1b[92m");
    }
    if (strncmp(c, start, strlen(start)) == 0) {
        printf(".%s\n", c + strlen(start));
    } else {
        printf("%s\n", c);  // If start is not a prefix, print full path
    }
    printf("\x1b[0m");
}

// hop wrong multiple



void seek(char* args[]) {
    for (int i = 0;i < filecount ; i++) free(paths[i]);
    filecount = 0;
    int len = 0;
    int i = 0;
    while(args[i] != NULL) {
        len++;
        i++;
    }
    len = i; i = 0;
    int other = 0;
    int d = 0,f = 0,e = 0;
    char path[buff] = "";
    search[0] = '\0';
    int c = 0;
    i = 1;
    while(args[i] != NULL) {
        if (args[i][0] == '-' && args[i][1] != '\0') {
            int j = 1;
            while(args[i][j] != '\0') {
                if (args[i][j] == 'd') {
                    d = 1;
                }
                else if (args[i][j] == 'f') {
                    f  = 1;
                }
                else if(args[i][j] == 'e')  {
                    e = 1;
                }
                else {
                    other = 1;
                }
                j++;
            }
        }
        else {
            if (c == 0)  {
                strcpy(search,args[i]);
                c = 1;
            }
            else if (c == 1) {
                strcpy(path,args[i]);
                c = 2;
            }
            else if (c == 2) {
                c = 3;
            }
        }
        i++;
    }
    if (c == 0) {
        printf("Invalid command\n");
        return;
    }
    if (c == 3) {
        printf("Invalid command\n");
        return;
    }
    if (c == 1) {
        getcwd(path,buff);
    }
    // write in readme about -defe flag
    if (other == 1 || (d == f && f == 1)) {
        printf("Invalid flags \n");
        return;
    }
    char start[buff];
    strcpy(start,path);
    if (!((path[0] == '/') || path[0] == '-' || path[0] == '~')) {
        // strcpy(start,home);
        getcwd(start,buff);
        int leng = strlen(start);
        int k = leng;
        start[k] = '/';
        k++;
        while(path[k - leng - 1] != '\0') {
            start[k] = path[k-leng - 1];
            k++;
        }
        start[k] = '\0';
    }
    converter(start,start);
    // printf("start is %s\n", start);
    expand(start);
    // for (i = 0;i < filecount;i++) printf("%s is string\n", paths[i]);
    // printf("start is %s\n", start);
    if (nftw(start, process_file, 25, 0) == -1) {
        if (strlen(start) == 0) {
            printf("bash: hop: OLDPWD not set\n");
            return;
        }
        perror("nftw");
        return;
    }
    // printf("%d is count\n", filecount);
    if (filecount == 0) {
        printf("No matching file found\n");
        return;
    }
    // for (i = 0;i < filecount;i++) printf("%s is string\n", paths[i]);
    if (e == 1) {
        if (filecount == 1) {
            const char* filename = paths[0];
            struct stat fileStat;
            if (stat(filename, &fileStat) == -1) {
                perror("stat");
                return;
            }
            if (S_ISDIR(fileStat.st_mode)) {
                if (f == 1 ) {
                    printf("No matching file found\n");
                    return;
                } 
                if (access(filename, X_OK) == -1) {
                    printf("Missing permissions for task!\n");
                    return;
                }
                char *argv[3];
                argv[0] = (char*)malloc(sizeof(char) * 10);
                argv[1] = (char*)malloc(sizeof(char) * buff);
                strcpy(argv[0],"Hop");
                strcpy(argv[1],filename);
                argv[2] = NULL;
                print_seek(paths[0],start);
                hop(argv);
                // free argv
                free(argv[0]);
                free(argv[1]);
                free(argv[2]);
                return;
            }
            else {
                if (d == 1) {
                    printf("No matching file found\n");
                    return;
                }
                if (access(filename, R_OK) == -1) {
                    printf("Missing permissions for task!\n");
                    return;
                }
                FILE* reader = fopen(paths[0],"r");
                if (reader) {
                    print_seek(paths[0],start);
                    char line[256];
                    while(fgets(line,sizeof(line),reader)) {
                        printf("%s", line);
                    }
                    printf("\n");
                    fclose(reader);
                    return;
                }
            }
        }
    }
    int cnt = 0;
    for (i = 0;i < filecount;i++) {
        const char* filename = paths[i];
        struct stat fileStat;
        if (stat(filename, &fileStat) == -1) {
            perror("stat");
            filecount = 0;
            return;
        }
        if (d != 1 && f != 1) {
            print_seek(paths[i],start);
            cnt++;
            continue;
        }
        if (d == 1) {
            if (S_ISDIR(fileStat.st_mode)) {
                // printf("%s\n", paths[i]);
                print_seek(paths[i],start);
                cnt++;
                continue;
            }
        }
        if (f == 1) {
            if (!(S_ISDIR(fileStat.st_mode))) {
                // printf("%s\n", paths[i]);
                print_seek(paths[i],start);
                cnt++;
                continue;
            }
        }
    }
    if (cnt == 0) {
        printf("No matching file found\n");
    }
    return;
}