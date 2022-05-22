################################### METADATA ###################################

# Contributors: roadelou
# Contacts: 
# Creation Date: 2021-11-14
# Language: Makefile
# Make version: GNU Make 4.3

################################### ALIASES ####################################

# The source files for the tests.
TEST_UTIL_SRC = $(wildcard $(TEST_DIR)/util/*.c)
#
# The elf files for the tests.
TEST_UTIL_ELF = $(patsubst $(TEST_DIR)/util/%.c,$(TEST_BIN_DIR)/%.elf,$(TEST_UTIL_SRC))

# REGISTERING TEST
##################
# Registering the tests for the global Makefile.
TEST_LIST += $(TEST_UTIL_ELF)

################################### SPECIAL ####################################

# The special rule modifiers (.PHONY etc...) go here

#################################### RULES #####################################

# Note that the tests are always compiled againts the 'DEBUG' version of the
# code.
#
# COMPILING
###########
#
# Generic rule to build the object file from the test source.
$(TEST_BIN_DIR)/%.o: $(TEST_DIR)/util/%.c | $(TEST_BIN_DIR)
	$(CC) $(C_FLAGS) -c -o $@ $<

#
# Generic rule to build the test elf from its object file.
$(TEST_BIN_DIR)/%.elf: $(TEST_BIN_DIR)/%.o $(TEMPLATE_LIB) $(TEST_LIB) | $(TEST_BIN_DIR)
	$(CC) $(C_TEST_ELF_FLAGS) -o $@ $<

##################################### EOF ######################################
