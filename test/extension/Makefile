################################### METADATA ###################################

# Contributors: roadelou
# Contacts: 
# Creation Date: 2021-11-14
# Language: Makefile
# Make version: GNU Make 4.3

################################### ALIASES ####################################

# The source files for the tests.
TEST_EXTENSION_SRC = $(wildcard $(TEST_DIR)/extension/*.c)
#
# The elf files for the tests.
TEST_EXTENSION_ELF = $(patsubst $(TEST_DIR)/extension/%.c,$(TEST_BIN_DIR)/%.elf,$(TEST_EXTENSION_SRC))

# REGISTERING TEST
##################
# Registering the tests for the global Makefile.
TEST_LIST += $(TEST_EXTENSION_ELF)

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
$(TEST_BIN_DIR)/%.o: $(TEST_DIR)/extension/%.c | $(TEST_BIN_DIR)
	$(CC) $(C_FLAGS) -c -o $@ $<

##################################### EOF ######################################
