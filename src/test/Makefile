################################### METADATA ###################################

# Contributors: roadelou
# Contacts: 
# Creation Date: 2021-11-14
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
TEST_BUILD_DIR = $(BUILD_DIR)/test

# TEST_INTEGER
##############
# The source code for the test_integer part of the library.
TEST_TEST_INTEGER_SRC = $(SRC_DIR)/test/test_integer.c
#
# The object file containing the code for test_integer part of the test library.
TEST_TEST_INTEGER_OBJ = $(TEST_BUILD_DIR)/test_integer.o
#
# The object file containing the code used for debugging purposes.
TEST_TEST_INTEGER_DEBUG_OBJ = $(TEST_BUILD_DIR)/test_integer.debug.o

# TEST_STRING
#############
# The source code for the test_string part of the library.
TEST_TEST_STRING_SRC = $(SRC_DIR)/test/test_string.c
#
# The object file containing the code for test_string part of the test library.
TEST_TEST_STRING_OBJ = $(TEST_BUILD_DIR)/test_string.o
#
# The object file containing the code used for debugging purposes.
TEST_TEST_STRING_DEBUG_OBJ = $(TEST_BUILD_DIR)/test_string.debug.o

# TEST_HEADER
#############
# The source code for the test_header part of the library.
TEST_TEST_HEADER_SRC = $(SRC_DIR)/test/test_header.c
#
# The object file containing the code for test_header part of the test library.
TEST_TEST_HEADER_OBJ = $(TEST_BUILD_DIR)/test_header.o
#
# The object file containing the code used for debugging purposes.
TEST_TEST_HEADER_DEBUG_OBJ = $(TEST_BUILD_DIR)/test_header.debug.o

# TEST
######
# The object files for the test library.
TEST_OBJ = $(TEST_TEST_INTEGER_OBJ) $(TEST_TEST_STRING_OBJ) $(TEST_TEST_HEADER_OBJ)
TEST_DEBUG_OBJ = $(TEST_TEST_INTEGER_DEBUG_OBJ) $(TEST_TEST_STRING_DEBUG_OBJ) $(TEST_TEST_HEADER_DEBUG_OBJ)

# TO CLEAN
##########
# Used for the global clean rule.
TO_CLEAN += $(TEST_OBJ) $(TEST_DEBUG_OBJ)


################################### SPECIAL ####################################

# The special rule modifiers (.PHONY etc...) go here

#################################### RULES #####################################

$(TEST_BUILD_DIR):
	mkdir -p $(TEST_BUILD_DIR)

# RELEASE
#########
$(TEST_TEST_INTEGER_OBJ): $(TEST_TEST_INTEGER_SRC) $(TEST_TEST_INTEGER_HEAD) | $(TEST_BUILD_DIR)
	$(CC) $(C_LIB_OBJ_FLAGS) -c -o $(TEST_TEST_INTEGER_OBJ) $(TEST_TEST_INTEGER_SRC)

$(TEST_TEST_STRING_OBJ): $(TEST_TEST_STRING_SRC) $(TEST_TEST_STRING_HEAD) | $(TEST_BUILD_DIR)
	$(CC) $(C_LIB_OBJ_FLAGS) -c -o $(TEST_TEST_STRING_OBJ) $(TEST_TEST_STRING_SRC)

$(TEST_TEST_HEADER_OBJ): $(TEST_TEST_HEADER_SRC) $(TEST_TEST_HEADER_HEAD) | $(TEST_BUILD_DIR)
	$(CC) $(C_LIB_OBJ_FLAGS) -c -o $(TEST_TEST_HEADER_OBJ) $(TEST_TEST_HEADER_SRC)

# DEBUG
#######
$(TEST_TEST_INTEGER_DEBUG_OBJ): $(TEST_TEST_INTEGER_SRC) $(TEST_TEST_INTEGER_HEAD) | $(TEST_BUILD_DIR)
	$(CC) $(C_LIB_OBJ_FLAGS) $(DEBUG_FLAGS) -c -o $(TEST_TEST_INTEGER_DEBUG_OBJ) $(TEST_TEST_INTEGER_SRC)

$(TEST_TEST_STRING_DEBUG_OBJ): $(TEST_TEST_STRING_SRC) $(TEST_TEST_STRING_HEAD) | $(TEST_BUILD_DIR)
	$(CC) $(C_LIB_OBJ_FLAGS) $(DEBUG_FLAGS) -c -o $(TEST_TEST_STRING_DEBUG_OBJ) $(TEST_TEST_STRING_SRC)

$(TEST_TEST_HEADER_DEBUG_OBJ): $(TEST_TEST_HEADER_SRC) $(TEST_TEST_HEADER_HEAD) | $(TEST_BUILD_DIR)
	$(CC) $(C_LIB_OBJ_FLAGS) $(DEBUG_FLAGS) -c -o $(TEST_TEST_HEADER_DEBUG_OBJ) $(TEST_TEST_HEADER_SRC)

##################################### EOF ######################################
