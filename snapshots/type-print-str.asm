[org 0x7c00] ; need to change origin of where memory is read
; this is because the BIOS loads in a vector table of all the interrupt codes,
; thus taking up the first portions of memor

; buffer is our var, and when mov is called with it as dst, it is a pointer to
; the beginning of the portion of memory
buffer:
    times 100 db 0

type:
    ; assign bx register to our var, bx is a pointer
    mov bx, buffer
    il:
        ; this interrupt takes user input from the keybord
        mov ah, 0
        int 0x16
        ; return to TTY mode to show keypresses
        mov ah, 0x0e
        int 0x10

        ; end input checking if char is hyphen
        cmp al, '-'
        je slashn

        ; move the al register of char inputted to dereferenced bx register (which is pointing to our var)
        mov [bx], al
        inc bx ; increment the pointer
        jmp il

slashn:
    mov ah, 0x0e ; TTY mode
    mov al, 13 ; carriage return 
    int 0x10
    mov al, 10 ; new line
    int 0x10

printStr:
    mov bx, buffer ; move register to beginning of our var
    mov ah, 0x0e
    pl:
        mov al, [bx] ; mov dereferenced bx to al register
        cmp al, 0
        je exit ; exits if null code
        int 0x10 ; prints
        inc bx ; increment pointer
        jmp pl

exit:
    jmp $

; init boot sector
times 510-($-$$) db 0
db 0x55, 0xaa