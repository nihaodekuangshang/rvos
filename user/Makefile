
# Building
TGT=riscv64-linux-gnu-
CC := $(TGT)gcc
LD := $(TGT)ld
GDB := $(TGT)gdb
AR := $(TGT)ar

# Binutils
OBJDUMP := $(TGT)objdump 
OBJCOPY := $(TGT)objcopy #--binary-architecture=riscv64
DISASM := -D -S
DISASM_TMP := tmp
define \n 



endef


SYSROOT := ../sysroot
INCLUDES := -I./src/include -Iinclude -I./src/lib/include
CC_FLAGS := -nostdlib -std=c2x --sysroot=../sysroot \
		-isystem=/usr/include  $(INCLUDES) \
		-c -g  


APP_DIR := src
LIB_DIR := src/lib
TARGET_DIR := target
BIN_DIR := bin
LIB := $(SYSROOT)/usr/lib/libc.a
CRTI := $(TARGET_DIR)/crti.o

APPS := $(wildcard $(APP_DIR)/*.c)
OBJS := $(patsubst $(APP_DIR)/%.c, $(TARGET_DIR)/%.o, $(APPS))
ELFS := $(patsubst $(APP_DIR)/%.c, $(TARGET_DIR)/%, $(APPS))
BINS := $(patsubst $(APP_DIR)/%.c, $(BIN_DIR)/%.bin, $(APPS))


elf: $(OBJS) $(LIB) $(CRTI)
	echo $(OBJS)
	$(foreach obj, $(OBJS),\
		$(LD) $(CRTI) $(obj) $(LIB)   \
		-T src/linker.ld \
		-o $(patsubst $(TARGET_DIR)/%.o, \
		$(TARGET_DIR)/%, $(obj)) ${\n})
	

$(CRTI): src/crt/crti.c
	$(CC) $<  $(CC_FLAGS) -o $@
target/%.o:src/%.s
	$(CC)  $< -nostdlib -c  -o $@

target/%.o:src/%.c
	$(CC) $<  $(CC_FLAGS) -o $@

target/%.a:src/lib/%.c
	$(CC) $<  $(CC_FLAGS) -o $@

binary: elf
	@$(foreach elf, $(ELFS), $(OBJCOPY) $(elf) --strip-all -O binary $(patsubst $(TARGET_DIR)/%, $(BIN_DIR)/%.bin, $(elf)) ${\n})

build: binary



disasm: binary
	@$(OBJDUMP) $(DISASM) $(KERNEL_ELF) | less

disasm-vim: binary
	 $(foreach elf,$(ELFS),$(OBJDUMP) $(DISASM) $(elf)\
		>> $(DISASM_TMP) ${\n})
	@vim $(DISASM_TMP)
	@rm $(DISASM_TMP)
