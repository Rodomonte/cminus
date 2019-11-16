nasm -f elf32 krnl.a -o kasm.o
gcc -m32 -c krnl.c -o kc.o
ld -m elf_i386 -T link.ld -o kernel-100 kasm.o kc.o
