mov ah, 0x0e
mov al, 65
int 0x10

lower:
    add al, 33
    int 0x10
    jmp upper

upper:
    sub al, 31
    cmp al, 91
    je exit
    int 0x10
    jmp lower

exit:
    jmp $

times 510-($-$$) db 0
db 0x55, 0xaa