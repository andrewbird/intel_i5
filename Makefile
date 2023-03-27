DPROG = i5test.exe
LPROG = i5test-l32

all: $(DPROG) $(LPROG)

$(DPROG) : sub.obj main.c
	i586-pc-msdosdjgpp-gcc main.c -o $@ -Wall $< -o $@

%.obj : %.asm
	nasm -f coff $< -o $@

$(LPROG) : sub.o main.o
	gcc -g -m32 -no-pie -o $@ $^ -Wl,-melf_i386

%.o : %.c
	gcc -g -m32 -no-pie -c $< -o $@

%.o : %.asm
	nasm -g -f elf32 $< -o $@

clean:
	$(RM) *.obj
	$(RM) $(DPROG)
	$(RM) *.o
	$(RM) $(LPROG)
