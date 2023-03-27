#ifdef __linux__
#  define doit _doit
#endif

extern void doit(void);

int main()
{
  doit();

  return 0;
}
