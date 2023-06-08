#include<stdio.h>
#include<unistd.h>
int main(){
    pid_t pid = fork();

    if(pid<0){
        printf("Failed to fork!!!");
    }
    else if(pid >0){
   
         printf("Parent Process:\n");
        printf("Parent PID: %d\n",getpid());
        printf("Child PID: %d\n",pid);
    }
    else{
        printf("Child Process:\n");
        printf("Child PID: %d\n",getpid());
        printf("Parent PID: %d\n",getppid());
    }
    return 0;
}
