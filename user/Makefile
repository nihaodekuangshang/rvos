
# Building
TGT=riscv64-linux-gnu-
CC := $(TGT)gcc
LD := $(TGT)ld
GDB := $(TGT)gdb
AR := $(TGT)ar

# Binutils
OBJDUMP := $(TGT)objdump 
OBJCOPY := $(TGT)objcopy #--binary-architecture=riscv64




APP_DIR := src
LIB_DIR := src/lib
TARGET_DIR := target
BIN_DIR := bin
LIB := src/lib/lib.a
LIB_ALL := $(wildcard $(LIB_DIR)/*.c)
LIBS := $(patsubst $(LIB_DIR)/%.c, $(TARGET_DIR)/%.a, $(LIB_ALL))

APPS := $(wildcard $(APP_DIR)/*.c)
OBJS := $(patsubst $(APP_DIR)/%.c, $(TARGET_DIR)/%.o, $(APPS))
ELFS := $(patsubst $(APP_DIR)/%.c, $(TARGET_DIR)/%, $(APPS))
BINS := $(patsubst $(APP_DIR)/%.c, $(BIN_DIR)/%.bin, $(APPS))


elf: $(OBJS) $(LIB)
	@$(foreach obj, $(OBJS),\
		$(LD) $(obj) $(LIB)   \
		-o $(patsubst $(TARGET_DIR)/%.o, \
		$(TARGET_DIR)/%, $(obj));)
	

$(LIB):$(LIBS)
	$(AR)  -rc $@  $^

target/%.o:src/%.s
	$(CC)  $< -nostdlib -c  -o $@

target/%.o:src/%.c
	$(CC)  $< -nostdlib -std=c2x --sysroot=../sysroot \
		-isystem=/usr/include -I./src/include  -Iinclude\
		-I./src/lib/include  \
		-c -o $@

target/%.a:src/lib/%.c
	$(CC)  $< -nostdlib -std=c2x --sysroot=../sysroot/ \
		-Iinclude -I./src/include \
		 -isystem=/usr/include -I./src/lib/include  \
		-c -o $@

binary: elf
	@$(foreach elf, $(ELFS), $(OBJCOPY) $(elf) --strip-all -O binary $(patsubst $(TARGET_DIR)/%, $(BIN_DIR)/%.bin, $(elf));)

build: binary
