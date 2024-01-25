# Building
TGT=riscv64-linux-gnu-
CC := $(TGT)gcc
LD := $(TGT)ld
GDB := $(TGT)gdb
AR := $(TGT)ar
MODE := dubug
KERNEL_ELF := target/os
KERNEL_BIN := $(KERNEL_ELF).bin
DISASM_TMP := target/asm
FS_IMG := ../user/target/fs.img
APPS := ../user/src/*
TARGET_DIR := ./target
SYSROOT ?= ../sysroot

#Flags
INCLUDE := -I./src/include/ -I./src/lib/include/
CC_FLAGS := -nostdlib -std=c2x  --sysroot=../sysroot/ \
	    -isystem=/usr/include/ $(INCLUDE) -c

LIBINCLUDE := -L$(SYSROOT)/usr/lib
# BOARD
BOARD := qemu
SBI ?= opensbi
BOOTLOADER := ../bootloader/$(SBI)-$(BOARD).bin

# GUI
GUI ?= off
ifeq ($(GUI), off)
	GUI_OPTION := -display none
endif

# Building mode argument
ifeq ($(MODE), debug)
	CC_FLAGS += -g
	DISASM := -D -S
endif

# KERNEL ENTRY
KERNEL_ENTRY_PA := 0x80200000

# Binutils
OBJDUMP := $(TGT)objdump 
OBJCOPY := $(TGT)objcopy #--binary-architecture=riscv64

# Disassembly
DISASM ?= -D


#File

C_DIR = ./src ./src/trap ./src/syscall
C_FILE := $(foreach dir,$(C_DIR),$(wildcard $(dir)/*.c ))
ASM_DIR := ./src ./src/trap 
ASM_FILE := $(foreach dir,$(ASM_DIR),$(wildcard $(dir)/*.S ))



# Object

OBJ = target/entry.o target/main.o   

LIBS := $(SYSROOT)/usr/lib/libk.a  target/kelio.a  target/sbi.a

define \n 



endef

# Run usertests or usershell
TEST ?=

build: env  $(KERNEL_BIN) 


env:
	@bash env.sh

$(KERNEL_BIN):apps  kernel
	@$(OBJCOPY) $(KERNEL_ELF) --strip-all -O binary $@

apps: $(APPS)
	@cd ../usr && make build TEST=$(TEST)

fs-img: $(APPS)
	@cd ../user && make build TEST=$(TEST)
	@rm -f $(FS_IMG)
	#@cd ../easy-fs-fuse && cargo run --release -- -s ../user/src/bin/ -t ../user/target/riscv64gc-unknown-none-elf/release/

$(APPS):

kernel: build_kernel
	@echo Platform: $(BOARD)
	@cp src/linker-$(BOARD).ld src/linker.ld
	@$(LD) $(OBJ) $(LIBS) -T src/linker.ld  -o $(KERNEL_ELF)
	@rm src/linker.ld

build_kernel:build_c build_asm $(LIB)


build_c:
	$(foreach file,$(C_FILE),$(CC) $(file) $(CC_FLAGS) -o \
		$(patsubst %.c,$(TARGET_DIR)/%.o,$(notdir $(file))) ${\n})


build_asm:
	bash ./build.sh
	$(foreach file,$(ASM_FILE),$(CC) $(file) -nostdlib -g -c -o  \
		$(patsubst %.S,$(TARGET_DIR)/%.o,$(notdir $(file))) ${\n})
#target/%.o:src/%.s
	#$(CC)  $< -nostdlib -g  -c -o $@
#
#target/%.o:src/%.c
	#$(CC)  $< -nostdlib -std=c2x -g  -I./src/include  -c -o $@

target/%.a:src/lib/%.c
	$(CC)  $< -nostdlib -std=c2x -g  -I./src/include -c -o target/a.out
	$(AR)  -rcs $@  target/a.out
	@rm target/a.out


clean:
	@rm target/*.o   $(KERNEL_ELF)

clean_all:
	@rm target/*.o target/*.a  $(KERNEL_ELF)


disasm: kernel
	@$(OBJDUMP) $(DISASM) $(KERNEL_ELF) | less

disasm-vim: kernel
	@$(OBJDUMP) $(DISASM) $(KERNEL_ELF) > $(DISASM_TMP)
	@vim $(DISASM_TMP)
	@rm $(DISASM_TMP)

run: run-inner

QEMU_ARGS := -machine virt \
			 -m 512M  \
			 -nographic \
			 -bios $(BOOTLOADER) \
			 -device loader,file=$(KERNEL_BIN),addr=$(KERNEL_ENTRY_PA) 
fdt:
	@qemu-system-riscv64 -M 128m -machine virt,dumpdtb=virt.out
	fdtdump virt.out

run-inner: build
	@qemu-system-riscv64 $(QEMU_ARGS)

debug: build
	@tmux new-session -d \
		"qemu-system-riscv64 $(QEMU_ARGS) -s -S" && \
		tmux split-window -h "$(GDB) -ex 'file $(KERNEL_ELF)' -ex 'set arch riscv:rv64' -ex 'target remote localhost:1234'" && \
		tmux -2 attach-session -d


gdbserver: build
	@qemu-system-riscv64 $(QEMU_ARGS) -s -S

gdbclient:
	@$(GDB) -ex 'file $(KERNEL_ELF)' -ex 'set arch riscv:rv64' -ex 'target remote localhost:1234'

.PHONY: build env kernel clean disasm disasm-vim run-inner fs-img gdbserver gdbclient fdt
