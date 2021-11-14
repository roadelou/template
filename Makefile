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

# Flag to include all headers
INCLUDE = -I $(HEAD_DIR)

# Flag to trigger compiler warnings
WARN = -Wall -pedantic

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
DEBUG_FLAGS = -O0 -g

# The name of the compiled executable
BUILD_DIR = $(TOP)/build
#
# The location where the executable will be installed.
BIN_DIR = $(DESTDIR)/usr/bin
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

################################### SPECIAL ####################################

.PHONY: debug all clean install uninstall fedora test

#################################### RULES #####################################

# Release build.
all: $(EXEC_ELF) | $(BUILD_DIR)

# Debug build.
debug: $(EXEC_DEBUG_ELF) | $(BUILD_DIR)

# Running the tests.
test: $(TEST_CSV) | $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

install: $(EXEC_ELF) $(TEMPLATES) | $(BIN_DIR)
	install -m 755 $(EXEC_TEMPLATE_ELF) $(BIN_DIR)/template
	install -m 755 $(EXEC_TEMPLATE_RUN_ELF) $(BIN_DIR)/template-run
	# Also copying the format files to the expected location.
	mkdir -p $(CONFIG)
	install -m 664 -t $(CONFIG) $(TEMPLATES) 

# Target fedora should also depend on every source file and header!
fedora: $(SPEC) | $(BUILD_DIR)
	fedpkg --release f35 local

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

uninstall:
	rm -f $(BIN_DIR)/template
	rm -rf $(CONFIG)

clean:
	rm -f $(TO_CLEAN)
	# Removing fedora package leftovers
	rm -f *.src.rpm *.log
	rm -rf x86_64

##################################### EOF ######################################
