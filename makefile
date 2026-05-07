target = -target i686-pc-non-elf
asm = nasm
compiler = clang
src_dir = src
standard_library = $(src_dir)/stdlib

debugflag = -g

#assembly flags
aflags = -f elf32

#Kernel flags
cflags = -m32 -ffreestanding -fno-builtin -fno-stack-protector -nostdlib

#Hardware/Interrupt Protection 
cflags += -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -mno-80387

#other stuff
cflags += -Wall -Wextra -fno-omit-frame-pointer

all: clean kernel boot image

clean:
	rm -rf build/*.o

kernel:
	$(compiler) $(target) $(cflags) -c $(src_dir)/kernel.c -o kernel.o 
	$(compiler) $(target) $(cflags) -c $(standard_library)/stdio.c -o stdio.o 
	$(asm) $(aflags) $(src_dir)/gdt.asm -o gdt.o
boot:
	$(asm) $(aflags) $(src_dir)/boot.asm -o boot.o

image:
	ld -m elf_i386 -T src/linker.lld -o kernel boot.o kernel.o stdio.o gdt.o 
	mv kernel XiaoLingOS/boot/kernel
	grub-mkrescue -o XiaoLingOS.iso XiaoLingOS
	rm *.o
