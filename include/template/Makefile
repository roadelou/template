################################### METADATA ###################################

# Contributors: roadelou
# Contacts: 
# Creation Date: 2021-11-13
# Language: Makefile
# Make version: GNU Make 4.3

################################### ALIASES ####################################

# Defining the directory for each part of the template library.
UTIL_HEAD_DIR = $(HEAD_DIR)/template/util
EXTENSION_HEAD_DIR = $(HEAD_DIR)/template/extension
FORMAT_HEAD_DIR = $(HEAD_DIR)/template/format
#
# Defining the headers for each library. We can deduce it from the name of the
# corresponding directory.
TEMPLATE_UTIL_HEAD = $(UTIL_HEAD_DIR).h
TEMPLATE_EXTENSION_HEAD = $(EXTENSION_HEAD_DIR).h
TEMPLATE_FORMAT_HEAD = $(FORMAT_HEAD_DIR).h
#
# Sourcing the corresponding directory for all of the contributing headers.
include $(UTIL_HEAD_DIR)/Makefile
include $(EXTENSION_HEAD_DIR)/Makefile
include $(FORMAT_HEAD_DIR)/Makefile

################################### SPECIAL ####################################

# The special rule modifiers (.PHONY etc...) go here

#################################### RULES #####################################

# The rules for your Makefile go here

##################################### EOF ######################################
