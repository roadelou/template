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

#
# The directory where this part of the codebase will be built.
TEST_BUILD_DIR = $(BUILD_DIR)/test
#
# The directory containing the source code for this part of the codebase.
TEST_SRC_DIR = $(SRC_DIR)/test
#
# The source files for the tests.
TEST_SRC = $(wildcard $(TEST_SRC_DIR)/*.c)
#
# The object files built for the release.
TEST_OBJ = $(patsubst $(TEST_SRC_DIR)/%.c,$(TEST_BUILD_DIR)/%.o,$(TEST_SRC))
#
# NOTE
# ====
# We don't add the test objects to the library, as they will instead be linked
# against it in the tests.

################################### SPECIAL ####################################

# The special rule modifiers (.PHONY etc...) go here

#################################### RULES #####################################

$(TEST_BUILD_DIR):
	mkdir -p $(TEST_BUILD_DIR)

# RELEASE
#########
$(TEST_BUILD_DIR)/%.o: $(TEST_SRC_DIR)/%.c $(TEST_HEAD) | $(TEST_BUILD_DIR)
	$(CC) $(C_LIB_OBJ_FLAGS) -c -o $@ $<

##################################### EOF ######################################
