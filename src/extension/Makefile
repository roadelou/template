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
EXTENSION_BUILD_DIR = $(BUILD_DIR)/extension
#
# The directory containing the source code for this part of the codebase.
EXTENSION_SRC_DIR = $(SRC_DIR)/extension
#
# The source files for the tests.
EXTENSION_SRC = $(wildcard $(EXTENSION_SRC_DIR)/*.c)
#
# The object files built for the release.
EXTENSION_OBJ = $(patsubst $(EXTENSION_SRC_DIR)/%.c,$(EXTENSION_BUILD_DIR)/%.o,$(EXTENSION_SRC))
#
# We add the objects from this directory to the list of compiled objects.
OBJ_LIST += $(EXTENSION_OBJ)

################################### SPECIAL ####################################

# The special rule modifiers (.PHONY etc...) go here

#################################### RULES #####################################

$(EXTENSION_BUILD_DIR):
	mkdir -p $(EXTENSION_BUILD_DIR)

# RELEASE
#########
$(EXTENSION_BUILD_DIR)/%.o: $(EXTENSION_SRC_DIR)/%.c $(EXTENSION_HEAD) | $(EXTENSION_BUILD_DIR)
	$(CC) $(C_LIB_OBJ_FLAGS) -c -o $@ $<

##################################### EOF ######################################
