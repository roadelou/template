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

- `-a author` to override the environment "author" value with the provided one (see the [Metadata](README.md#Metadata) for details about the author value).
- `-c contact` to override the environment "contact" value with the provided one (see the [Metadata](README.md#Metadata) for details about the contact value).
- `-h` to print help and exit.

## Metadata

When creating a template file, __template__ will fill in some dynamically deduced contextual information.

- Author: Can be set via the environment variable __TEMPLATE\_USER__, else defaults to the __USER__ variable.
- Contact: Can be set via the environment variable __TEMPLATE\_CONTACT__, else defaults to an empty string.
- Date: Reported by the OS.

It is also common to find a __Language__ field in the created files, but it is in fact part of the template file and not dynamically deduced by __template__.

## Template files

__template__ uses printf-style format files to build the templated files. For a file with the extension _bar_, template will try to find the template file `$HOME/.config/roadelou_template/bar.template`. If this file cannot be found, then `$HOME/.config/roadelou_template/txt.template` will be used instead.

### Formatting syntax

 - When writing the template files, __%1__ will refer to the author metadata, __%2__ will be the contact and __%3__ will be the date of creation.
 - __%%__ can be used as an escape and will print a single character '%'.
 - Any other occurence of '%' which doesn't fit any of the previous definitions will simply be pasted litteraly to the created file, without formatting.

### METADATA

Field | Value
--- | ---
Contributors | roadelou
Contacts |
Creation Date | 2020-09-27
Language | Markdown Document

### EOF
