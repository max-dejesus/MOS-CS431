; uassign str var and print string
[org 0x7c00]
mov ah, 0x0e
mov bx, myStr

printStr:
    mov al, [bx]
    cmp al, 0
    je exit
    int 0x10
    inc bx
    jmp printStr

myStr:
    db "Hello world", 0

exit:
    jmp $

; init boot sector
times 510-($-$$) db 0
db 0x55, 0xaa