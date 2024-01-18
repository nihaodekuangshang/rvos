# Building
TGT=riscv64-linux-gnu-
CC := $(TGT)gcc
LD := $(TGT)ld
GDB := $(TGT)gdb
AR := $(TGT)ar
MODE := release
KERNEL_ELF := target/os
KERNEL_BIN := $(KERNEL_ELF).bin
DISASM_TMP := target/asm
FS_IMG := ../user/target/$(TARGET)/$(MODE)/fs.img
APPS := ../user/src/bin/*

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
ifeq ($(MODE), release)
	MODE_ARG := --release
endif

# KERNEL ENTRY
KERNEL_ENTRY_PA := 0x80200000

# Binutils
OBJDUMP := $(TGT)objdump 
OBJCOPY := $(TGT)objcopy #--binary-architecture=riscv64

# Disassembly
DISASM ?= -D

# Object

OBJ = target/entry.o target/main.o  target/io.o  

LIB := target/string.a  target/kelio.a  target/sbi.a

# Run usertests or usershell
TEST ?=

build:  $(KERNEL_BIN) 


$(KERNEL_BIN): kernel
	@$(OBJCOPY) $(KERNEL_ELF) --strip-all -O binary $@

fs-img: $(APPS)
	@cd ../user && make build TEST=$(TEST)
	@rm -f $(FS_IMG)
	@cd ../easy-fs-fuse && cargo run --release -- -s ../user/src/bin/ -t ../user/target/riscv64gc-unknown-none-elf/release/

$(APPS):

kernel: build_kernel
	@echo Platform: $(BOARD)
	@cp src/linker-$(BOARD).ld src/linker.ld
	@$(LD) $(OBJ) $(LIB)  -T src/linker.ld  -o $(KERNEL_ELF)
	@rm src/linker.ld

build_kernel:$(OBJ) $(LIB)

target/%.o:src/%.s
	$(CC)  $< -nostdlib  -c -o $@

target/%.o:src/%.c
	$(CC)  $< -nostdlib -std=c23  -I./src/include  -c -o $@

target/%.a:src/lib/%.c
	$(CC)  $< -nostdlib -std=c23   -I./src/include -c -o target/a.out
	$(AR)  -rc $@  target/a.out
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
