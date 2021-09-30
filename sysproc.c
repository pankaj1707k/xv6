#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "uproc.h"

int sys_fork(void)
{
  return fork();
}

int sys_exit(void)
{
  exit();
  return 0; // not reached
}

int sys_wait(void)
{
  return wait();
}

int sys_kill(void)
{
  int pid;

  if (argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int sys_getpid(void)
{
  return myproc()->pid;
}

int sys_sbrk(void)
{
  int addr;
  int n;

  if (argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if (growproc(n) < 0)
    return -1;
  return addr;
}

int sys_sleep(void)
{
  int n;
  uint ticks0;

  if (argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n)
  {
    if (myproc()->killed)
    {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int sys_getyear(void)
{
  return 2021;
}

extern int getppid(void);

int sys_getppid(void){
  return getppid();
}

//Processes || Copy elements from the kernel ptable to the user space
extern struct proc * getptable_proc(void);

int sys_getptable(void){
  int size;
  char *buf;
  char *s;
  struct proc *p = '\0';
  
  if (argint(0, &size) <0){
    return -1;
  }
  if (argptr(1, &buf,size) <0){
    return -1;
  }
  
  s = buf;
  p = getptable_proc();
  
  while(buf + size > s && p->state != UNUSED){
    *(int *)s = p->state;
    s+=4;
    *(int *)s = p -> pid;
    s+=4;
    *(int *)s = p->parent->pid;
    s+=4;
    memmove(s,p->name,16);
    s+=16;
    p++;
  } 
  return 0;
}



// extern int getprocinfo(int pid, struct uproc *up);

// int sys_getprocinfo(void)
// {
//   // int pid;
//   // char* up;

//   // if (argint(0, &pid) < 0 || argptr(1, &up, sizeof(struct uproc)) < 0)
//   //   return -1;
  
//   return getprocinfo(pid, (struct uproc*)up);
// }

// extern int getnextpid(void);
// int sys_getnextpid(void)
// {
//   return getnextpid();
// }
