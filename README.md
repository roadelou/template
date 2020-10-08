# TEMPLATE

__template__ is a small C executable to build templated files from the command line.

## Usage

The syntax of __template__ is

```
template [filenames ...]
```

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

## Template files

__template__ uses printf-style format files to build the templated files. For a file with the extension _bar_, template will try to find the template file `$HOME/.config/roadelou_template/bar.template`. If this file cannot be found, then `$HOME/.config/roadelou_template/txt.template` will be used instead.

When writing the template files, __%1$s__ will refer to the author metadata, __%2$s__ will be the contact and __%3$s__ will be the date of creation.

> User-defined printf format are dangerous and prone to breaking, in the future I will reimplment a safer wrapper to avoid such issues.

### METADATA

Field | Value
--- | ---
:pencil: Contributors | roadelou
:email: Contacts |
:date: Creation Date | 2020-09-27
:bulb: Language | Markdown Document

### EOF
