################################### METADATA ###################################

# Contributors: roadelou
# Contacts: 
# Creation Date: 2020-10-09
# Language: Makefile

################################### ALIASES ####################################

# Root directory of the git repository
TOP = $(CURDIR)

# All source files
SRC = $(wildcard src/*.c)
# All the headers, used for recompilation.
HEAD = $(wildcard include/*.h)

# Flag to include all headers
INCLUDE = -I $(TOP)/include/

# Flag to trigger compiler warnings
WARN = -Wall -pedantic

# Pinning the C standard used for the compilation of the code.
#
# NOTE
# ====
# popen and pclose are POSIX extensions, which aren't enabled by default. To use
# them (in write_command_output from dynamic_format) we have to specify that we
# are compiling under a POSIX system.
C_STD = --std=c99 -D_POSIX_C_SOURCE=2

# Adding RPM distro C flags if they are provided.
CFLAGS = $(RPM_OPT_FLAGS) $(WARN) $(INCLUDE) $(C_STD)

# The name of the compiled executable
BUILDDIR = $(TOP)/build
EXEC = $(BUILDDIR)/template.elf
# Target used for debugging
DEBUG = $(BUILDDIR)/template.debug.elf
# The location where the executable will be installed.
BINDIR = $(DESTDIR)/usr/bin

# All the preset template files.
TEMPLATES = $(wildcard $(TOP)/etc/*.template)
# The location where the configuration format files will be stored.
CONFIG = $(DESTDIR)/etc/roadelou_template

# The aliases used to create the RPM package.
#
# The spec file used to automate the compilation of the package.
SPEC = $(TOP)/template.spec

################################### SPECIAL ####################################

.PHONY: debug all clean install uninstall fedora

#################################### RULES #####################################

# The compilation flow here is rather straightforward.
all: $(EXEC)

$(EXEC): $(SRC) $(HEAD) | $(BUILDDIR)
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)

debug: $(DEBUG)

$(DEBUG): $(SRC) $(HEAD) | $(BUILDDIR)
	$(CC) $(CFLAGS) -g -O0 $(SRC) -o $(DEBUG)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -f $(EXEC) $(DEBUG)
	# Removing fedora package leftovers
	rm -f *.src.rpm *.log
	rm -rf x86_64

install: $(EXEC) $(TEMPLATES) | $(BINDIR)
	install -m 755 $(EXEC) $(BINDIR)/template
	# Also copying the format files to the expected location.
	mkdir -p $(CONFIG)
	install -m 664 -t $(CONFIG) $(TEMPLATES) 

fedora: $(SRC) $(SPEC) $(HEAD) | $(BUILDDIR)
	fedpkg --release f34 local

$(BINDIR):
	mkdir -p $(BINDIR)

uninstall:
	rm -f $(BINDIR)/template
	rm -rf $(CONFIG)

##################################### EOF ######################################
