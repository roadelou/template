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

# All the preset template files.
templates = ./etc/*.template
# The location where the configuration format files will be stored.
config = ~/.config/roadelou_template/

.PHONY: clean install uninstall

# The compilation flow here is rather straight forward.
$(out): $(src)
	mkdir -p $(outdir)
	clang $(warn) $(include) $(src) -o $(out)

clean:
	rm -f $(out)

install: $(out) $(templates)
	cp $(out) ~/.local/bin/template
	# Also copying the format files to the expected location.
	mkdir -p $(config)
	cp $(templates) $(config)

uninstall:
	rm -f ~/.local/bin/template
	rm -rf $(config)
