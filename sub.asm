[BITS 32]

[GLOBAL _doit]

[SECTION .text]

_doit:
  push ebx
  push eax

  mov bx, 0xbeef

  mov eax, chunk
  add eax, 63
  and eax, 0xffffffc0 ; align to 64 bytes

  xchg [eax], bx      ; should be okay
  dec eax
  xchg [eax], bx      ; might lock

  pop eax
  pop ebx
  ret


[SECTION .data]
  times 0x10 db 0
chunk:
  times 256 db 0
