# Project name
PRJNAME := saferm

# Compiler
CC := cc

# Compile flags
CFLAGS := -Werror -Wall -std=c99

# Source directory
SRCDIR := src

# Precomipiled libraries that have to stay
LIBDIR := lib

# Static libraries
STATLIB := $(shell find $(LIBDIR)  -depth -maxdepth 1 -type f -name *.a)

# Combined static library
COMBLIB := $(LIBDIR)/lib$(PRJNAME).a

# Linking flags
LFLAGS := -L./$(LIBDIR) -l$(PRJNAME)

# Build files go here
BUILDDIR := build

# All source files
SOURCES := $(shell find $(SRCDIR) -type f -name *.c)

# Derive Object files from source files
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.c=.o)) $(AOBJECTS)

# Derive Header files from source files
HEADERS := $(SOURCES:.c=.h)

# Export dir
TARDIR := target


# Default target
default: $(OBJECTS) $(COMBLIB)
	$(CC) $(CFLAGS) $(OBJECTS) $(LFLAGS) -o ./saferm.out


# Default target to create a combined static library
$(COMBLIB):
	@cd $(LIBDIR) && \
	for file in ./*.a ; do \
		ar -x $$file  ; \
	done 
	@cd ../
	@ar -rcs $@ $(LIBDIR)/*.o
	@/usr/bin/rm -r $(LIBDIR)/*.o



# Custom target for main
$(BUILDDIR)/main.o: $(SRCDIR)/main.c
	@echo "Building main.o"
	$(CC) $(CFLAGS) -c $< -o $@




# Default target for source files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(SRCDIR)/%.h
	@echo "Building $(shell basename $@)"
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) -c $< -o $@
