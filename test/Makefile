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

# The directory where the test executables will be stored.
TEST_BIN_DIR = $(BUILD_DIR)/testing/bin

# The directory where the test results will be stored.
TEST_CSV_DIR = $(BUILD_DIR)/testing/csv

# The list of all the CSV files produced by all the tests.
TEST_CSV =

# Sourcing all of the unit tests for the project.
include $(TEST_DIR)/util/Makefile
include $(TEST_DIR)/extension/Makefile

################################### SPECIAL ####################################

# The special rule modifiers (.PHONY etc...) go here

#################################### RULES #####################################

$(TEST_BIN_DIR):
	mkdir -p $(TEST_BIN_DIR)

$(TEST_CSV_DIR):
	mkdir -p $(TEST_CSV_DIR)

##################################### EOF ######################################
