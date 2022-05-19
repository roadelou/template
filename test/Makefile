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
#
# The directory where the log for the tests will be stored.
TEST_CSV_DIR = $(BUILD_DIR)/testing/csv
#
# The list of test executables, which will be populated in the leaf Makefiles.
TEST_LIST =
#
# The log file for the tests.
TEST_LOG = $(TEST_CSV_DIR)/log.csv

# This short macro is used to set the LD_LIBRARY_PATH to use the compiled
# library for debugging purposes.
SET_LD = LD_LIBRARY_PATH=$(LIB_BUILD_DIR):$(LD_LIBRARY_PATH)

# Sourcing all of the unit tests for the project.
include $(TEST_DIR)/util/Makefile
include $(TEST_DIR)/extension/Makefile

#
# TO CLEAN
##########
# The CSV files  and the test programs should be deleted on clean.
TO_CLEAN += $(TEST_LIST)

################################### SPECIAL ####################################

# The special rule modifiers (.PHONY etc...) go here
.PHONY: $(TEST_CSV)

#################################### RULES #####################################

# Running the tests.
test: $(TEST_LIST) | $(TEST_CSV_DIR)
	@# Printing the header for the tests.
	@echo "STATUS;FILE;FUNCTION;LINE;EXPECTED;COMPUTED" | tee $(TEST_LOG)
	@$(foreach TEST,$(TEST_LIST),$(SET_LD) $(TEST) | tee -a $(TEST_LOG);)

$(TEST_BIN_DIR):
	mkdir -p $(TEST_BIN_DIR)

##################################### EOF ######################################
