################################### METADATA ###################################

# Contributors: roadelou
# Contacts: 
# Creation Date: 2021-11-14
# Language: Makefile
# Make version: GNU Make 4.3

################################### ALIASES ####################################

# BASE
######
# The source code for the base tests.
TEST_UTIL_BASE_SRC = $(TEST_DIR)/util/base.c
#
# The object file containing the code for the base test.
TEST_UTIL_BASE_OBJ = $(TEST_BIN_DIR)/base.o
#
# The linked executable for the base test.
TEST_UTIL_BASE_ELF = $(TEST_BIN_DIR)/base.elf
#
# The csv file containing the results of the base test.
TEST_UTIL_BASE_CSV = $(TEST_CSV_DIR)/base.csv

# UTIL
######
# The object files for the tests.
TEST_UTIL_OBJ = $(TEST_UTIL_BASE_OBJ)
#
# The execuatables themselves.
TEST_UTIL_ELF = $(TEST_UTIL_BASE_ELF)
#
# The CSVs containing the results of the test.
TEST_UTIL_CSV = $(TEST_UTIL_BASE_CSV)

# TO CLEAN
##########
# Used for the global clean rule.
TO_CLEAN += $(TEST_UTIL_OBJ) $(TEST_UTIL_ELF) $(TEST_UTIL_CSV)

# REGISTERING TEST
##################
# Registering the tests for the global Makefile.
TEST_CSV += $(TEST_UTIL_CSV)

################################### SPECIAL ####################################

# The special rule modifiers (.PHONY etc...) go here

#################################### RULES #####################################

#
# Note that the tests are always compiled againts the 'RELEASE' version of the
# code.
#
# COMPLING
##########
$(TEST_UTIL_BASE_OBJ): $(TEST_UTIL_BASE_SRC) | $(TEST_BIN_DIR)
	$(CC) $(C_FLAGS) -c -o $(TEST_UTIL_BASE_OBJ) $(TEST_UTIL_BASE_SRC)

$(TEST_UTIL_BASE_ELF): $(TEST_UTIL_BASE_OBJ) $(TEST_OBJ) $(UTIL_DEBUG_OBJ) | $(TEST_BIN_DIR)
	$(CC) $(C_FLAGS) -o $(TEST_UTIL_BASE_ELF) $(TEST_UTIL_BASE_OBJ) $(TEST_OBJ) $(UTIL_DEBUG_OBJ)

#
# RUNNING TESTS
###############
$(TEST_UTIL_BASE_CSV): $(TEST_UTIL_BASE_ELF) | $(TEST_CSV_DIR)
	$(TEST_UTIL_BASE_ELF) | tee $(TEST_UTIL_BASE_CSV)

##################################### EOF ######################################
