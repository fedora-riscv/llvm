%bcond_with snapshot_build

%global maj_ver 19
%global min_ver 1
%global patch_ver 0
#global rc_ver 4

%if %{with snapshot_build}
%include %{_sourcedir}/version.spec.inc
%endif

%include %{_sourcedir}/globals.spec.inc

Name:		%{pkg_name_llvm}
Version:	%{maj_ver}.%{min_ver}.%{patch_ver}%{?rc_ver:~rc%{rc_ver}}%{?llvm_snapshot_version_suffix:~%{llvm_snapshot_version_suffix}}
Release:	1%{?dist}
Summary:	The Low Level Virtual Machine

License:	Apache-2.0 WITH LLVM-exception OR NCSA
URL:		http://llvm.org

%if %{with snapshot_build}
Source0: https://github.com/llvm/llvm-project/archive/%{llvm_snapshot_git_revision}.tar.gz
%else
Source0: https://github.com/llvm/llvm-project/releases/download/llvmorg-%{maj_ver}.%{min_ver}.%{patch_ver}%{?rc_ver:-rc%{rc_ver}}/%{src_tarball_dir}.tar.xz
Source1: https://github.com/llvm/llvm-project/releases/download/llvmorg-%{maj_ver}.%{min_ver}.%{patch_ver}%{?rc_ver:-rc%{rc_ver}}/%{src_tarball_dir}.tar.xz.sig
%endif
Source6: release-keys.asc

%if %{without compat_build}
Source2005: macros.%{pkg_name_clang}
%endif

%if %{with bundle_compat_lib}
Source3000: https://github.com/llvm/llvm-project/releases/download/llvmorg-%{compat_ver}/llvm-project-%{compat_ver}.src.tar.xz
Source3001: https://github.com/llvm/llvm-project/releases/download/llvmorg-%{compat_ver}/llvm-project-%{compat_ver}.src.tar.xz.sig
%endif

# Sources we use to split up the main spec file in sections so that we can more
# easily see what specfile sections are touched by a patch.
%if %{with snapshot_build}
Source1000: version.spec.inc
%endif
Source1001: build.spec.inc
Source1002: changelog.spec.inc
Source1003: check.spec.inc
Source1004: files.spec.inc
Source1005: globals.spec.inc
Source1006: install.spec.inc
Source1007: prep.spec.inc
Source1008: packages.spec.inc

#region CLANG patches
Patch2001: 0001-PATCH-clang-Make-funwind-tables-the-default-on-all-a.patch
Patch2002: 0003-PATCH-clang-Don-t-install-static-libraries.patch
#endregion

# Workaround a bug in ORC on ppc64le.
# More info is available here: https://reviews.llvm.org/D159115#4641826
Patch2005: 0001-Workaround-a-bug-in-ORC-on-ppc64le.patch

#region LLD patches
Patch3002: 0001-Always-build-shared-libs-for-LLD.patch
#endregion

#region RHEL patches
# All RHEL
%if %{maj_ver} >= 20
Patch9001: 0001-20-Remove-myst_parser-dependency-for-RHEL.patch
%else
Patch9001: 0001-19-Remove-myst_parser-dependency-for-RHEL.patch
%endif

# RHEL 8 only
Patch9002: 0001-Fix-page-size-constant-on-aarch64-and-ppc64le.patch
#endregion

%if 0%{?rhel} == 8
%global python3_pkgversion 3.12
%global __python3 /usr/bin/python3.12
%endif

BuildRequires:	gcc
BuildRequires:	gcc-c++
BuildRequires:	clang
BuildRequires:	cmake
BuildRequires:	ninja-build
BuildRequires:	zlib-devel
BuildRequires:	libffi-devel
BuildRequires:	ncurses-devel
# This intentionally does not use python3_pkgversion. RHEL 8 does not have
# python3.12-sphinx, and we are only using it as a binary anyway.
BuildRequires:	python3-sphinx
%if 0%{?rhel} != 8
# RHEL 8 does not have these packages for python3.12. However, they are only
# needed for LLDB tests.
BuildRequires:	python%{python3_pkgversion}-psutil
BuildRequires:	python%{python3_pkgversion}-pexpect
%endif
%if %{undefined rhel}
BuildRequires:	python%{python3_pkgversion}-myst-parser
%endif
# Needed for %%multilib_fix_c_header
BuildRequires:	multilib-rpm-config
%if %{with gold}
BuildRequires:	binutils-devel
%endif
%ifarch %{valgrind_arches}
# Enable extra functionality when run the LLVM JIT under valgrind.
BuildRequires:	valgrind-devel
%endif
# LLVM's LineEditor library will use libedit if it is available.
BuildRequires:	libedit-devel
# We need python3-devel for %%py3_shebang_fix
BuildRequires:	python%{python3_pkgversion}-devel
BuildRequires:	python%{python3_pkgversion}-setuptools
%if 0%{?rhel} == 8
BuildRequires:	python%{python3_pkgversion}-rpm-macros
%endif

# For gpg source verification
BuildRequires:	gnupg2

BuildRequires:	swig
BuildRequires:	libxml2-devel
BuildRequires:	doxygen

