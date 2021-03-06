/**************************************
 * CptS 360 Final Project
 * 
 * Main File
 * 
 * Programmers:
 * Amariah Del Mar 11504395
 * Elizabeth Viele
 * 
 * Last Modified: 12/4/18
*/


#include "type.h"
#include "util.c"
#include "ialloc.c"
#include "my_pwd.c"
#include "my_mkdir.c"
#include "my_rmdir.c"
#include "my_creat.c"
#include "my_chmod.c"
#include "my_link.c"
#include "my_syslink.c"
#include "my_unlink.c"
#include "mount_root.c"
#include "my_ls.c"
#include "my_cd.c"

char *commands[] = {"ls", "pwd", "cd", "mkdir", "rmdir", "creat", "link", "symlink", "unlink", "chmod", "menu", "quit"};

char line[128];

int quit(char *pathname) {
    printf("\n\tQUITTING\n");
    return -1;
}
int menu()
{
    printf("*********************************\n");
    printf("************** MENU *************\n");
    printf("** ls pwd cd mkdir rmdir creat **\n");
    printf("*** link syslink unlink chmod ***\n");
    printf("*********************************\n");

    return 0;
}

int(*fptr[])(char*) = {(int(*)())my_ls, my_pwd, my_cd, my_mkdir, my_rmdir, my_creat, my_link, my_syslink, my_unlink, my_chmod, menu, quit};

int findCmd(command) {
    // cycle through commands stored in the commands[] array and return it's index
    for (int i = 0; i < 12; i++) {
        if (strcmp(command, commands[i]) == 0) {
            return i;
        }
    }
    return -1; // return -1 to run the default option
}

char *disk;
int main(int argc, char *argv[])
{
    int index, quitting = 0;

    if (argc < 2) {
        disk = "mydisk";
    } 
    else {
        disk = argv[1];
    }
    init();
    mount_root(disk);

    while(!quitting) {
        memset(pathname, 0, 256);
        printf("input a command:\t");
        fgets(line, 128, stdin);
        line[strlen(line)-1] = NULL; // get rid of NULL at the end
        sscanf(line, "%s %s", command, pathname);
        index = findCmd(command);
        if (index != -1) {
            quitting = fptr[index](pathname);
        } else {
            printf("invalid command %s\n", command);
        }
    }
    
    return 0;
}