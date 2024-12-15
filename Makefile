# Compilador y ensamblador
AS = nasm
CC = gcc
LD = ld

# Flags para las herramientas
NASM_FLAGS = -f bin
GCC_FLAGS = -ffreestanding -O2 -Wall -Wextra -g -fno-pie
LD_FLAGS = -T $(LINKER_SCRIPT) -nostdlib

# Directorios
BUILD_DIR = build
BOOT_DIR = boot
KERNEL_DIR = kernel
ISO_DIR = iso

# Archivos
BOOTLOADER = $(BOOT_DIR)/bootloader.asm
KERNEL_SRC = $(KERNEL_DIR)/kernel.c \
             $(KERNEL_DIR)/scheduler.c \
             $(KERNEL_DIR)/debug.c \
             $(KERNEL_DIR)/keyboard.c \
             $(KERNEL_DIR)/interrupts.c \
             $(KERNEL_DIR)/console.c \
             $(KERNEL_DIR)/serial.c \
             $(KERNEL_DIR)/io.c
MULTIBOOT_HEADER = $(KERNEL_DIR)/multiboot_header.S
KERNEL_BIN = $(BUILD_DIR)/kernel.bin
ISO_IMAGE = $(BUILD_DIR)/myos.iso
LINKER_SCRIPT = linker.ld
GRUB_CFG = $(ISO_DIR)/boot/grub/grub.cfg

# Ruta a libgcc
LIBGCC = /usr/lib/gcc/x86_64-linux-gnu/13/libgcc.a

# Generar todo
.PHONY: all
all: $(ISO_IMAGE)

# Compilar el bootloader
$(BUILD_DIR)/bootloader.bin: $(BOOTLOADER)
	mkdir -p $(BUILD_DIR)
	$(AS) $(NASM_FLAGS) $< -o $@

# Compilar el kernel
$(KERNEL_BIN): $(KERNEL_SRC) $(MULTIBOOT_HEADER) $(LINKER_SCRIPT)
	# Compilar el encabezado Multiboot
	$(CC) $(GCC_FLAGS) -c $(MULTIBOOT_HEADER) -o $(BUILD_DIR)/multiboot_header.o

	# Compilar cada componente del kernel
	$(CC) $(GCC_FLAGS) -c $(KERNEL_DIR)/kernel.c -o $(BUILD_DIR)/kernel.o
	$(CC) $(GCC_FLAGS) -c $(KERNEL_DIR)/scheduler.c -o $(BUILD_DIR)/scheduler.o
	$(CC) $(GCC_FLAGS) -c $(KERNEL_DIR)/debug.c -o $(BUILD_DIR)/debug.o
	$(CC) $(GCC_FLAGS) -c $(KERNEL_DIR)/keyboard.c -o $(BUILD_DIR)/keyboard.o
	$(CC) $(GCC_FLAGS) -c $(KERNEL_DIR)/interrupts.c -o $(BUILD_DIR)/interrupts.o
	$(CC) $(GCC_FLAGS) -c $(KERNEL_DIR)/console.c -o $(BUILD_DIR)/console.o
	$(CC) $(GCC_FLAGS) -c $(KERNEL_DIR)/serial.c -o $(BUILD_DIR)/serial.o
	$(CC) $(GCC_FLAGS) -c $(KERNEL_DIR)/io.c -o $(BUILD_DIR)/io.o

	# Enlazar todos los objetos en kernel.bin
	$(LD) $(LD_FLAGS) -o $@ $(BUILD_DIR)/multiboot_header.o $(BUILD_DIR)/kernel.o \
                      $(BUILD_DIR)/scheduler.o $(BUILD_DIR)/debug.o \
                      $(BUILD_DIR)/keyboard.o $(BUILD_DIR)/interrupts.o \
                      $(BUILD_DIR)/console.o $(BUILD_DIR)/serial.o \
                      $(BUILD_DIR)/io.o $(LIBGCC)

# Generar grub.cfg
$(GRUB_CFG):
	mkdir -p $(ISO_DIR)/boot/grub
	echo "set timeout=5\nset default=0\n\nmenuentry 'MyOS' {\n    multiboot /boot/kernel.bin\n    boot\n}" > $(GRUB_CFG)

# Generar la imagen ISO
$(ISO_IMAGE): $(BUILD_DIR)/bootloader.bin $(KERNEL_BIN) $(GRUB_CFG)
	mkdir -p $(ISO_DIR)/boot
	cp $(BUILD_DIR)/bootloader.bin $(ISO_DIR)/boot/
	cp $(KERNEL_BIN) $(ISO_DIR)/boot/
	grub-mkrescue -o $@ $(ISO_DIR)

# Limpiar archivos generados
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(ISO_DIR)
