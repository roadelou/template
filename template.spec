Name: template
Version: 1.7
Release: 1%{?dist}
Summary: template is a small C executable to build templated files from the command line

License: GPLv3
URL: https://github.com/roadelou/template
# Source0: master.tar.gz

BuildRequires: gcc
BuildRequires: make

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
# The default template files are stored in /etc/roadelou_template
/etc/roadelou_template/*.template
