#include <stdint.h>


// Inline assembly functions
// outb uses out cmd to interface w/ output devices
void outb(uint16_t port, uint8_t data){
    __asm__ volatile ("outb %1, %0" : : "dN" (port), "a" (data));
}


// Screen printing
// Instantiate some vars
uint8_t cursor_x = 0;
uint8_t cursor_y = 0;
uint16_t* const video_memory = (uint16_t* const)0xb8000;
const uint16_t default_color = (0 << 8) | (7 << 12);

// Functions
// Updates cursor location on screen
static void move_cursor(){
    uint16_t cursor_loc = cursor_y * 80 + cursor_x;
    outb(0x3D4, 14);
    outb(0x3D5, cursor_loc >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, cursor_loc);
}

// Scroll the screen down (if applicable)
static void scroll(){
    if (cursor_y >= 25){
        for (int i = 0*80; i < 24*80; i++){
            video_memory[i] = video_memory[i+80];
        }

        for (int i = 24*80; i < 25*80; i++)
       {
           video_memory[i] = ' ' | default_color;
       }
       cursor_y = 24;
    }
}

// Instantiate/reset screen space w/ default colors and cursor location
void clear_screen(){
    cursor_x = 0;
    cursor_y = 0;
    move_cursor();

    for (uint16_t y = 0; y < 25; y++)
    {
        for (uint16_t x = 0; x < 80; x++){
            video_memory[y * 80 + x] = ' ' | default_color;
        }
    }    
}

// Print a string to the screen
void puts(const char* s) {
    while (*s)
    {
        // Backspace
        if (*s == 0x08 && cursor_x)
        {
            cursor_x--;
        }
        // Handle a tab by increasing the cursor's X, but only to a point
        // where it is divisible by 8.
        else if (*s == 0x09)
        {
            cursor_x = (cursor_x+8) & ~(8-1);
        }
        // Handle carriage return
        else if (*s == '\r')
        {
            cursor_x = 0;
        }
        // Handle newline by moving cursor back to left and increasing the row
        else if (*s == '\n')
        {
            cursor_x = 0;
            cursor_y++;
        }
        // Handle any other printable character.
        else if(*s >= ' ')
        {
            video_memory[cursor_y * 80 + (cursor_x++)] = *s | default_color;
        }
        // Check if we need to insert a new line because we have reached the end
        // of the screen.
        if (cursor_x >= 80)
        {
            cursor_x = 0;
            cursor_y ++;
        }

        // Scroll the screen if needed.
        scroll();
        // Move the hardware cursor.
        move_cursor();
        // GO to next character
        s++;
    }
}


// Start main
extern void main() {
    clear_screen();
    for (int i = 0; i < 26; i++){
        puts("Hello\t world!\n");
    }
    puts("Scroll screen\n");
    puts("abcdefghijklmnopqrstuvwzyx1234567890!@#$%^&*()-_=+;:?><,./\n");


    /*
    clear_screen();
    int a = 255;
    char* int_buffer[20];
    int_to_str(a, int_buffer);
    puts(int_buffer);
    */

    return;
}