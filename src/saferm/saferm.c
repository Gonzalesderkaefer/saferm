// Libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../utils/path.h"
#include "../utils/lin_alloc.h"

// For the linear allocator
lin_init();
// Allocator function
void *this_alloc(size_t size) {
    return lalloc(cur_mem, size);
}
// Free function
void this_free(void *ptr) {}


// Other utils TODO: Put this in header file.
#define file_exists(filepath) !access(filepath, F_OK)


/**
 * usage: saferm [--proper [RM-FLAGS]..., -p [RM-FLAGS]...] [FILES]...
 */




static void print_help() {
    printf("Not enough args\n"
       "usage: saferm [--proper [RM-FLAGS]..., -p [RM-FLAGS]...] [FILES]...\n");
}

static void move_trash(const char *basename, const char *filename, const char *trash) {
    // Local allocator
    lin_switch(trash_move_mem);

    // Sanity checks
    if (basename == NULL || filename == NULL || trash == NULL) {
        return;
    }

    // find new name
    Path *new_path = path_init_alloc(trash, this_alloc, this_free);
    if (new_path == NULL) {
        lin_free(trash_move_mem);
        return;
    }
    path_append(new_path, basename);

    while (file_exists(path_str(new_path))){
        path_append_to_base(new_path, ".bac");
    }

    // move to new_path
    rename(filename, path_str(new_path));


    lin_free(trash_move_mem);
}

static void move(const int argc, const char **argv) {
    // Local allocator
    lin_switch(move_mem)

    // Build path to trash dir
    Path *trash_path = path_init_alloc(getenv("HOME"), this_alloc, this_free);
    path_append(trash_path, ".trash");
    const char *trash = path_str(trash_path);

    // Check if dir exists
    if (!file_exists(trash)) {
        mkdir(trash, 0755);
    }

    for (int i = 1; i < argc; ++i) {
        Path *arg_path = path_init_alloc(argv[i], this_alloc, this_free);
        if (arg_path == NULL) {
            continue;
        }
        const char *arg_base = path_base(arg_path);
        if (arg_base != NULL) {
            move_trash(arg_base, argv[i], trash);
        }
    }

    lin_free(move_mem)
}

void process_args(int argc, char **argv) {
    // Check if there are enough arguments
    if (argc < 2) {
        print_help();
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
