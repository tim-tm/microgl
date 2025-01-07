CC=gcc
CFLAGS=-Wall -Wextra -pedantic -I./include
DEFINES=
LIBS=-lm

SRCDIR=src
EXAMPLESDIR=examples
BUILDDIR=build

SRC=$(SRCDIR)/mgl.c

ifeq ($(PLATFORM),RPI_PICO)
$(error Unimplemented)
else ifeq ($(PLATFORM),WIRINGPI)
$(error Unimplemented)
else
$(warning Platform not specified, \
		  building for generic platform \
		  without an actual implementation)
SRC += $(SRCDIR)/mgl_platform_generic.c
endif

ifeq ($(PREFIX),)
    PREFIX := /usr
endif

OBJ=$(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRC))

EXAMPLES=$(wildcard $(EXAMPLESDIR)/*.c)
EXAMPLESOBJ=$(patsubst $(EXAMPLESDIR)/%.c, $(BUILDDIR)/%, $(EXAMPLES))

HEADERNAME=mgl.h
HEADER=include/$(HEADERNAME)

BINARYNAME=libmgl.so
BINARY=$(BUILDDIR)/$(BINARYNAME)

all: always $(BINARY)

$(BINARY): $(BUILDDIR)/$(OBJ)
	$(CC) $(CFLAGS) -shared $(OBJ) -o $(BINARY) $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(DEFINES) -c -fpic $< -o $@

examples: always $(EXAMPLES:.c=)

%: %.c
	$(CC) $(CFLAGS) $(DEFINES) -o $(BUILDDIR)/$@ $< -lmgl

always:
	mkdir -p $(BUILDDIR)
	mkdir -p $(BUILDDIR)/examples

install: $(BINARY)
	install -d $(DESTDIR)$(PREFIX)/lib/
	install -m 644 $(BINARY) $(DESTDIR)$(PREFIX)/lib/
	install -d $(DESTDIR)$(PREFIX)/include/
	install -m 644 $(HEADER) $(DESTDIR)$(PREFIX)/include/

uninstall: $(BINARY)
	rm $(DESTDIR)$(PREFIX)/lib/$(BINARYNAME)
	rm $(DESTDIR)$(PREFIX)/include/$(HEADERNAME)

clean:
	rm -rf $(BUILDDIR)
