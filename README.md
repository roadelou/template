# TEMPLATE

`template` is a collection of tools used to create templated file from the command line.

## Usage

There are currently 2 executables provided by this project:

 - [template](doc/TEMPLATE.md) which is used to create files from templates chosen based on the extension.
 - [template-run](doc/TEMPLATE-RUN.md) which is used to print the result of the execution of a provided template file.

## Examples

`template example.c` will create a C source file based on the template in the `/etc/roadelou_template` directory, if any.

`template-run example.template` will print the result of the execution of `example.template` to stdout.

### METADATA

Field | Value
--- | ---
:pencil: Contributors | roadelou
:email: Contacts | 
:date: Creation Date | 2021-11-20
:bulb: Language | Markdown Document
:page: Repository | git@github.com:roadelou/template

### EOF
