
DEFAULT_HOST?=riscv64-linux-gnu-
HOST?=$(DEFAULT_HOST)

AR:=$(HOST)ar
AS:=$(HOST)as
CC:=$(HOST)gcc

PREFIX:=/usr
EXEC_PREFIX:=$(PREFIX)
BOOTDIR:=/boot
LIBDIR:=$(EXEC_PREFIX)/lib
INCLUDEDIR:=$(PREFIX)/include


KELDIR := ../os/src/lib/include/kelio.h \
	  ./arch/riscv64/kernel/syscall/include/syscall.h

define \n



endef

CFLAGS:=-O2 -g 
CPPFLAGS:=

# Configure the cross-compiler to use the desired system root.
SYSROOT:=../sysroot
CC+=--sysroot=$(SYSROOT)

# Work around that the -elf gcc targets doesn't have a system include directory
# because it was configured with --without-headers rather than --with-sysroot.
ifneq ($(findstring "gnu",$(HOST)),"")
	CC+=-isystem=$(INCLUDEDIR)
endif


HOSTARCH?=riscv64

LDFLAGS?=

LIBS?=

DESTDIR?=$(SYSROOT)

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_libc -Iinclude
LIBK_CFLAGS:=$(CFLAGS)
LIBK_CPPFLAGS:=$(CPPFLAGS) -D__is_libk

ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config

CFLAGS:=$(CFLAGS) $(ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(ARCH_CPPFLAGS)
LIBK_CFLAGS:=$(LIBK_CFLAGS) $(KERNEL_ARCH_CFLAGS)
LIBK_CPPFLAGS:=$(LIBK_CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)

FREEOBJS=\
stdio/panic.o \
stdio/putchar.o \
stdio/puts.o \
stdio/printf.o \
stdio/sprintf.o \
stdio/vsprintf.o \
stdlib/abort.o \
stdlib/process.o \
stdlib/fs.o \
string/memcmp.o \
string/memcpy.o \
string/memmove.o \
string/memset.o \
string/strlen.o \
string/strnlen.o \
$(ARCH_FREEOBJS) \


HOSTEDOBJS=\
$(ARCH_HOSTEDOBJS) \

OBJS=\
$(FREEOBJS) \
$(HOSTEDOBJS) \

LIBK_OBJS=$(FREEOBJS:.o=.libk.o)

BINARIES=libc.a libk.a # Not ready for libc yet.
#BINARIES=libk.a

.PHONY: all clean install install-headers install-libs build_ah
.SUFFIXES: .o .libk.o .c .S

all:  install-libs

libc.a:  $(OBJS)
	$(AR) rcs $@ $(OBJS)


build_ah:
	$(foreach obj,$(ARCH_HOSTEDOBJS),\
		$(CC) -MD -c $(patsubst %.o,%.c,$(obj)) -o $(obj) \
		-std=c2x $(CFLAGS) $(CPPFLAGS)${\n})
libk.a: install-headers $(LIBK_OBJS)
	$(AR) rcs $@ $(LIBK_OBJS)

.c.o:
	$(CC) -MD -c $< -o $@ -std=c2x $(CFLAGS) $(CPPFLAGS)

.c.S:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

.c.libk.o:
	$(CC) -MD -c $< -o $@ -std=c2x $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

.S.libk.o:
	$(CC) -MD -c $< -o $@ $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

clean:
	rm -f $(BINARIES) *.a
	rm -f $(OBJS) $(LIBK_OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) $(LIBK_OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-libs

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)/kernel
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.
	$(foreach file,$(KELDIR),\
		cp -R --preserve=timestamps $(file) $(DESTDIR)$(INCLUDEDIR)/kernel/ ${\n})
	

install-libs: build_ah $(BINARIES)
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp $(BINARIES) $(DESTDIR)$(LIBDIR)

-include $(OBJS:.o=.d)
-include $(LIBK_OBJS:.o=.d)
