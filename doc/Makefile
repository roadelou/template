################################### METADATA ###################################

# Contributors: roadelou
# Contacts: 
# Creation Date: 2021-11-25
# Language: Makefile
# Make version: GNU Make 4.3

################################### ALIASES ####################################

# The source for the man pages.
TEMPLATE_DOC_SRC = $(DOC_DIR)/TEMPLATE.md
TEMPLATE_RUN_DOC_SRC = $(DOC_DIR)/TEMPLATE-RUN.md
#
# The directory where the documentation is built.
DOC_BUILD_DIR = $(BUILD_DIR)/doc
#
# The man pages produced by pandoc.
TEMPLATE_MAN_SRC = $(DOC_BUILD_DIR)/template.1
TEMPLATE_RUN_MAN_SRC = $(DOC_BUILD_DIR)/template-run.1
#
# The compressed man pages.
TEMPLATE_MAN_ZIP = $(DOC_BUILD_DIR)/template.1.gz
TEMPLATE_RUN_MAN_ZIP = $(DOC_BUILD_DIR)/template-run.1.gz

# Adding the documentation to the dedicate variable.
MAN_DOC += $(TEMPLATE_MAN_ZIP) $(TEMPLATE_RUN_MAN_ZIP)
TO_CLEAN += $(MAN_DOC)

################################### SPECIAL ####################################

# The special rule modifiers (.PHONY etc...) go here

#################################### RULES #####################################

$(DOC_BUILD_DIR): | $(BUILD_DIR)
	mkdir -p $(DOC_BUILD_DIR)

$(TEMPLATE_MAN_ZIP): $(TEMPLATE_DOC_SRC) | $(DOC_BUILD_DIR)
	pandoc $(TEMPLATE_DOC_SRC) -s -t man -o $(TEMPLATE_MAN_SRC)
	gzip $(TEMPLATE_MAN_SRC)

$(TEMPLATE_RUN_MAN_ZIP): $(TEMPLATE_RUN_DOC_SRC) | $(DOC_BUILD_DIR)
	pandoc $(TEMPLATE_RUN_DOC_SRC) -s -t man -o $(TEMPLATE_RUN_MAN_SRC)
	gzip $(TEMPLATE_RUN_MAN_SRC)

##################################### EOF ######################################
