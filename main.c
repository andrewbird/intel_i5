#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#ifdef __linux__
#  define doit _doit
#endif

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
  printf("Starting timer\n");

#ifdef __linux__
  setalarm();
#endif

  usleep(500000);

  printf("Before xchg\n");

  doit();

  printf("After xchg\n"); // never gets here

  printf("PASS\n");
  return 0;
}