# For clang-offload-packager
BuildRequires: elfutils-libelf-devel
BuildRequires: perl
BuildRequires: perl-Data-Dumper
BuildRequires: perl-Encode
BuildRequires: libffi-devel

BuildRequires:	perl-generators

# According to https://fedoraproject.org/wiki/Packaging:Emacs a package
# should BuildRequires: emacs if it packages emacs integration files.
BuildRequires:	emacs

BuildRequires:	libatomic

# scan-build uses these perl modules so they need to be installed in order
# to run the tests.
BuildRequires: perl(Digest::MD5)
BuildRequires: perl(File::Copy)
BuildRequires: perl(File::Find)
BuildRequires: perl(File::Path)
BuildRequires: perl(File::Temp)
BuildRequires: perl(FindBin)
BuildRequires: perl(Hash::Util)
BuildRequires: perl(lib)
BuildRequires: perl(Term::ANSIColor)
BuildRequires: perl(Text::ParseWords)
BuildRequires: perl(Sys::Hostname)

BuildRequires:	graphviz

# This is required because we need "ps" when running LLDB tests
BuildRequires: procps-ng

# For reproducible pyc file generation
# See https://docs.fedoraproject.org/en-US/packaging-guidelines/Python_Appendix/#_byte_compilation_reproducibility
# Since Fedora 41 this happens automatically, and RHEL 8 does not support this.
%if (%{defined fedora} && 0%{?fedora} < 41) || 0%{?rhel} == 9 || 0%{?rhel} == 10
BuildRequires: /usr/bin/marshalparser
%global py_reproducible_pyc_path %{buildroot}%{python3_sitelib}
%endif

Requires:	%{pkg_name_llvm}-libs%{?_isa} = %{version}-%{release}

Provides:	llvm(major) = %{maj_ver}

%description
LLVM is a compiler infrastructure designed for compile-time, link-time,
runtime, and idle-time optimization of programs from arbitrary programming
languages. The compiler infrastructure includes mirror sets of programming
tools as well as libraries with equivalent functionality.

%include %{_sourcedir}/packages.spec.inc

%prep
%include %{_sourcedir}/prep.spec.inc

%build
%include %{_sourcedir}/build.spec.inc

%install
%include %{_sourcedir}/install.spec.inc

%check
%include %{_sourcedir}/check.spec.inc

%ldconfig_scriptlets -n %{pkg_name-llvm}-libs

%if %{without compat_build}
%ldconfig_scriptlets -n %{pkg_name_lld}-libs
%endif

%post -n %{pkg_name_llvm}-devel
%{_sbindir}/update-alternatives --install %{_bindir}/llvm-config%{exec_suffix} llvm-config%{exec_suffix} %{install_bindir}/llvm-config%{exec_suffix}-%{__isa_bits} %{__isa_bits}
%if %{without compat_build}
%{_sbindir}/update-alternatives --install %{_bindir}/llvm-config-%{maj_ver} llvm-config-%{maj_ver} %{install_bindir}/llvm-config%{exec_suffix}-%{__isa_bits} %{__isa_bits}

# During the upgrade from LLVM 16 (F38) to LLVM 17 (F39), we found out the
# main llvm-devel package was leaving entries in the alternatives system.
# Try to remove them now.
for v in 14 15 16; do
  if [[ -e %{_bindir}/llvm-config-$v
        && "x$(%{_bindir}/llvm-config-$v --version | awk -F . '{ print $1 }')" != "x$v" ]]; then
    %{_sbindir}/update-alternatives --remove llvm-config-$v %{install_bindir}/llvm-config%{exec_suffix}-%{__isa_bits}
  fi
done
%endif

%postun -n %{pkg_name_llvm}-devel
if [ $1 -eq 0 ]; then
  %{_sbindir}/update-alternatives --remove llvm-config%{exec_suffix} %{install_bindir}/llvm-config%{exec_suffix}-%{__isa_bits}
fi
%if %{without compat_build}
# When upgrading between minor versions (i.e. from x.y.1 to x.y.2), we must
# not remove the alternative.
# However, during a major version upgrade (i.e. from 16.x.y to 17.z.w), the
# alternative must be removed in order to give priority to a newly installed
# compat package.
if [[ $1 -eq 0
      || "x$(%{_bindir}/llvm-config-%{maj_ver} --version | awk -F . '{ print $1 }')" != "x%{maj_ver}" ]]; then
  %{_sbindir}/update-alternatives --remove llvm-config-%{maj_ver} %{install_bindir}/llvm-config%{exec_suffix}-%{__isa_bits}
fi
%endif

%if %{without compat_build}
%post -n %{pkg_name_lld}
%{_sbindir}/update-alternatives --install %{_bindir}/ld ld %{_bindir}/ld.lld 1

%postun -n %{pkg_name_lld}
if [ $1 -eq 0 ] ; then
  %{_sbindir}/update-alternatives --remove ld %{_bindir}/ld.lld
fi
%endif

%include %{_sourcedir}/files.spec.inc

%changelog
%include %{_sourcedir}/changelog.spec.inc
