#include "types.h"
#include "stat.h"
#include "user.h"

//From proc.h Proc structure
// Per-process state
enum procstate { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };
struct proc {
  enum procstate state;        // Process state
  int pid;            // Process ID
  int ppid;          // Parent process ID
  char name[16];               // Process name 
};

#define MAX_PROC 10

int
main(int argc, char *argv[]){  
  struct proc ptable[MAX_PROC];
  struct proc *p;
  int err;
  
  err = getptable(10*sizeof(struct proc),&ptable);
  if(err !=0)
    printf(1,"Error getting ptable");
  
  p = &ptable[0];
  printf(1, " PID  PPID  STATE  CMD \n");
  while(p != &ptable[MAX_PROC-1] && p->state != UNUSED){
	if (p->pid == 1)
		p->ppid = 0;
  	printf(1,"  %d  %d ",p->pid,p->ppid);
  	switch(p->state){
  	case UNUSED:
  		printf(1," %s ", "UNUSED");
  		break;
  	case EMBRYO:
  		printf(1," %s ", "EMBRYO");
  		break;
  	case SLEEPING:
  		printf(1," %s ", "SLEEPING");
  		break;
  	case RUNNABLE:
  		printf(1," %s ", "RUNNABLE");
  		break;
  	case RUNNING:
  		printf(1," %s ", "RUNNING");
  		break;
  	case ZOMBIE:
  		printf(1," %s ", "ZOMBIE");
  		break;
  	} 
  	printf(1," %s \n", p->name);
  	p++;
  }
  	  
  exit();
}







// #include "types.h"
// #include "stat.h"
// #include "user.h"
// #include "syscall.h"
// #include "uproc.h"

// void ps(void)
// {
//     struct uproc *up;   // user process
//     up = malloc(sizeof(struct uproc));

//     int nextpid = getnextpid();
//     int i;

//     printf(1, " PID  PPID  STATE  SIZE  NAME \n");

//     for (i=1; i < nextpid; i++) {
//         if (getprocinfo(i,up) == 0) {
//             printf(1, " %d  %d  %s  %d  %s \n", up->pid, up->ppid, up->state, up->sz, up->name);
//         }
//     }
//     free(up);
// }

// int main()
// {
//     ps();
//     exit();
// }