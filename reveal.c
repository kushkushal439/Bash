#include "reveal.h"

void print_permissions(int mode) {
    if (S_ISDIR(mode)) {
        printf("d");
    }
    else if (S_ISREG(mode)) printf("-");


    printf( (mode & S_IRUSR) ? "r" : "-");
    printf( (mode & S_IWUSR) ? "w" : "-");
    printf( (mode & S_IXUSR) ? "x" : "-");

    printf( (mode & S_IRGRP) ? "r" : "-");
    printf( (mode & S_IWGRP) ? "w" : "-");
    printf( (mode & S_IXGRP) ? "x" : "-");

    printf( (mode & S_IROTH) ? "r" : "-");
    printf( (mode & S_IWOTH) ? "w" : "-");
    printf( (mode & S_IXOTH) ? "x" : "-");
}

int myfunc(const void* a,const void* b) {
    return strcmp(*(char**)a,*(char**)b);
}

void printextra(char* file,char* fileperu,int l) {
        const char* filename = file;
        struct stat fileStat;
        if (stat(filename, &fileStat) == -1) {
            perror("stat");
            return;
        }
        struct passwd *pw1 = getpwuid(fileStat.st_uid);
        if (pw1 == NULL) {
            perror("getpwuid");
            return;
        }
        struct passwd *pw2 = getpwuid(fileStat.st_gid);
        if (pw2 == NULL) {
            perror("getpwuid");
            return;
        }
        char time1[80];
        struct tm *tm_info = localtime(&fileStat.st_mtime);
        strftime(time1, sizeof(time1), "%b %d %H:%M", tm_info);
        if (l == 1 ) {
            print_permissions(fileStat.st_mode);
            printf("\t");
            printf("%ld\t", fileStat.st_nlink);
            printf("%s\t%s\t", pw1->pw_name,pw2->pw_name);
            printf("%ld\t", fileStat.st_size);
            printf("%s\t", time1);
        }
        if (S_ISDIR(fileStat.st_mode)) {
            printf("\x1b[1;94m%s\x1b[0m\n", fileperu);
        }
        else if (fileStat.st_mode & S_IXUSR) {
            printf("\x1b[1;92m%s\x1b[0m\n", fileperu);
        }
        else if (S_ISREG(fileStat.st_mode)) {
            printf("%s\n", fileperu);
        }
        else
        printf("%s\n", fileperu);
}

void reveal(char * args[]) {
    int i = 0;
    while(args[i] != NULL) i++;
    int len = i;
    i = 0;
    int l = 0;
    int a = 0;
    int other = 0;
    i = 1;
    char path[buff];
    getcwd(path,buff);
    while(args[i] != NULL) {
        if (args[i][0] == '-' && args[i][1] != '\0') {
            int j = 1;
            while(args[i][j] != '\0') {
                if (args[i][j] == 'l') l = 1;
                else if (args[i][j] == 'a') a = 1;
                else {
                    printf("reveal: invalid option -- \'%c\'\n", args[i][j]);
                    other = 1;
                    return;
                }
                j++;
            }
            i++;
            continue;
        }
        if (args[i][0] == '-' && args[i][1] == '\0') {
            strcpy(path,prev);
            break;
        }
        strcpy(path,args[i]);
        break;
    }
    converter(path,path);
    expand(path);
    char files1[buff1][buff1];
    DIR* dr = opendir(path);
    if (dr == NULL) {
        if (strlen(path) == 0) {
            printf("bash: cd: OLDPWD not set\n");
            return;
        }
        // now check if path is a file and print the file name
        struct stat fileStat;
        if (stat(path, &fileStat) == -1) {
            perror("stat");
            return;
        }
        if (a == 0) {
            if (path[0] == '.') return;
        }
        if (l == 1) printextra(path,path,l);
        else printf("%s\n",path);
        return;
    }
    struct dirent* r;
    r = readdir(dr);
    i = 0;
    while(r != NULL) {
        strcpy(files1[i],r->d_name);
        i++;
        r = readdir(dr);
    }
    closedir(dr);
    int len1 = i;
    i = 0;
    char *file[len1];
    for (int i = 0;i < len1;i++) file[i] = (char*)malloc(sizeof(char) * buff);
    char * files[len1];
    for (int i = 0;i < len1;i++) {
        files[i] = (char*)malloc(sizeof(char) * buff);
        strcpy(files[i],files1[i]);
    }
    for (;i < len1;i++) {
        snprintf(file[i],buff + buff,"%s/%s", path,files[i]);
    }
    i = 0;

// do qsort
    qsort(files,len1,sizeof(char*),myfunc);
    qsort(file,len1,sizeof(char*),myfunc);

    int sum = 0;
    for (int j = 0;j < len1;j++) {
        const char* filename = file[j];
        struct stat fileStat;
        if (stat(filename, &fileStat) == -1) {
            perror("stat");
            printf("At %s\n", filename);
            exit(0);
        }
        if (a == 1) {
            sum += fileStat.st_blocks;
            continue;
        }
        else {
            if (files[j][0] == '.') continue;
            else sum += fileStat.st_blocks;
            if (strcmp(files[j],".") == 0 || strcmp(files[j],"..") == 0) {
                sum -= fileStat.st_blocks;
            }
        }
    }
    if (l == 1) printf("total: %d\n", sum/2);
    for (i = 0;i < len1;i++) {
        if (a == 0) {
            if (files[i][0] == '.') continue;
        }
        printextra(file[i],files[i],l);
    }
    //free file and files
    for (int i = 0;i < len1;i++) {
        free(file[i]);
        free(files[i]);
    }
    return;
    
}