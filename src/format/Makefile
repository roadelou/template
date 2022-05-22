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
FORMAT_BUILD_DIR = $(BUILD_DIR)/format
#
# The directory containing the source code for this part of the codebase.
FORMAT_SRC_DIR = $(SRC_DIR)/format
#
# The source files for the tests.
FORMAT_SRC = $(wildcard $(FORMAT_SRC_DIR)/*.c)
#
# The object files built for the release.
FORMAT_OBJ = $(patsubst $(FORMAT_SRC_DIR)/%.c,$(FORMAT_BUILD_DIR)/%.o,$(FORMAT_SRC))
#
# We add the objects from this directory to the list of compiled objects.
OBJ_LIST += $(FORMAT_OBJ)

################################### SPECIAL ####################################

# The special rule modifiers (.PHONY etc...) go here

#################################### RULES #####################################

$(FORMAT_BUILD_DIR):
	mkdir -p $(FORMAT_BUILD_DIR)

# RELEASE
#########
$(FORMAT_BUILD_DIR)/%.o: $(FORMAT_SRC_DIR)/%.c $(FORMAT_HEAD) | $(FORMAT_BUILD_DIR)
	$(CC) $(C_LIB_OBJ_FLAGS) -c -o $@ $<

##################################### EOF ######################################
