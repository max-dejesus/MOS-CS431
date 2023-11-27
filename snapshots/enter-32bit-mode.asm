[org 0x07c00]

mov [BOOT_DISK], dl

; pointers to our segments
CODE_SEG equ GDT_code - GDT_start
DATA_SEG equ GDT_data - GDT_start


; disable interrupts
cli
lgdt [GDT_descriptor]
mov eax, cr0
or eax, 1
mov cr0, eax
jmp CODE_SEG:start_pm

jmp $

; define GDT
GDT_start:
    GDT_null:
        dd 0x0
        dd 0x0
    
    GDT_code:
        ; define first 16 bits of limit
        dw 0xffff
        ; define first 24 bits of base
        dw 0x0 
        db 0x0
        ; first four: present, priviledge, and type, last four: type flags 
        db 0b10011010
        ; first four: other flags, last four: limit
        db 0b11001111
        ; last 8 bits of base
        db 0x0
    
    GDT_data:
        dw 0xffff
        dw 0x0
        db 0x0
        db 0b10010010
        db 0b11001111
        db 0x0

GDT_end:

GDT_descriptor:
    dw GDT_end - GDT_start - 1
    dd GDT_start


[bits 32]
start_pm:
    ; write char to screen (meaning we are in 32 bit mode)
    mov al, 'A'
    mov ah, 0x0f
    mov [0xb8000], ax
    jmp $

BOOT_DISK: db 0

; init boot sector
times 510-($-$$) db 0
db 0x55, 0xaa