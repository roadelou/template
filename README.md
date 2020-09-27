# TEMPLATE

__template__ is a small C executable to build templated files from the command line.

## Usage

The syntax of __template__ is

```
template [-h|--help] [filenames ...]
```

- To print the (short) help of template, use `template -h` or `template --help`.
- To create a template file called foo.bar, use `template foo.bar`. Several files can be provided at once and they will all be created.

__template__ will use the extension of the provided file to determine which template should be applied.

## Metadata

When creating a template file, __template__ will fill in some contextual information. These additional information are summed up in the table below.

Information | Where it comes from
----------- | -------------------
Contributor | Can be set via the environment variable __TEMPLATE\_USER__, else defaults to the __USER__ variable.
Contact | Can be set via the environment variable __TEMPLATE\_CONTACT__, else defaults to an empty string.
Date | Reported by the OS.
Language | Based on the file extension recognized by __template__.

## Bugs

__template__ does not use getopt inside because it wasn't worth it. This means that __template__ will print its help for all occurrences of `-h` or `--help` in its arguments. For instance, `template -h -h --help` would print the help three times.

### METADATA

Field | Value
--- | ---
:pencil: Contributors | roadelou
:email: Contacts |
:date: Creation Date | 2020-09-27
:bulb: Language | Markdown Document

### EOF
