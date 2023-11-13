echo "Booting up MOS"
nasm -f bin ./asm/boot.asm -o ./bin/boot.bin
bash ./sh/compile.sh
cat "./bin/boot.bin" "./bin/full_kernel.bin" > "MOS.bin"
qemu-system-x86_64 MOS.bin
