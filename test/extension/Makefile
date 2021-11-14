################################### METADATA ###################################

# Contributors: roadelou
# Contacts: 
# Creation Date: 2021-11-14
# Language: Makefile
# Make version: GNU Make 4.3

################################### ALIASES ####################################

# EXTENSION_MATCH
######
# The source code for the extension_match tests.
TEST_EXTENSION_EXTENSION_MATCH_SRC = $(TEST_DIR)/extension/extension_match.c
#
# The object file containing the code for the extension_match test.
TEST_EXTENSION_EXTENSION_MATCH_OBJ = $(TEST_BIN_DIR)/extension_match.o
#
# The linked executable for the extension_match test.
TEST_EXTENSION_EXTENSION_MATCH_ELF = $(TEST_BIN_DIR)/extension_match.elf
#
# The csv file containing the results of the extension_match test.
TEST_EXTENSION_EXTENSION_MATCH_CSV = $(TEST_CSV_DIR)/extension_match.csv

# EXTENSION
######
# The object files for the tests.
TEST_EXTENSION_OBJ = $(TEST_EXTENSION_EXTENSION_MATCH_OBJ)
#
# The execuatables themselves.
TEST_EXTENSION_ELF = $(TEST_EXTENSION_EXTENSION_MATCH_ELF)
#
# The CSVs containing the results of the test.
TEST_EXTENSION_CSV = $(TEST_EXTENSION_EXTENSION_MATCH_CSV) $(TEST_EXTENSION_LIST_CSV)

# TO CLEAN
##########
# Used for the global clean rule.
TO_CLEAN += $(TEST_EXTENSION_OBJ) $(TEST_EXTENSION_ELF) $(TEST_EXTENSION_CSV)

# REGISTERING TEST
##################
# Registering the tests for the global Makefile.
TEST_CSV += $(TEST_EXTENSION_CSV)

################################### SPECIAL ####################################

# The special rule modifiers (.PHONY etc...) go here

#################################### RULES #####################################

# Note that the tests are always compiled againts the 'RELEASE' version of the
# code.
#
# COMPLING
##########
$(TEST_EXTENSION_EXTENSION_MATCH_OBJ): $(TEST_EXTENSION_EXTENSION_MATCH_SRC) | $(TEST_BIN_DIR)
	$(CC) $(C_FLAGS) -c -o $(TEST_EXTENSION_EXTENSION_MATCH_OBJ) $(TEST_EXTENSION_EXTENSION_MATCH_SRC)

$(TEST_EXTENSION_EXTENSION_MATCH_ELF): $(TEST_EXTENSION_EXTENSION_MATCH_OBJ) $(UTIL_OBJ) $(TEST_OBJ) $(EXTENSION_OBJ) | $(TEST_BIN_DIR)
	$(CC) $(C_FLAGS) -o $(TEST_EXTENSION_EXTENSION_MATCH_ELF) $(TEST_EXTENSION_EXTENSION_MATCH_OBJ) $(UTIL_OBJ) $(TEST_OBJ) $(EXTENSION_OBJ)

# RUNNING TESTS
###############
$(TEST_EXTENSION_EXTENSION_MATCH_CSV): $(TEST_EXTENSION_EXTENSION_MATCH_ELF) | $(TEST_CSV_DIR)
	$(TEST_EXTENSION_EXTENSION_MATCH_ELF) | tee $(TEST_EXTENSION_EXTENSION_MATCH_CSV)

##################################### EOF ######################################
