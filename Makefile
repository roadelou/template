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

# Adding RPM distro C flags if they are provided.
CFLAGS = $(RPM_OPT_FLAGS) $(WARN) $(INCLUDE)

# The name of the compiled executable
BUILDDIR = $(TOP)/build
EXEC = $(BUILDDIR)/template.elf
# The location where the executable will be installed.
BINDIR = $(DESTDIR)/usr/bin

# All the preset template files.
TEMPLATES = $(wildcard $(TOP)/etc/*.template)
# The location where the configuration format files will be stored.
CONFIG = $(DESTDIR)/etc/roadelou_template

################################### SPECIAL ####################################

.PHONY: all clean install uninstall

#################################### RULES #####################################

# The compilation flow here is rather straightforward.
all: $(EXEC)

$(EXEC): $(SRC) $(HEAD) $(BUILDDIR)
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -f $(EXEC)

install: $(EXEC) $(TEMPLATES) $(BINDIR)
	install -m 755 $(EXEC) $(BINDIR)/template
	# Also copying the format files to the expected location.
	mkdir -p $(CONFIG)
	install -m 664 -t $(CONFIG) $(TEMPLATES) 

$(BINDIR):
	mkdir -p $(BINDIR)

uninstall:
	rm -f $(BINDIR)/template
	rm -rf $(CONFIG)

##################################### EOF ######################################
