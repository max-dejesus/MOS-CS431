// IDT
// IDT entry struct definition
typedef struct {
    uint16_t isr_lo;        // ISR lower 16 bits
    uint16_t kernel_cs;     // code selector
    uint8_t reserved;       // always 0
    uint8_t flags;          // Type flags
    uint16_t isr_hi;        // ISR higher 16 hits
}__attribute__((packed)) idt_entry_t;

// IDT pointer definition
typedef struct {
	uint16_t	limit;
	uint32_t	base;
} __attribute__((packed)) idtr_t;

// Create IDT array and pointer
__attribute__((aligned(0x10))) 
static idt_entry_t idt[256];
static idtr_t idtr;

__attribute__((noreturn))
void excp_handler(void);
void excp_handler(){
    __asm__ volatile("cli; hlt"); // Halts computer entirely
}


/*
    clear_screen();
    int a = 255;
    char* int_buffer[20];
    int_to_str(a, int_buffer);
    puts(int_buffer);
    */

/*
ASM code

    %macro isr_err_stub 1
    isr_stub_%+%1:
        call excp_handler
        iret
    %endmacro

    %macro isr_no_err_stub 1
    isr_stub_%+%1:
        call excp_handler
        iret
    %endmacro

    extern excp_handler
    isr_no_err_stub 0
    isr_no_err_stub 1
    isr_no_err_stub 2
    isr_no_err_stub 3
    isr_no_err_stub 4
    isr_no_err_stub 5
    isr_no_err_stub 6
    isr_no_err_stub 7
    isr_err_stub    8
    isr_no_err_stub 9
    isr_err_stub    10
    isr_err_stub    11
    isr_err_stub    12
    isr_err_stub    13
    isr_err_stub    14
    isr_no_err_stub 15
    isr_no_err_stub 16
    isr_err_stub    17
    isr_no_err_stub 18
    isr_no_err_stub 19
    isr_no_err_stub 20
    isr_no_err_stub 21
    isr_no_err_stub 22
    isr_no_err_stub 23
    isr_no_err_stub 24
    isr_no_err_stub 25
    isr_no_err_stub 26
    isr_no_err_stub 27
    isr_no_err_stub 28
    isr_no_err_stub 29
    isr_err_stub    30
    isr_no_err_stub 31

    /*
    global isr_stub_table
    isr_stub_table:
    %assign i 0 
    %rep    32 
        dd isr_stub_%+i ; use DQ instead if targeting 64-bit
    %assign i i+1 
    %endrep
    

*/

/*
void int_to_str(int val, char* buffer){
    int len = sizeof(buffer) / sizeof(buffer[0]);
    
    int count = 1;
    int tmp = val;

    while (tmp != 0) { 
        tmp /= 10;
        count++;
    }

    int tmp_int[20];

    for (int i = count - 1; i >= 0; i--) {
        tmp_int[i] = val % 10;  // Get the last digit
        val /= 10;             // Remove the last digit
    }

    for (int i = 0; i == count; i++){
        int curr_int = tmp_int[i];
        switch(curr_int){
            case 0:
                buffer[i] = '0';
                break;
            case 1:
                buffer[i] = '1';
                break;
            case 2:
                buffer[i] = '2';
                break;
            case 3:
                buffer[i] = '3';
                break;
            case 4:
                buffer[i] = '4';
                break;
            case 5:
                buffer[i] = '5';
                break;
            case 6:
                buffer[i] = '6';
                break;
            case 7:
                buffer[i] = '7';
                break;
            case 8:
                buffer[i] = '8';
                break;
            case 9:
                buffer[i] = '9';
                break;
        }
    }

}
*/