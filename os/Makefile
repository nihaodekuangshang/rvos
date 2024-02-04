# Building
TGT=riscv64-linux-gnu-
CC := $(TGT)gcc
LD := $(TGT)ld
GDB := $(TGT)gdb
AR := $(TGT)ar
RUSTC := rustc
MODE := dubug
KERNEL_ELF := target/os
KERNEL_BIN := $(KERNEL_ELF).bin
DISASM_TMP := target/asm
FS_IMG := ../user/target/fs.img
APPS := ../user/src/*
TARGET_DIR := ./target
SYSROOT ?= ../sysroot

#Flags
INCLUDE := -I./src/include -I./src/lib/include -I./src/trap/include \
	   -I./src/syscall/include -Iinclude  -I./src/task/include \
	   -I$(SYSROOT)/usr/include
CC_FLAGS := -nostdlib -std=c2x   $(INCLUDE) -c
RS_FLAGS := -L./target -L$(SYSROOT)/usr/lib/  --crate-type=staticlib   \
	    --edition=2021 --target=riscv64gc-unknown-none-elf 
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

C_DIR = ./src ./src/trap ./src/syscall ./src/task
C_FILES := $(foreach dir,$(C_DIR),$(wildcard $(dir)/*.c ))
ASM_DIR := ./src ./src/trap  ./src/task
ASM_FILES := $(foreach dir,$(ASM_DIR),$(wildcard $(dir)/*.S ))
RS_DIR := 
RS_FILES := $(foreach dir,$(RS_DIR),$(wildcard $(dir)/*.rs ))

RS_REQ := $(TARGET_DIR)/liblang_item.rlib
CH_FILES := 
RH_FILES := #src/batch.rs

# Object

OBJ =\
target/entry.o \
target/main.o \
target/link_app.o \
target/loader.o \
target/task.o \
target/taskContext.o \
target/switch.o \
target/trap.o \
target/trap_cont.o \
target/context.o \
target/timer.o \
target/syscall.o \
target/process.o \
target/fs.o \


LIBS :=  $(SYSROOT)/usr/lib/libk.a  \
	target/kelio.a  target/sbi.a

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
	@cd ../user && bash ./build_lk.sh

fs-img: $(APPS)
	@cd ../user && make build TEST=$(TEST)
	@rm -f $(FS_IMG)
	#@cd ../easy-fs-fuse && cargo run --release -- -s ../user/src/bin/ -t ../user/target/riscv64gc-unknown-none-elf/release/

$(APPS):

kernel: build_kernel
	@echo Platform: $(BOARD)
	@cp src/linker-$(BOARD).ld src/linker.ld
	$(LD) $(OBJ) $(LIBS) -T src/linker.ld  -o $(KERNEL_ELF)
	@rm src/linker.ld

build_kernel: build_c build_asm $(LIBS)

binding_cheader:


binding_rheader:
	$(foreach file,$(RH_FILES),cbindgen $(file) \
		--config ./cbindgen.toml \
		-o $(patsubst %.rs,$(dir $(file))/include/%.h,$(notdir $(file))) ${\n})

build_rs: $(RS_REQ)
	$(foreach file,$(RS_FILES),$(RUSTC) $(file) $(RS_FLAGS) \
		--crate-name=$(patsubst %.rs,%,$(notdir $(file)))   \
		--out-dir $(TARGET_DIR) ${\n})

$(RS_REQ): src/lang_item.rs
	$(RUSTC) src/lang_item.rs   \
 		-L./target   --crate-type=rlib   \
		--edition=2021 --target=riscv64gc-unknown-none-elf  \
		--crate-name=lang_item --out-dir $(TARGET_DIR) 

build_c:
	echo $(C_FILES)
	$(foreach file,$(C_FILES),$(CC) $(file) $(CC_FLAGS) -o \
		$(patsubst %.c,$(TARGET_DIR)/%.o,$(notdir $(file))) ${\n})


build_asm:
	bash ./build.sh
	$(foreach file,$(ASM_FILES),$(CC) $(file) -nostdlib -g -c -o  \
		$(patsubst %.S,$(TARGET_DIR)/%.o,$(notdir $(file))) ${\n})
#target/%.o:src/%.s
	#$(CC)  $< -nostdlib -g  -c -o $@
#
#target/%.o:src/%.c
	#$(CC)  $< -nostdlib -std=c2x -g  -I./src/include  -c -o $@

target/%.a:src/lib/%.c
	$(CC)  $< $(CC_FLAGS) -o $(patsubst %.c,\
		$(TARGET_DIR)/%.o,$(notdir $<))
	$(AR)  -rcs $@  $(patsubst %.c,\
		$(TARGET_DIR)/%.o,$(notdir $<))
	rm $(patsubst %.c,\
		$(TARGET_DIR)/%.o,$(notdir $<))

$(SYSROOT)/usr/lib/libk.a:
	@pushd ../libc/
	@make 
	@popd

clean:
	@rm target/*.o   $(KERNEL_ELF)

clean_all:
	@rm target/*.o target/*.a  target/*.rlib \
		$(KERNEL_ELF) $(KERNEL_BIN)


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
