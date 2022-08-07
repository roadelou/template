# TEMPLATE

`template` is a collection of tools used to create templated files from the command line.

## Usage

There are currently 2 executables provided by this project:

 - [template](doc/template.md) which is used to create files from templates chosen based on the extension.
 - [template-run](doc/template-run.md) which is used to print the result of the execution of a provided template file.

Rudimentary man pages are also provided, check `man 1 template` and `man 1 template-run`.

The package will also install the shared library *libtemplate.so* used by the two executable, and store the corresponding header files on the system.

## Examples

`template example.c` will create a C source file based on the template in the `/etc/roadelou_template` directory, if any.

`template-run example.template` will print the result of the execution of `example.template` to stdout.

### METADATA

Field | Value
--- | ---
Contributors | roadelou
Contacts | 
Creation Date | 2021-11-20
Language | Markdown Document
Repository | git@github.com:roadelou/template

### EOF
