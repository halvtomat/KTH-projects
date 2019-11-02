bits 32
global start
 
section .text
 
start:
    mov dword   [0xB8000], 0x2F4B2F4F
    hlt