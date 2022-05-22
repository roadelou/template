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
UTIL_BUILD_DIR = $(BUILD_DIR)/util
#
# The directory containing the source code for this part of the codebase.
UTIL_SRC_DIR = $(SRC_DIR)/util
#
# The source files for the tests.
UTIL_SRC = $(wildcard $(UTIL_SRC_DIR)/*.c)
#
# The object files built for the release.
UTIL_OBJ = $(patsubst $(UTIL_SRC_DIR)/%.c,$(UTIL_BUILD_DIR)/%.o,$(UTIL_SRC))
#
# We add the objects from this directory to the list of compiled objects.
OBJ_LIST += $(UTIL_OBJ)

################################### SPECIAL ####################################

# The special rule modifiers (.PHONY etc...) go here

#################################### RULES #####################################

$(UTIL_BUILD_DIR):
	mkdir -p $(UTIL_BUILD_DIR)

# RELEASE
#########
$(UTIL_BUILD_DIR)/%.o: $(UTIL_SRC_DIR)/%.c $(UTIL_HEAD) | $(UTIL_BUILD_DIR)
	$(CC) $(C_LIB_OBJ_FLAGS) -c -o $@ $<

##################################### EOF ######################################
