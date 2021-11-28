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

# The build directory for this part of the library.
FORMAT_BUILD_DIR = $(BUILD_DIR)/format

# DYNAMIC_FORMAT
################
# The source code for the dynamic_format part of the library.
FORMAT_DYNAMIC_FORMAT_SRC = $(SRC_DIR)/format/dynamic_format.c
#
# The object file containing the code for dynamic_format part of the format library.
FORMAT_DYNAMIC_FORMAT_OBJ = $(FORMAT_BUILD_DIR)/dynamic_format.o
#
# The object file containing the code used for debugging purposes.
FORMAT_DYNAMIC_FORMAT_DEBUG_OBJ = $(FORMAT_BUILD_DIR)/dynamic_format.debug.o

# SAFE_FORMAT
#############
# The source code for the safe_format part of the library.
FORMAT_SAFE_FORMAT_SRC = $(SRC_DIR)/format/safe_format.c
#
# The object file containing the code for safe_format part of the format library.
FORMAT_SAFE_FORMAT_OBJ = $(FORMAT_BUILD_DIR)/safe_format.o
#
# The object file containing the code used for debugging purposes.
FORMAT_SAFE_FORMAT_DEBUG_OBJ = $(FORMAT_BUILD_DIR)/safe_format.debug.o

# FORMAT
########
# The object files for the format library.
FORMAT_OBJ = $(FORMAT_DYNAMIC_FORMAT_OBJ) $(FORMAT_SAFE_FORMAT_OBJ)
FORMAT_DEBUG_OBJ = $(FORMAT_DYNAMIC_FORMAT_DEBUG_OBJ) $(FORMAT_SAFE_FORMAT_DEBUG_OBJ)

# TO CLEAN
##########
# Used for the global clean rule.
TO_CLEAN += $(FORMAT_OBJ) $(FORMAT_DEBUG_OBJ)

################################### SPECIAL ####################################

# The special rule modifiers (.PHONY etc...) go here

#################################### RULES #####################################

$(FORMAT_BUILD_DIR):
	mkdir -p $(FORMAT_BUILD_DIR)

# RELEASE
#########
$(FORMAT_DYNAMIC_FORMAT_OBJ): $(FORMAT_DYNAMIC_FORMAT_SRC) $(FORMAT_DYNAMIC_FORMAT_HEAD) | $(FORMAT_BUILD_DIR)
	$(CC) $(C_LIB_OBJ_FLAGS) -c -o $(FORMAT_DYNAMIC_FORMAT_OBJ) $(FORMAT_DYNAMIC_FORMAT_SRC)

$(FORMAT_SAFE_FORMAT_OBJ): $(FORMAT_SAFE_FORMAT_SRC) $(FORMAT_SAFE_FORMAT_HEAD) | $(FORMAT_BUILD_DIR)
	$(CC) $(C_LIB_OBJ_FLAGS) -c -o $(FORMAT_SAFE_FORMAT_OBJ) $(FORMAT_SAFE_FORMAT_SRC)

# DEBUG
#######
$(FORMAT_DYNAMIC_FORMAT_DEBUG_OBJ): $(FORMAT_DYNAMIC_FORMAT_SRC) $(FORMAT_DYNAMIC_FORMAT_HEAD) | $(FORMAT_BUILD_DIR)
	$(CC) $(C_LIB_OBJ_FLAGS) $(DEBUG_FLAGS) -c -o $(FORMAT_DYNAMIC_FORMAT_DEBUG_OBJ) $(FORMAT_DYNAMIC_FORMAT_SRC)

$(FORMAT_SAFE_FORMAT_DEBUG_OBJ): $(FORMAT_SAFE_FORMAT_SRC) $(FORMAT_SAFE_FORMAT_HEAD) | $(FORMAT_BUILD_DIR)
	$(CC) $(C_LIB_OBJ_FLAGS) $(DEBUG_FLAGS) -c -o $(FORMAT_SAFE_FORMAT_DEBUG_OBJ) $(FORMAT_SAFE_FORMAT_SRC)

##################################### EOF ######################################
