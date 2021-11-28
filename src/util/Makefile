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

# The build directory for this part of the library.
UTIL_BUILD_DIR = $(BUILD_DIR)/util

# BASE
######
# The source code for the base part of the library.
UTIL_BASE_SRC = $(SRC_DIR)/util/base.c
#
# The object file containing the code for base part of the util library.
UTIL_BASE_OBJ = $(UTIL_BUILD_DIR)/base.o
#
# The object file containing the code used for debugging purposes.
UTIL_BASE_DEBUG_OBJ = $(UTIL_BUILD_DIR)/base.debug.o

# DATE_NOW
##########
# The source code for the date_now part of the library.
UTIL_DATE_NOW_SRC = $(SRC_DIR)/util/date_now.c
#
# The object file containing the code for date_now part of the util library.
UTIL_DATE_NOW_OBJ = $(UTIL_BUILD_DIR)/date_now.o
#
# The object file containing the code used for debugging purposes.
UTIL_DATE_NOW_DEBUG_OBJ = $(UTIL_BUILD_DIR)/date_now.debug.o

# LIST
######
# The source code for the list part of the library.
UTIL_LIST_SRC = $(SRC_DIR)/util/list.c
#
# The object file containing the code for list part of the util library.
UTIL_LIST_OBJ = $(UTIL_BUILD_DIR)/list.o
#
# The object file containing the code used for debugging purposes.
UTIL_LIST_DEBUG_OBJ = $(UTIL_BUILD_DIR)/list.debug.o

# LOG
#####
# The source code for the log part of the library.
UTIL_LOG_SRC = $(SRC_DIR)/util/log.c
#
# The object file containing the code for log part of the util library.
UTIL_LOG_OBJ = $(UTIL_BUILD_DIR)/log.o
#
# The object file containing the code used for debugging purposes.
UTIL_LOG_DEBUG_OBJ = $(UTIL_BUILD_DIR)/log.debug.o

# UTIL
######
# The object files for the util library.
UTIL_OBJ = $(UTIL_BASE_OBJ) $(UTIL_DATE_NOW_OBJ) $(UTIL_LIST_OBJ) $(UTIL_LOG_OBJ)
UTIL_DEBUG_OBJ = $(UTIL_BASE_DEBUG_OBJ) $(UTIL_DATE_NOW_DEBUG_OBJ) $(UTIL_LIST_DEBUG_OBJ) $(UTIL_LOG_DEBUG_OBJ)

# TO CLEAN
##########
# Used for the global clean rule.
TO_CLEAN += $(UTIL_OBJ) $(UTIL_DEBUG_OBJ)

################################### SPECIAL ####################################

# The special rule modifiers (.PHONY etc...) go here

#################################### RULES #####################################

$(UTIL_BUILD_DIR):
	mkdir -p $(UTIL_BUILD_DIR)

# RELEASE
#########
$(UTIL_BASE_OBJ): $(UTIL_BASE_SRC) $(UTIL_BASE_HEAD) | $(UTIL_BUILD_DIR)
	$(CC) $(C_LIB_OBJ_FLAGS) -c -o $(UTIL_BASE_OBJ) $(UTIL_BASE_SRC)

$(UTIL_DATE_NOW_OBJ): $(UTIL_DATE_NOW_SRC) $(UTIL_DATE_NOW_HEAD) | $(UTIL_BUILD_DIR)
	$(CC) $(C_LIB_OBJ_FLAGS) -c -o $(UTIL_DATE_NOW_OBJ) $(UTIL_DATE_NOW_SRC)

$(UTIL_LIST_OBJ): $(UTIL_LIST_SRC) $(UTIL_LIST_HEAD) | $(UTIL_BUILD_DIR)
	$(CC) $(C_LIB_OBJ_FLAGS) -c -o $(UTIL_LIST_OBJ) $(UTIL_LIST_SRC)

$(UTIL_LOG_OBJ): $(UTIL_LOG_SRC) $(UTIL_LOG_HEAD) | $(UTIL_BUILD_DIR)
	$(CC) $(C_LIB_OBJ_FLAGS) -c -o $(UTIL_LOG_OBJ) $(UTIL_LOG_SRC)

# DEBUG
#######
$(UTIL_BASE_DEBUG_OBJ): $(UTIL_BASE_SRC) $(UTIL_BASE_HEAD) | $(UTIL_BUILD_DIR)
	$(CC) $(C_LIB_OBJ_FLAGS) $(DEBUG_FLAGS) -c -o $(UTIL_BASE_DEBUG_OBJ) $(UTIL_BASE_SRC)

$(UTIL_DATE_NOW_DEBUG_OBJ): $(UTIL_DATE_NOW_SRC) $(UTIL_DATE_NOW_HEAD) | $(UTIL_BUILD_DIR)
	$(CC) $(C_LIB_OBJ_FLAGS) $(DEBUG_FLAGS) -c -o $(UTIL_DATE_NOW_DEBUG_OBJ) $(UTIL_DATE_NOW_SRC)

$(UTIL_LIST_DEBUG_OBJ): $(UTIL_LIST_SRC) $(UTIL_LIST_HEAD) | $(UTIL_BUILD_DIR)
	$(CC) $(C_LIB_OBJ_FLAGS) $(DEBUG_FLAGS) -c -o $(UTIL_LIST_DEBUG_OBJ) $(UTIL_LIST_SRC)

$(UTIL_LOG_DEBUG_OBJ): $(UTIL_LOG_SRC) $(UTIL_LOG_HEAD) | $(UTIL_BUILD_DIR)
	$(CC) $(C_LIB_OBJ_FLAGS) $(DEBUG_FLAGS) -c -o $(UTIL_LOG_DEBUG_OBJ) $(UTIL_LOG_SRC)

##################################### EOF ######################################
