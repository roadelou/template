################################### METADATA ###################################

# Contributors: roadelou
# Contacts: 
# Creation Date: 2020-10-09
# Language: Makefile

################################### ALIASES ####################################

# Root directory of the git repository
top = $(CURDIR)

# All source files
src = src/*.c

# Flag to include all headers
include = -I$(top)/include/

# Flag to trigger compiler warnings
warn = -Wall -pedantic

# The name of the compiled executable
outdir = build
out = $(outdir)/template.elf
# The location where the executable will be installed.
bindir = $(DESTDIR)/usr/bin

# All the preset template files.
templates = ./etc/*.template
# The location where the configuration format files will be stored.
config = $(DESTDIR)/etc/roadelou_template/

################################### SPECIAL ####################################

.PHONY: clean install uninstall

#################################### RULES #####################################

# The compilation flow here is rather straightforward.
$(out): $(src)
	mkdir -p $(outdir)
	$(CC) $(warn) $(include) $(src) -o $(out)

clean:
	rm -f $(out)

install: $(out) $(templates)
	mkdir -p $(bindir)
	cp $(out) $(bindir)/template
	# Also copying the format files to the expected location.
	mkdir -p $(config)
	cp $(templates) $(config)

uninstall:
	rm -f $(bindir)/template
	rm -rf $(config)

##################################### EOF ######################################
