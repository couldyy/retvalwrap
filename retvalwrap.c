#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <spawn.h>
#include <sys/wait.h>

extern char** environ;

char** slice_arguments(int count, char** raw_args);

int main(int argc, char** argv)
{
    if(argc <= 1) {
        fprintf(stderr, "Invalid argumnets, see -h or --help for help\n");
        return -1;
    }
    else if(argc == 2 && !strcmp(argv[1], "--help")) {
        printf("Hello, this is just a simple wrapper to obtain a return code of a program\n"
                "due to functions that is used to obtain that value, \nit will return only 8 least significant bits of returned value (range 0..255)\n"
                "\nto make this program work specify the following: \nretvalwrap your_program_name *arguments to a program*\n"
                "\nexample: retvalwrap echo \"Hello, world\"\n"
                "Hello, world\n\nProgram exited with status 0\n");
        return 0;
    }
    

    //make slice of argv[], thus getting arguments to call a program if there are arguments
    char** callable_progam_args = slice_arguments(argc, argv); 


    // call desired program
    pid_t child_pid;
    int spawn_status = posix_spawnp(&child_pid, argv[1], NULL, NULL, callable_progam_args, environ);
    if(spawn_status != 0) {
        printf("posix_spawn: %s\n", strerror(spawn_status));
        exit(1);
    }
    else {
        //obtain returned value
        int status;
        waitpid(child_pid, &status, 0);
        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            printf("\nProgram exited with status %d\n", exit_code);
        } else if (WIFSIGNALED(status)) {
            int sig = WTERMSIG(status);
            printf("\nProgram was terminated by signal %d(%d)\n", sig, 128+sig);
        } else {
            printf("\nProgram exited abnormally.\n");
        }
    }
    free(callable_progam_args);
    return 0;
}

char** slice_arguments(int count, char** raw_args)
{
    char** args = (char**)malloc(sizeof(char*) * (count + 1)); // +1 for NULL at the end of array
    for(int i = 0; i < count; i++) {
        args[i] = raw_args[i+1];
    }
    args[count] = NULL;
    return args;

}
