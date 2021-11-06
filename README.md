# TEMPLATE

__template__ is a small C executable to build templated files from the command line.

## Usage

The syntax of __template__ is

```
template [options] [filenames ...]
```

- To create a template file called foo.bar, use `template foo.bar`. Several files can be provided at once and they will all be created.

- __template__ will use the extension of the provided file to determine which template should be applied.

### Options

__template__ uses [getopt](https://www.gnu.org/software/libc/manual/html_node/Getopt.html) to parse its command line options. The recognized options are:

- `-a, --author <author>` to override the environment "author" value with the provided one (see the [Metadata](README.md#Metadata) for details about the author value).
- `-c, --contact <contact>` to override the environment "contact" value with the provided one (see the [Metadata](README.md#Metadata) for details about the contact value).
- `-v, --verbose` to raise the verbosity of the tool and see all the messages.
- `-q, --quiet` to lower the verbosity of the tool and only see error messages.
- `-o, --old` to use the old matching algorithm that only matches whole extensions.
- `-n, --new` to use the new hierarchical matching algorithm.
- `-s, --static` to use the older templating style described in the **Static Format** section.
- `-d, --dynamic` to use the newer templating style with shell subcommands. This is the default and is described in the **Dynamic Format** section.
- `-l, --license` to print license information and exit.
- `-h, --help` to print help and exit.

## Metadata

When creating a template file, __template__ will fill in some dynamically deduced contextual information.

- Author: Can be set via the environment variable __TEMPLATE\_USER__, else defaults to the __USER__ variable.
- Contact: Can be set via the environment variable __TEMPLATE\_CONTACT__, else defaults to an empty string.
- Date: Reported by the OS.

It is also common to find a __Language__ field in the created files, but it is in fact part of the template file and not dynamically deduced by __template__.

## Template files

__template__ uses printf-style format files to build the templated files. For a file with the extension _bar_, template will try to find the template file `$HOME/.config/roadelou_template/bar.template`. If this file cannot be found, then `$HOME/.config/roadelou_template/txt.template` will be used instead.

The way **template** searches the extension file is non-trivial, but allows recognition of hierachies of extension. So a file like `foo.bar.txt` can use the template `txt.bar.template` even if the more generic `txt.template` also exists. This is usefull for templates with a license specific headers.

### Static Format

 - When writing the template files with the older static format, __%1__ will refer to the author metadata, __%2__ will be the contact and __%3__ will be the date of creation.
 - __%%__ can be used as an escape and will print a single character '%'.
 - Any other occurence of '%' which doesn't fit into the previous definitions will simply be pasted litteraly to the created file, without formatting.

### Dynamic Format

 - The newer dynamic format takes advantage of shell scripting to include the output of commands in your created file. The basic syntax for a subcommand is `%$ [...] $` where `$` can be any ASCII character. This is similar to the way the `sed` command handles its `/` for instance.
 - For instance, `%/echo rouge/` would yield `rouge`.
 - `template` will warn about incomplete or malformed format specifiers and should proceed without crashing.

## Verbosity

**template** prints messages with three levels of importance. Whether a message os printed or not depends on the log level (i.e. the verbosity of the tool) during the execution. The three importance levels are explained in the table below.

Importance Level | Printed If | Color | Meaning
-----------------|------------|-------|--------
INFO\_MSG | `-v` or `--verbose` is used | White | No problem occured, no user intervention is needed
WARNING\_MSG | `-q` or `--quiet` is **not** used | Yellow | A recoverable problem occured, no user intervention is needed
ERROR\_MSG | *Always* | Red | A irrecoverable problem has occured, some user intervention is needed

Note that template isn't meant to crash even when an **ERROR\_MSG** is printed, in most cases **template** will just not create the expected file and move on.

### METADATA

Field | Value
--- | ---
Contributors | roadelou
Contacts |
Creation Date | 2020-09-27
Language | Markdown Document

### EOF
