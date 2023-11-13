[org 0x07c00]

mov [BOOT_DISK], dl

; pointers to our segments and kernel
KERNEL_LOC equ 0x1000
CODE_SEG equ GDT_code - GDT_start
DATA_SEG equ GDT_data - GDT_start

; load from disk
xor ax, ax                          
mov es, ax
mov ds, ax
mov bp, 0x8000
mov sp, bp

mov bx, KERNEL_LOC
mov dh, 2

mov ah, 0x02
mov al, dh 
mov ch, 0x00
mov dh, 0x00
mov cl, 0x02
mov dl, [BOOT_DISK]
int 0x13

; converts to text mode, clear screen                                  
mov ah, 0x0
mov al, 0x3
int 0x10


; disable interrupts
cli
lgdt [GDT_descriptor]
mov eax, cr0
or eax, 1
mov cr0, eax
jmp CODE_SEG:start_pm

jmp $

BOOT_DISK: db 0

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
    ; set up segments and stack
    mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	mov ebp, 0x90000
	mov esp, ebp

    jmp KERNEL_LOC


; init boot sector
times 510-($-$$) db 0
db 0x55, 0xaa