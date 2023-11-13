#ifndef IDT_H
#define IDT_H

// Set an IDT entry at index num w/
void idt_set(unsigned char num, unsigned long handler);

// Prepare IDT and load
void idt_install();

#endif