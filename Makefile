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

.PHONY: clean install

# The compilation flow here is rather straight forward.
$(out): $(src)
	mkdir -p $(outdir)
	clang $(warn) $(include) $(src) -o $(out)

clean:
	rm -f $(out)

install: $(out)
	cp $(out) ~/.local/bin/template
