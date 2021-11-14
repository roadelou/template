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

# EXEC
######
# The Makefile used to create the executables.
EXEC_MAKEFILE = $(SRC_DIR)/exec/Makefile

# EXTENSION
###########
# The Makefile used to create the extension library.
EXTENSION_MAKEFILE = $(SRC_DIR)/extension/Makefile

# FORMAT
########
# The Makefile used to create the format library.
FORMAT_MAKEFILE = $(SRC_DIR)/format/Makefile

# UTIL
######
# The Makefile used to create the util library.
UTIL_MAKEFILE = $(SRC_DIR)/util/Makefile

# TEST
######
# The Makefile used to create the test library.
TEST_MAKEFILE = $(SRC_DIR)/test/Makefile

#
# Including the Makefiles from the children directories to use their rules.
#
# NOTE
######
# The order of the inclusions is important, it corresponds to compilation
# dependancies.
include $(UTIL_MAKEFILE)
include $(EXTENSION_MAKEFILE)
include $(FORMAT_MAKEFILE)
include $(TEST_MAKEFILE)
include $(EXEC_MAKEFILE)

##################################### EOF ######################################
