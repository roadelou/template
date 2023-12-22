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

# TEST ENVIRONMENT
##################
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
#
# The list of template files we can try the executable against.
ETC_LIST = $(wildcard etc/*.template)
#
# The directory where the vagrind resuts will be held.
TEST_VALGRIND_DIR = $(BUILD_DIR)/testing/valgrind
#
# The fix valgrind arguments for valgring.
VALGRIND_ARGS = --tool=memcheck --show-error-list=yes --leak-check=full --error-exitcode=1

# TEST ELFS
###########
#
# Flags used to compile the executables for the tests.
C_TEST_ELF_LINK_FLAGS = -L$(LIB_BUILD_DIR) -ltemplate -ltemplate_test

# This short macro is used to set the LD_LIBRARY_PATH to use the compiled
# library for debugging purposes.
SET_LD = LD_LIBRARY_PATH=$(LIB_BUILD_DIR):$(LD_LIBRARY_PATH)

# Sourcing all of the unit tests for the project.
include $(TEST_DIR)/util/Makefile
include $(TEST_DIR)/extension/Makefile
include $(TEST_DIR)/format/Makefile

#
# TO CLEAN
##########
# The CSV files and the test programs should be deleted on clean.
TO_CLEAN += $(TEST_LIST) $(TEST_LOG)

################################### SPECIAL ####################################

# The special rule modifiers (.PHONY etc...) go here
.PHONY: $(TEST_CSV) valgrind

#################################### RULES #####################################

# Running the tests.
tests: $(TEST_LIST) | $(TEST_CSV_DIR)
	@# Printing the header for the tests.
	@echo "STATUS;FILE;FUNCTION;LINE;EXPECTED;COMPUTED" | tee $(TEST_LOG)
	@$(foreach TEST,$(TEST_LIST),$(SET_LD) $(TEST) | tee -a $(TEST_LOG);)

# Testing the code against valgrind. Note that we use the
# $(VAR:PATTERN=REPLACEMENT) syntax here.
valgrind: elfs | $(TEST_VALGRIND_DIR)
	@$(foreach ETC_FILE,$(ETC_LIST),echo [valgrind] $(ETC_FILE); $(SET_LD) valgrind $(VALGRIND_ARGS) --log-file=$(TEST_VALGRIND_DIR)/$(notdir $(ETC_FILE)).log $(ELF_BUILD_DIR)/template-run.elf $(ETC_FILE) > /dev/null;)

# Generic rule to build the test elf from its object file.
$(TEST_BIN_DIR)/%.elf: $(TEST_BIN_DIR)/%.o $(TEMPLATE_LIB) $(TEST_LIB) | $(TEST_BIN_DIR)
	$(CC) $(C_FLAGS) -o $@ $< $(C_TEST_ELF_LINK_FLAGS)

$(TEST_CSV_DIR):
	mkdir -p $(TEST_CSV_DIR)

$(TEST_BIN_DIR):
	mkdir -p $(TEST_BIN_DIR)

$(TEST_VALGRIND_DIR):
	mkdir -p $(TEST_VALGRIND_DIR)

##################################### EOF ######################################
