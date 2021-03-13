#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
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
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// ckd

// set ticket 시스템콜. 
int
sys_setix(void)
{
  int num_tix;
  if(argint(0,&num_tix)<0) // argint OK?
    return -1;
  myproc()->tix = num_tix; // set ticket as input
  return 0;

}
// process info를 얻는 시스템콜. input 값에 따라 다른 정보를 return한다.
// 1 : ticket
// 2 : 걸린시간.(ticks)
// 3 : winner_ticket
// 4 : 총 티켓 수
// 5 : count
// 6 : 현재 state (0: UNUSED, 1: EMBRYO, 2:SLEEPING, 3:RUNNABLE, 4:RUNNING, 5:ZOMBIE)
int
sys_gpinfo(void)
{
  int operation;
  if(argint(0,&operation)<0) // argint OK?
    return -1;
    /* // name 은 문자열이기 때문에 getname 시스템콜을 이용.
  if(operation == 0){
    return myproc()->name;
  }*/
  if(operation == 1){
    return myproc()->tix;
  }
  else if(operation == 2){
    return myproc()->ticks;
  }
  else if(operation == 3){
    return myproc()->winner_tix;
  }
  else if(operation == 4){
    return totaltix();
  }
  else if(operation == 5){
    return myproc()->count;
  }
  else if(operation == 6){
    return myproc()->state;
  }
  return 0;
}
// process명을 return 하는 시스템콜.
char*
sys_getname(void)
{
  return myproc()->name;
}