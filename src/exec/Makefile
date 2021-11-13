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

# Note that the X_HEAD variables are defined in the Makefiles of the include
# folder.

# The build directory for this part of the library. It is called bin for the
# sake of clarity, even though it isn't very consisten with how the rest of the
# compilation works.
EXEC_BUILD_DIR = $(BUILD_DIR)/bin

# TEMPLATE
##########
# The source code for the template executable.
EXEC_TEMPLATE_SRC = $(SRC_DIR)/exec/template.c
#
# The object file containing the code for the template executable.
EXEC_TEMPLATE_OBJ = $(EXEC_BUILD_DIR)/template.o
#
# The object file containing the code used for debugging purposes.
EXEC_TEMPLATE_DEBUG_OBJ = $(EXEC_BUILD_DIR)/template.debug.o
#
# The linked template executable.
EXEC_TEMPLATE_ELF = $(EXEC_BUILD_DIR)/template.elf
#
# The linked executable used for debugging.
EXEC_TEMPLATE_DEBUG_ELF = $(EXEC_BUILD_DIR)/template.debug.elf

# EXEC
######
# The object files for the executables.
EXEC_OBJ = $(EXEC_TEMPLATE_OBJ)
EXEC_DEBUG_OBJ = $(EXEC_TEMPLATE_DEBUG_OBJ)
#
# The execuatables themselves.
EXEC_ELF = $(EXEC_TEMPLATE_ELF)
EXEC_DEBUG_ELF = $(EXEC_TEMPLATE_DEBUG_ELF)

# TO CLEAN
##########
# Used for the global clean rule.
TO_CLEAN += $(EXEC_OBJ) $(EXEC_DEBUG_OBJ) $(EXEC_ELF) $(EXEC_DEBUG_ELF)

################################### SPECIAL ####################################

# The special rule modifiers (.PHONY etc...) go here

#################################### RULES #####################################

$(EXEC_BUILD_DIR):
	mkdir -p $(EXEC_BUILD_DIR)

# RELEASE
#########
$(EXEC_TEMPLATE_OBJ): $(EXEC_TEMPLATE_SRC) $(EXEC_TEMPLATE_HEAD) | $(EXEC_BUILD_DIR)
	$(CC) $(C_FLAGS) -c -o $(EXEC_TEMPLATE_OBJ) $(EXEC_TEMPLATE_SRC)

$(EXEC_TEMPLATE_ELF): $(EXEC_TEMPLATE_OBJ) $(UTIL_OBJ) $(EXTENSION_OBJ) $(FORMAT_OBJ) | $(EXEC_BUILD_DIR)
	$(CC) $(C_FLAGS) -o $(EXEC_TEMPLATE_ELF) $(EXEC_TEMPLATE_OBJ) $(UTIL_OBJ) $(EXTENSION_OBJ) $(FORMAT_OBJ)

# DEBUG
#######
$(EXEC_TEMPLATE_DEBUG_OBJ): $(EXEC_TEMPLATE_SRC) $(EXEC_TEMPLATE_HEAD) | $(EXEC_BUILD_DIR)
	$(CC) $(C_FLAGS) -c -o $(EXEC_TEMPLATE_DEBUG_OBJ) $(EXEC_TEMPLATE_SRC)

$(EXEC_TEMPLATE_DEBUG_ELF): $(EXEC_TEMPLATE_DEBUG_OBJ) $(UTIL_DEBUG_OBJ) $(EXTENSION_DEBUG_OBJ) $(FORMAT_DEBUG_OBJ) | $(EXEC_BUILD_DIR)
	$(CC) $(C_FLAGS) -o $(EXEC_TEMPLATE_DEBUG_ELF) $(EXEC_TEMPLATE_DEBUG_OBJ) $(UTIL_DEBUG_OBJ) $(EXTENSION_DEBUG_OBJ) $(FORMAT_DEBUG_OBJ)

##################################### EOF ######################################