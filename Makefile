CC = gcc
AS = nasm
LD = ld

CFLAGS = -m32 -ffreestanding -fno-stack-protector -fno-pie -nostdlib -nostdinc \
         -fno-builtin -Wall -Wextra -c -I.
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T linker.ld -nostdlib

BUILD_DIR = build
ISO_DIR = isodir

BOOT_SRC = boot/boot.asm
KERNEL_C_SRC = kernel/kernel.c kernel/gdt.c kernel/idt.c kernel/irq.c kernel/memory.c
DRIVER_SRC = drivers/vga.c drivers/keyboard.c drivers/mouse.c drivers/timer.c
GUI_SRC = gui/gui.c gui/window.c gui/button.c gui/desktop.c gui/welcome.c \
          gui/setup.c gui/settings.c gui/fileman.c
FS_SRC = fs/fs.c
LIB_SRC = lib/string.c
ASM_SRC = kernel/isr.asm

C_SRC = $(KERNEL_C_SRC) $(DRIVER_SRC) $(GUI_SRC) $(FS_SRC) $(LIB_SRC)

BOOT_OBJ = $(BUILD_DIR)/boot.o
ASM_OBJ = $(BUILD_DIR)/isr.o
C_OBJ = $(C_SRC:%.c=$(BUILD_DIR)/%.o)

KERNEL = $(BUILD_DIR)/kernel.bin

.PHONY: all clean iso run

all: $(BUILD_DIR) $(KERNEL)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/kernel
	mkdir -p $(BUILD_DIR)/drivers
	mkdir -p $(BUILD_DIR)/gui
	mkdir -p $(BUILD_DIR)/fs
	mkdir -p $(BUILD_DIR)/lib

$(BOOT_OBJ): $(BOOT_SRC)
	$(AS) $(ASFLAGS) $< -o $@

$(ASM_OBJ): $(ASM_SRC)
	$(AS) $(ASFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(KERNEL): $(BOOT_OBJ) $(ASM_OBJ) $(C_OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

iso: $(KERNEL)
	mkdir -p $(ISO_DIR)/boot/grub
	cp $(KERNEL) $(ISO_DIR)/boot/kernel.bin
	cp grub.cfg $(ISO_DIR)/boot/grub/grub.cfg
	grub-mkrescue -o minios.iso $(ISO_DIR)

run: iso
	qemu-system-i386 -cdrom minios.iso -m 128M

clean:
	rm -rf $(BUILD_DIR) $(ISO_DIR) minios.iso
