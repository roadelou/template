################################### METADATA ###################################

# Contributors: roadelou
# Contacts: 
# Creation Date: 2021-11-13
# Language: Makefile
# Make version: GNU Make 4.3

################################### ALIASES ####################################

# Root directory of the git repository
TOP = $(CURDIR)

# The directory hodling the source code.
SRC_DIR = $(TOP)/src

# The directory holding the header files.
HEAD_DIR = $(TOP)/include

# Directory holding all of the test files.
TEST_DIR = $(TOP)/test

# Directory holding the documentation.
DOC_DIR = $(TOP)/doc

# Flag to include all headers
INCLUDE = -I $(HEAD_DIR)

# Flag to trigger compiler warnings
WARN = -Wall -pedantic

# The command used to format a C source file.
FORMAT = clang-format -i --style="{BasedOnStyle: llvm, IndentWidth: 4}" 

# Pinning the C standard used for the compilation of the code.
#
# NOTE
# ====
# popen and pclose are POSIX extensions, which aren't enabled by default. To use
# them (in write_command_output from dynamic_format) we have to specify that we
# are compiling under a POSIX system.
#
# setenv (used in the main to set TEMPLATE_USER and TEMPLATE_CONTACT) requires
# at least posix 200112L.
C_STD = --std=c99 -D_POSIX_C_SOURCE=200112L

# Adding RPM distro C flags if they are provided.
C_FLAGS = $(RPM_OPT_FLAGS) $(WARN) $(INCLUDE) $(C_STD)
#
# Additional flags used for the debug builds.
ifeq ($(DEBUG),1)
C_FLAGS += -O0 -g
endif

# The name of the compiled executable
BUILD_DIR = $(TOP)/build
#
# The location where the executable will be installed.
BIN_DIR = $(DESTDIR)/usr/bin
#
# The location where the man pages should be installed.
MAN_DIR = $(DESTDIR)/usr/share/man
#
# The location where the shared library should be installed. Can be overriden
# because not all Linux distributions put the libraaries in the same directory.
# Redhat puts them in /usr/lib64 while debian puts them in /usr/lib.
ifeq ($(DEBIAN),TRUE)
#
# Meant for Debian
LIB_DIR = $(DESTDIR)/usr/lib
else
#
# Meant for Redhat
LIB_DIR = $(DESTDIR)/usr/lib64
endif
#
# The directory where the header file should be installed on the target system.
INCLUDE_DIR = $(DESTDIR)/usr/include
#
# All the preset template files.
TEMPLATES = $(wildcard $(TOP)/etc/*.template)
#
# The location where the configuration format files will be stored.
CONFIG = $(DESTDIR)/etc/roadelou_template
#
# The spec file used to automate the compilation of the package.
SPEC = $(TOP)/template.spec
#
# The fakeroot used to compile the debian package.
FAKEROOT_DEBIAN = $(TOP)/template_1.13-1
#
# A variable used to hold the path to every file which should be deleted when
# the clean command is used.
TO_CLEAN =

# We force the default rule to be 'all' even though it isn't the first rule in
# the Makefile (because of the includes).
.DEFAULT_GOAL = all

# Including the definitions for the header files.
include $(HEAD_DIR)/Makefile
#
# Including the defintions for the source code compilation.
include $(SRC_DIR)/Makefile
#
# Including the definitions for the tests.
include $(TEST_DIR)/Makefile
#
# Including the definitions for the documentation files.
include $(DOC_DIR)/Makefile

################################### SPECIAL ####################################

.PHONY: debug all clean install uninstall fedora test debian format

#################################### RULES #####################################

# Release build.
all: elfs manpages | $(BUILD_DIR)

# The test rule lives inside of test/Makefile

# PHONY rule to automatically format the codebase.
format:
	find $(TOP) -type f -name '*.h' | xargs $(FORMAT)
	find $(TOP) -type f -name '*.c' | xargs $(FORMAT)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(CONFIG):
	mkdir -p $(CONFIG)

$(MAN_DIR):
	mkdir -p $(MAN_DIR)

install: all $(TEMPLATES) | $(BIN_DIR) $(CONFIG) $(MAN_DIR)
	# Installing the executables to the required location. We have to remove the
	# '.elf' from every executable file once installed.
	$(foreach ELF,$(ELF_LIST),install -m 755 -T $(ELF) $(BIN_DIR)/$(patsubst $(ELF_BUILD_DIR)/%.elf,%,$(ELF));)
	# Also copying the format files to the expected location.
	mkdir -p $(CONFIG)
	install -m 664 -t $(CONFIG) $(TEMPLATES) 
	# Also copying the man-pages.
	mkdir -p $(MAN_DIR)/man1
	install -m 664 -t $(MAN_DIR)/man1/ $(MAN_PAGE_LIST)
	# Copying the shared library, otherwise the executables won't work.
	mkdir -p $(LIB_DIR)
	install -m 755 $(TEMPLATE_LIB) $(LIB_DIR)/$(LIB_NAME)
	# Copying the headers of the template library.
	mkdir -p $(INCLUDE_DIR)
	install -m 664 $(HEAD_DIR)/template.h $(INCLUDE_DIR)/template.h
	cp -r $(HEAD_DIR)/template $(INCLUDE_DIR)/template

# Target fedora should also depend on every source file and header!
fedora: $(SPEC)
	fedpkg --release f35 local

debian: 
	# We start by creating the fakeroot to build the debian package.
	mkdir -p $(FAKEROOT_DEBIAN)
	# We compile the source code.
	make -j12
	# We install the code in the fakeroot.
	DESTDIR=$(FAKEROOT_DEBIAN) DEBIAN=TRUE make install
	# We copy the package metadata inside the fakeroot.
	mkdir -p $(FAKEROOT_DEBIAN)/DEBIAN
	install -m 664 DEBIAN.control $(FAKEROOT_DEBIAN)/DEBIAN/control
	# Finally, we build the debian package itself.
	dpkg-deb --build $(FAKEROOT_DEBIAN)


$(BIN_DIR):
	mkdir -p $(BIN_DIR)

uninstall:
	rm -f $(BIN_DIR)/template
	rm -f $(BIN_DIR)/template-run
	rm -rf $(CONFIG)
	rm -f $(MAN_DIR)/man1/template.1.gz
	rm -f $(MAN_DIR)/man1/template-run.1.gz
	rm -f $(LIB_DIR)/$(LIB_NAME)
	rm -f $(INCLUDE_DIR)/template.h
	rm -rf $(INCLUDE_DIR)/template

clean:
	rm -f $(TO_CLEAN)
	# Removing fedora package leftovers
	rm -f *.src.rpm *.log .*.ld
	rm -rf x86_64
	# Removing the debian package leftovers.
	rm -rf $(FAKEROOT_DEBIAN)
	rm -f *.deb

##################################### EOF ######################################
