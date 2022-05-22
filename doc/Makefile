################################### METADATA ###################################

# Contributors: roadelou
# Contacts: 
# Creation Date: 2021-11-25
# Language: Makefile
# Make version: GNU Make 4.3

################################### ALIASES ####################################

# The source for the man pages.
DOC_LIST = $(wildcard $(DOC_DIR)/*.md)
#
# The directory where the documentation is built.
DOC_BUILD_DIR = $(BUILD_DIR)/doc
#
# The list of man pages built for distribution.
MAN_PAGE_LIST = $(patsubst $(DOC_DIR)%.md,$(DOC_BUILD_DIR)%.1.gz,$(DOC_LIST))

#
# The man pages shuld be deleted when `make clean` is called.
TO_CLEAN += $(MAN_PAGE_LIST)


################################### SPECIAL ####################################

#
# Phony rule to build every man page.
.PHONY: manpages

#################################### RULES #####################################

$(DOC_BUILD_DIR): | $(BUILD_DIR)
	mkdir -p $(DOC_BUILD_DIR)

#
# Pattern rule to build the raw man-page from the Markdown documentation.
$(DOC_BUILD_DIR)/%.1: $(DOC_DIR)/%.md
	pandoc $< -s -t man -o $@

#
# Pattern rule to compress an man page.
$(DOC_BUILD_DIR)/%.1.gz: $(DOC_BUILD_DIR)/%.1
	gzip $<

#
# PHONY rule to build every man page.
manpages: $(MAN_PAGE_LIST) | $(DOC_BUILD_DIR)
	echo $(MAN_PAGE_LIST)

##################################### EOF ######################################
