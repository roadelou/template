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
EXEC_BUILD_DIR = $(BUILD_DIR)/exec
#
# The directory containing the source code for this part of the codebase.
EXEC_SRC_DIR = $(SRC_DIR)/exec
#
# The source files for the tests.
EXEC_SRC = $(wildcard $(EXEC_SRC_DIR)/*.c)
#
# The object files built for the release.
EXEC_OBJ = $(patsubst $(EXEC_SRC_DIR)/%.c,$(EXEC_BUILD_DIR)/%.o,$(EXEC_SRC))
#
# NOTE
# ====
# We don't add the executables to the list of objects compiled in the library,
# it will instead be linked against it.

################################### SPECIAL ####################################

# The special rule modifiers (.PHONY etc...) go here

#################################### RULES #####################################

$(EXEC_BUILD_DIR):
	mkdir -p $(EXEC_BUILD_DIR)

# RELEASE
#########
$(EXEC_BUILD_DIR)/%.o: $(EXEC_SRC_DIR)/%.c $(EXEC_HEAD) | $(EXEC_BUILD_DIR)
	$(CC) $(C_LIB_OBJ_FLAGS) -c -o $@ $<

##################################### EOF ######################################
