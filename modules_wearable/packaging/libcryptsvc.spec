Name:      libcryptsvc
Summary:   nothing
Version:    0.0.1
Release:    6
VCS:        magnolia/framework/security/libcryptsvc#submit/master/20130306.011315-19-gac48e818bbb9d2187644955595f303887609bc64
Group:      Osp/Security
License:    APLv2
Source0:    %{name}-%{version}.tar.gz
BuildRequires: cmake

BuildRequires: pkgconfig(dlog)
BuildRequires: pkgconfig(openssl)

%description

%package devel
Summary: nothing
Group: Bada/Security
Requires: %{name} = %{version}-%{release}

%description devel

%prep
%setup -q

%build
%if 0%{?tizen_build_binary_release_type_eng}
export CFLAGS="$CFLAGS -DTIZEN_ENGINEER_MODE"
export CXXFLAGS="$CXXFLAGS -DTIZEN_ENGINEER_MODE"
export FFLAGS="$FFLAGS -DTIZEN_ENGINEER_MODE"
%endif

MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
%ifarch %{ix86}
cmake . -DCMAKE_INSTALL_PREFIX=%{_prefix} -DARCH=x86 -DFULLVER=%{version} -DMAJORVER=${MAJORVER} -DDESCRIPTION=%{summary}
%else
cmake . -DCMAKE_INSTALL_PREFIX=%{_prefix} -DARCH=arm -DFULLVER=%{version} -DMAJORVER=${MAJORVER} -DDESCRIPTION=%{summary}
%endif
make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
mkdir -p %{buildroot}/usr/share/license
cat LICENSE.APLv2 > %{buildroot}/usr/share/license/%{name}

%make_install

%files
%manifest libcryptsvc.manifest
%{_libdir}/*.so*
%{_datadir}/license/%{name}
%attr(755,root,app) /opt/etc/duid-gadget

%files devel
%{_includedir}/*
%{_libdir}/pkgconfig/cryptsvc.pc
