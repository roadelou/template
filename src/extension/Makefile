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
EXTENSION_BUILD_DIR = $(BUILD_DIR)/extension

# EXTENSION_MATCH
#################
# The source code for the extension match part of the library.
EXTENSION_EXTENSION_MATCH_SRC = $(SRC_DIR)/extension/extension_match.c
#
# The object file containing the code for extension_match part of the extension library.
EXTENSION_EXTENSION_MATCH_OBJ = $(EXTENSION_BUILD_DIR)/extension_match.o
#
# The object file containing the code used for debugging purposes.
EXTENSION_EXTENSION_MATCH_DEBUG_OBJ = $(EXTENSION_BUILD_DIR)/extension_match.debug.o

# FORMAT_EXTENSION
##################
# The source code for the format_extension part of the library.
EXTENSION_FORMAT_EXTENSION_SRC = $(SRC_DIR)/extension/format_extension.c
#
# The object file containing the code for format_extension part of the extension library.
EXTENSION_FORMAT_EXTENSION_OBJ = $(EXTENSION_BUILD_DIR)/format_extension.o
#
# The object file containing the code used for debugging purposes.
EXTENSION_FORMAT_EXTENSION_DEBUG_OBJ = $(EXTENSION_BUILD_DIR)/format_extension.debug.o

# GET_EXTENSION
###############
# The source code for the get_extension part of the library.
EXTENSION_GET_EXTENSION_SRC = $(SRC_DIR)/extension/get_extension.c
#
# The object file containing the code for get_extension part of the extension library.
EXTENSION_GET_EXTENSION_OBJ = $(EXTENSION_BUILD_DIR)/get_extension.o
#
# The object file containing the code used for debugging purposes.
EXTENSION_GET_EXTENSION_DEBUG_OBJ = $(EXTENSION_BUILD_DIR)/get_extension.debug.o

# GET_FORMAT_EXTENSION
######################
# The source code for the get_format_extension part of the library.
EXTENSION_GET_FORMAT_EXTENSION_SRC = $(SRC_DIR)/extension/get_format_extension.c
#
# The object file containing the code for get_format_extension part of the extension library.
EXTENSION_GET_FORMAT_EXTENSION_OBJ = $(EXTENSION_BUILD_DIR)/get_format_extension.o
#
# The object file containing the code used for debugging purposes.
EXTENSION_GET_FORMAT_EXTENSION_DEBUG_OBJ = $(EXTENSION_BUILD_DIR)/get_format_extension.debug.o

# EXTENSION
###########
# The object files for the extension library.
EXTENSION_OBJ = $(EXTENSION_EXTENSION_MATCH_OBJ) $(EXTENSION_FORMAT_EXTENSION_OBJ) $(EXTENSION_GET_EXTENSION_OBJ) $(EXTENSION_GET_FORMAT_EXTENSION_OBJ)
EXTENSION_DEBUG_OBJ = $(EXTENSION_EXTENSION_MATCH_DEBUG_OBJ) $(EXTENSION_FORMAT_EXTENSION_DEBUG_OBJ) $(EXTENSION_GET_EXTENSION_DEBUG_OBJ) $(EXTENSION_GET_FORMAT_EXTENSION_DEBUG_OBJ)

# TO CLEAN
##########
# Used for the global clean rule.
TO_CLEAN += $(EXTENSION_OBJ) $(EXTENSION_DEBUG_OBJ)

################################### SPECIAL ####################################

# The special rule modifiers (.PHONY etc...) go here

#################################### RULES #####################################

$(EXTENSION_BUILD_DIR):
	mkdir -p $(EXTENSION_BUILD_DIR)

# RELEASE
#########
$(EXTENSION_EXTENSION_MATCH_OBJ): $(EXTENSION_EXTENSION_MATCH_SRC) $(EXTENSION_EXTENSION_MATCH_HEAD) | $(EXTENSION_BUILD_DIR)
	$(CC) $(C_FLAGS) -c -o $(EXTENSION_EXTENSION_MATCH_OBJ) $(EXTENSION_EXTENSION_MATCH_SRC)

$(EXTENSION_FORMAT_EXTENSION_OBJ): $(EXTENSION_FORMAT_EXTENSION_SRC) $(EXTENSION_FORMAT_EXTENSION_HEAD) | $(EXTENSION_BUILD_DIR)
	$(CC) $(C_FLAGS) -c -o $(EXTENSION_FORMAT_EXTENSION_OBJ) $(EXTENSION_FORMAT_EXTENSION_SRC)

$(EXTENSION_GET_EXTENSION_OBJ): $(EXTENSION_GET_EXTENSION_SRC) $(EXTENSION_GET_EXTENSION_HEAD) | $(EXTENSION_BUILD_DIR)
	$(CC) $(C_FLAGS) -c -o $(EXTENSION_GET_EXTENSION_OBJ) $(EXTENSION_GET_EXTENSION_SRC)

$(EXTENSION_GET_FORMAT_EXTENSION_OBJ): $(EXTENSION_GET_FORMAT_EXTENSION_SRC) $(EXTENSION_GET_FORMAT_EXTENSION_HEAD) | $(EXTENSION_BUILD_DIR)
	$(CC) $(C_FLAGS) -c -o $(EXTENSION_GET_FORMAT_EXTENSION_OBJ) $(EXTENSION_GET_FORMAT_EXTENSION_SRC)

# DEBUG
#######
$(EXTENSION_EXTENSION_MATCH_DEBUG_OBJ): $(EXTENSION_EXTENSION_MATCH_SRC) $(EXTENSION_EXTENSION_MATCH_HEAD) | $(EXTENSION_BUILD_DIR)
	$(CC) $(C_FLAGS) $(DEBUG_FLAGS) -c -o $(EXTENSION_EXTENSION_MATCH_DEBUG_OBJ) $(EXTENSION_EXTENSION_MATCH_SRC)

$(EXTENSION_FORMAT_EXTENSION_DEBUG_OBJ): $(EXTENSION_FORMAT_EXTENSION_SRC) $(EXTENSION_FORMAT_EXTENSION_HEAD) | $(EXTENSION_BUILD_DIR)
	$(CC) $(C_FLAGS) $(DEBUG_FLAGS) -c -o $(EXTENSION_FORMAT_EXTENSION_DEBUG_OBJ) $(EXTENSION_FORMAT_EXTENSION_SRC)

$(EXTENSION_GET_EXTENSION_DEBUG_OBJ): $(EXTENSION_GET_EXTENSION_SRC) $(EXTENSION_GET_EXTENSION_HEAD) | $(EXTENSION_BUILD_DIR)
	$(CC) $(C_FLAGS) $(DEBUG_FLAGS) -c -o $(EXTENSION_GET_EXTENSION_DEBUG_OBJ) $(EXTENSION_GET_EXTENSION_SRC)

$(EXTENSION_GET_FORMAT_EXTENSION_DEBUG_OBJ): $(EXTENSION_GET_FORMAT_EXTENSION_SRC) $(EXTENSION_GET_FORMAT_EXTENSION_HEAD) | $(EXTENSION_BUILD_DIR)
	$(CC) $(C_FLAGS) $(DEBUG_FLAGS) -c -o $(EXTENSION_GET_FORMAT_EXTENSION_DEBUG_OBJ) $(EXTENSION_GET_FORMAT_EXTENSION_SRC)

##################################### EOF ######################################
