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

#
# Flags used to compile the objects for the template library.
C_LIB_OBJ_FLAGS = $(C_FLAGS) -fPIC

# LIBRARY
#########
#
# The name of the template library file.
LIB_NAME = libtemplate.so
#
# The name of the debugging library.
LIB_DEBUG_NAME = libtemplate.debug.so
#
# The directory where the compiled library will be stored.
LIB_BUILD_DIR = $(BUILD_DIR)/lib
#
# The compiled library path.
TEMPLATE_LIB = $(LIB_BUILD_DIR)/$(LIB_NAME)
#
# Same for debugging.
TEMPLATE_DEBUG_LIB = $(LIB_BUILD_DIR)/$(LIB_DEBUG_NAME)
#
# Flags used to compile the template library itself.
C_LIB_FLAGS = $(C_FLAGS) -shared -Wl,-soname,libtemplate.so
#
# Flags used to compile the template library itself.
C_LIB_DEBUG_FLAGS = $(C_FLAGS) -shared -Wl,-soname,libtemplate.debug.so

# The dynamic library should also be cleaned by the `make clean` command.
TO_CLEAN += $(TEMPLATE_LIB) $(TEMPLATE_DEBUG_LIB)

# Including the Makefiles from the children directories to use their rules.
#
# NOTE
######
# The order of the inclusions is important, it corresponds to compilation
# dependancies.
include $(UTIL_MAKEFILE)
include $(EXTENSION_MAKEFILE)
include $(FORMAT_MAKEFILE)
include $(TEST_MAKEFILE)

# Rule to create the library build directory.
$(LIB_BUILD_DIR): | $(BUILD_DIR)
	mkdir -p $(LIB_BUILD_DIR)

$(TEMPLATE_LIB): $(UTIL_OBJ) $(EXTENSION_OBJ) $(FORMAT_OBJ) $(TEST_OBJ) | $(LIB_BUILD_DIR)
	$(CC) $(C_LIB_FLAGS) -o $(TEMPLATE_LIB) $(UTIL_OBJ) $(EXTENSION_OBJ) $(FORMAT_OBJ) $(TEST_OBJ)

$(TEMPLATE_DEBUG_LIB): $(UTIL_DEBUG_OBJ) $(EXTENSION_DEBUG_OBJ) $(FORMAT_DEBUG_OBJ) $(TEST_DEBUG_OBJ) | $(LIB_BUILD_DIR)
	$(CC) $(C_LIB_DEBUG_FLAGS) -o $(TEMPLATE_DEBUG_LIB) $(UTIL_DEBUG_OBJ) $(EXTENSION_DEBUG_OBJ) $(FORMAT_DEBUG_OBJ) $(TEST_DEBUG_OBJ)

# The executables depend on the main library, hence they have to be included
# last.
include $(EXEC_MAKEFILE)

##################################### EOF ######################################
