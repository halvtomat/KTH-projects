bits 16

start:
    mov     ax, 0x07C0
    add     ax, 0x20
    mov     ss, ax
    mov     sp, 0x1000

    mov     ax, 0x07C0
    mov     ds, ax
    
    mov     si, msg
    mov     ah, 0x0E

.next:
    lodsb
    cmp     al, 0
    je      .done
    int     0x10
    jmp     .next

.done:
    jmp     $

msg:    db 'Hello', 0

times 510-($-$$) db 0
dw      0xAA55