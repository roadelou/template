Name: template
Version: 1.12
Release: 1%{?dist}
Summary: template is a small C executable to build templated files from the command line

License: GPLv3
URL: https://github.com/roadelou/template

BuildRequires: gcc
BuildRequires: make
BuildRequires: pandoc
BuildRequires: gzip

# Needed for the documentation.
Requires: man-db

%description
template is a small C executable to build templated files from the command line.

%prep
# No preparation is needed here, we are already inside of the source code.

%build
# We just call `make [all]` to compile the executable.
make %{?_smp_mflags}

%install
# `make install` is used to install the executable.
%make_install

%files
# This section is used to specify which files this package creates.
#
# This is the executable itself, stored in /usr/bin
/usr/bin/template
#
# The second executable for running templates directly
/usr/bin/template-run
#
# The default template files are stored in /etc/roadelou_template
/etc/roadelou_template/*.template
#
# The man pages should be installed in the end.
%{_mandir}/man1/template.1*
%{_mandir}/man1/template-run.1*
#
# The shared library used by the template executables.
/usr/lib64/libtemplate.so
#
# The header files for the template library.
/usr/include/template.h
/usr/include/template/*
