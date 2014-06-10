#include <unistd.h>  
#include <stdio.h>   
#include <stdlib.h>

#include <dlfcn.h> //for dlopen

const char* filename = "tprint.so";
const char* funcname = "print";

int main(int argc, char *argv[])   
{   
        int count = 0;  
        pid_t fpid = fork();   
        if(fpid < 0){
                printf("error in fork!");
        }
        else if(fpid == 0){  
                printf("i am the child process, my process id is %d\n", getpid());   
                void* handle = dlopen(filename, RTLD_NOW);
                if(handle == NULL){
                        printf("dlopen error\n");
                        exit(1);
                }

        //(double (*)(double)) dlsym(handle, "cos");
        //*(void **) (&cosine) = dlsym(handle, "cos");

                void (*func)(void) = (void (*)(void))dlsym(handle, funcname);
                char* error = dlerror();
                if(error != NULL){
                        printf("dlsym error: %s\n", error);
                        exit(1);
                }

        //(*cosine)(2.0)
                (*func)();

                dlclose(handle);

                count++;  
                printf("i am the child process, my process id is %d\n", getpid());   
        }  
        else{  
                printf("i am the parent process, my process id is %d\n", getpid());   
                count++;  
        }  
        printf("count %d pid %d\n",count, getpid());  
        return 0;  
}
