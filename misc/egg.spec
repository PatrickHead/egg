Name:           egg
Version:        0.2.2
Release:        1
Summary:        Parser generation tools for EGG grammars.
#Source0:        http://www.patrickhead.net/projects/egg/%{name}-%{version}.tar.gz 
Source:        %{name}-%{version}.tar.gz 
URL:            http://www.patrickhead.net/projects/egg

Group:          Development/Tools
License:        GPLv3+

Prefix:         /usr

%description
Tools and libraries for generating recursive descent parsers from a grammar that is
defined in the EGG format.

%prep 
%setup -q

%build 
%configure 
make

%install
rm -rf %{buildroot}
%makeinstall   

%files 
%defattr(0755,root,root) 
%doc AUTHORS ChangeLog COPYING INSTALL NEWS README doc/printable.egg doc/egg.pdf doc/PROJECT doc/TODOS doc/VERSION doc/reference-manual/html
%{_bindir}/embryo 
%{_bindir}/egg-walker 
%{_bindir}/egg-mapper 
%{_libdir}/libegg-common.*
%{_libdir}/libegg-parser.*
%{_includedir}/egg/callback.h
%{_includedir}/egg/common.h
%{_includedir}/egg/input.h
%{_includedir}/egg/mkdir_p.h
%{_includedir}/egg/strapp.h

%changelog 
* Wed Dec 18 2013 Patrick Head <patrickhead@gmail.com> 0.1-1generic
- Initial package release
