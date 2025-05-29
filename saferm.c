#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


#define file_exists(filepath) !access(filepath, F_OK)


/**
 * usage: saferm [--proper [RM-FLAGS]..., -p [RM-FLAGS]...] [FILES]...
 */




void help() {
    printf("Not enough args\n"
       "usage: saferm [--proper [RM-FLAGS]..., -p [RM-FLAGS]...] [FILES]...\n");
}

void move_trash(const char *basename, const char *filename,
        const char *trash) {

    size_t trashlen = strlen(basename) + strlen(trash) + 1; // Store trash length
    char *trashpath = (char *)malloc(trashlen + 1); // allocate trash pathbuffer
    if (!trashpath) {
        fprintf(stderr, "saferm: Allocation failed\n");
        return;
    }
    snprintf(trashpath, strlen(basename) + strlen(trash) + 2,"%s/%s",
            trash, basename); // copy chars into pathbuffer

    while(file_exists(trashpath)) {
        trashpath = realloc(trashpath, trashlen + strlen(".bac") + 1); // Reallocate and make bigger by 4
        if (!trashpath) {
            fprintf(stderr, "saferm: Reallocation failed\n");
            return;
        }
        strncat(trashpath, ".bac", 5); // Append .bac to trash path
        trashlen += strlen(".bac"); // update trash length
    }
    rename(filename, trashpath); // Finally Move the file
    free(trashpath);
}

void move(const int argc, const char **argv) {
    // Build path to trash dir
    char trash[strlen(getenv("HOME")) + strlen("/.trash") + 1];
    snprintf(trash, strlen(getenv("HOME")) + strlen("/.trash") + 1, 
            "%s/.trash", getenv("HOME"));

    // Check if dir exists
    if (!file_exists(trash)) {
        mkdir(trash, 0755);
    }

    for (int i = 1; i < argc; ++i) {
        char argument[strlen(argv[i]) + 1]; // allocate memory for copy of argv
        snprintf(argument, strlen(argv[i]) + 1, "%s", argv[i]); // copy chars into buffer
        if (argument[strlen(argument) - 1] == '/') { // check if argument ends with /
            argument[strlen(argument) - 1] = '\0'; // set that byte to NUL
        }

        char *basename = strrchr(argument, '/'); // find last '/'
        if (basename) {
            basename++; // increment basename to next char
            move_trash(basename, argv[i], trash);
        } else {
            move_trash(argv[i], argv[i], trash);
        }
    }
}

void process_args(int argc, char **argv) {
    // Check if there are enough arguments
    if (argc < 2) {
        help();
        return;
    }
    // Check if user wants to run proper rm
    if (strcmp(argv[1], "--proper") == 0 || strcmp(argv[1], "-p") == 0) {
        char *rm = "rm";
        argv[1] = rm;
        execv("/usr/bin/rm", &argv[1]); // I think this will turn this proc into rm
    }

    move(argc, (const char**)argv);
}





int main(int argc, char **argv) {
    process_args(argc, argv);
}
