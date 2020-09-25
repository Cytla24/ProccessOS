#include  <stdio.h>
#include <stdlib.h>
#include  <string.h>
#include  <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define   MAX_COUNT  3

void  ChildProcess(void);                /* child process prototype  */
void  ParentProcess(void);               /* parent process prototype */

void  main(void)
{
  srand((unsigned int)time(NULL));
  pid_t  pid_a, pid_b;
  pid_a = fork();
  if (pid_a == 0){
    ChildProcess();
  } else if (pid_a == -1){
    printf("Error");
  }
  else{
    pid_b = fork();
    if (pid_b == 0){
      ChildProcess();
    } else if (pid_a == -1){
      printf("Error");
    }else {
      ParentProcess();
    }
  } 
}

void  ChildProcess(void)
{
  int   i;
  int iter = random() % 31;
  for (i = 1; i <= iter; i++){
    printf("Child Pid: %d is going to sleep!\n", getpid());
    int r = random() % 11;
    sleep(r);
    printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
//     printf("   This line is from child, value = %d\n", i);
  }
  exit(0);
}

void  ParentProcess(void)
{
  int status;
  pid_t c_status;
  c_status = wait(&status); 
  printf("Child Pid: %d has completed\n", c_status);
}
