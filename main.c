#include <stdio.h>

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

int main()
{
  unsigned short cs = get_cs(), ds = get_ds();
  printf("cs = %#hx  lsl(cs) = %#x  lar(cs) = %#x\n", cs, lsl(cs), lar(cs));
  printf("ds = %#hx  lsl(ds) = %#x  lar(ds) = %#x\n", ds, lsl(ds), lar(ds));
  printf("eflags = %#x\n", eflags());

  doit();

  return 0;
}
