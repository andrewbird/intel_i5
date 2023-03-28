#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#ifdef __linux__
#  define doit _doit
#endif

static inline unsigned short get_cs(void)
{
  unsigned short cs;
  asm("movw %%cs, %0" : "=rm" (cs));
  return cs;
}

static inline unsigned short get_ds(void)
{
  unsigned short ds;
  asm("movw %%ds, %0" : "=rm" (ds));
  return ds;
}

static inline unsigned lsl(unsigned short sel)
{
  unsigned sl;
  asm("lsll %1, %0" : "=r" (sl) : "rm" ((unsigned)sel));
  return sl;
}

static inline unsigned lar(unsigned short sel)
{
  unsigned ar;
  asm("larl %1, %0" : "=r" (ar) : "rm" ((unsigned)sel));
  return ar;
}

static inline unsigned eflags(void)
{
  unsigned ef;
  asm("pushfl; popl %0" : "=rm" (ef));
  return ef;
}

extern void doit(void);

#ifdef __linux__
static void doalarm(int sig)
{
}

static void setalarm(void)
{
  struct sigaction sa;
  struct itimerval itv;

  memset(&sa, 0, sizeof(sa));

  sa.sa_handler = doalarm;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sigaction(SIGALRM, &sa, NULL);

  itv.it_interval.tv_sec = itv.it_value.tv_sec = 0;
  itv.it_interval.tv_usec = itv.it_value.tv_usec = 5000;  /* less than 10ms */
  setitimer(ITIMER_REAL, &itv, NULL);
}
#endif

int main()
{
  unsigned short cs = get_cs(), ds = get_ds();
  printf("cs = %#hx  lsl(cs) = %#x  lar(cs) = %#x\n", cs, lsl(cs), lar(cs));
  printf("ds = %#hx  lsl(ds) = %#x  lar(ds) = %#x\n", ds, lsl(ds), lar(ds));
  printf("eflags = %#x\n", eflags());

#ifdef __linux__
  setalarm();
#endif

  usleep(500000);

  doit();

  return 0;
}
