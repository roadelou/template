################################### METADATA ###################################

# Contributors: roadelou
# Contacts: 
# Creation Date: 2021-11-13
# Language: Makefile
# Make version: GNU Make 4.3

################################### ALIASES ####################################

# NOTE
######
# Don't call this Makefile directly, instead use the one provided in the root
# directory.

# EXEC
######
# The Makefile used to create the executables.
EXEC_MAKEFILE = $(SRC_DIR)/exec/Makefile

# EXTENSION
###########
# The Makefile used to create the extension library.
EXTENSION_MAKEFILE = $(SRC_DIR)/extension/Makefile

# FORMAT
########
# The Makefile used to create the format library.
FORMAT_MAKEFILE = $(SRC_DIR)/format/Makefile

# UTIL
######
# The Makefile used to create the util library.
UTIL_MAKEFILE = $(SRC_DIR)/util/Makefile

# TEST
######
# The Makefile used to create the test library.
TEST_MAKEFILE = $(SRC_DIR)/test/Makefile

# OBJECT FILES
##############
#
# Flags used to compile the objects for the template library.
C_LIB_OBJ_FLAGS = $(C_FLAGS) -fPIC
#
# The list of objects and debug objects to build, which will be populated by the
# included leaf Makefiles.
OBJ_LIST =

# LIBRARY
#########
#
# The directory where the compiled library will be stored.
LIB_BUILD_DIR = $(BUILD_DIR)/lib
#
# The compiled library path.
TEMPLATE_LIB = $(LIB_BUILD_DIR)/libtemplate.so
#
# The library with the test functions.
TEST_LIB = $(LIB_BUILD_DIR)/libtemplate_test.so
#
# Flags used to compile the template library itself.
C_TEMPLATE_LIB_FLAGS = $(C_FLAGS) -shared -Wl,-soname,libtemplate.so
#
# Flags used to compile the test library.
C_TEST_LIB_FLAGS = $(C_FLAGS) -shared -Wl,-soname,libtemplate_test.so

# INCLUDING MAKEFILES
#####################
#
# Including the Makefiles from the children directories to use their rules and
# populate the list of objects to build.
include $(UTIL_MAKEFILE)
include $(EXTENSION_MAKEFILE)
include $(FORMAT_MAKEFILE)
include $(TEST_MAKEFILE)
include $(EXEC_MAKEFILE)

# EXECUTABLES
#############
#
# We put the executables in the exec directory, since it would be empty anyway.
ELF_BUILD_DIR = $(BUILD_DIR)/exec
#
# Each EXEC_OBJ contaons a main and will have its own ELF.
ELF_LIST = $(patsubst $(EXEC_BUILD_DIR)/%.o,$(ELF_BUILD_DIR)/%.elf,$(EXEC_OBJ))

#
# The dynamic library and every object file should also be cleaned by the
# `make clean` command.
TO_CLEAN += $(TEMPLATE_LIB) $(TEST_LIB) $(ELF_LIST)

# We define a PHONY rule to build all of the ELF files.
.PHONY: elfs
#
# The object files are marked as intermediary so that they are cleaned up
# automatically.
.INTERMEDIATE: $(OBJ_LIST) $(TEST_OBJ) $(EXEC_OBJ)

# Rule to create the library build directory.
$(LIB_BUILD_DIR): | $(BUILD_DIR)
	mkdir -p $(LIB_BUILD_DIR)

# RULES FOR LIBRARY
###################
# Rules to build the libraries from the object files.
$(TEMPLATE_LIB): $(OBJ_LIST) | $(LIB_BUILD_DIR)
	$(CC) $(C_TEMPLATE_LIB_FLAGS) -o $@ $^

# RULES FOR TEST LIBRARY
########################
# Rules to build the library with the test functions.
$(TEST_LIB): $(TEST_OBJ) | $(LIB_BUILD_DIR)
	$(CC) $(C_TEST_LIB_FLAGS) -o $@ $^

# RULES FOR EXECUTABLES
#######################
# Rules to build the executables and link them against the libraries.
$(ELF_BUILD_DIR)/%.elf: $(EXEC_BUILD_DIR)/%.o $(TEMPLATE_LIB) | $(ELF_BUILD_DIR)
	$(CC) $(C_FLAGS) -L$(LIB_BUILD_DIR) -o $@ $< -ltemplate

#
# PHONY rule to build every elf at once.
elfs: $(ELF_LIST)

##################################### EOF ######################################
