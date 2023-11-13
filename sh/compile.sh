echo "Compiling files..."
i386-elf-gcc -ffreestanding -m32 -g -c "./src/kernel.c" -o "./obj/kernel.o"
nasm "./asm/kernel_entry.asm" -f elf -o "./obj/kernel_entry.o"
i386-elf-ld -o "./bin/full_kernel.bin" -Ttext 0x1000 "./obj/kernel_entry.o" "./obj/kernel.o" --oformat binary
