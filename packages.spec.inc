#region LLVM lit package
%if %{with python_lit}
%package -n python%{python3_pkgversion}-lit
Summary: LLVM lit test runner for Python 3

BuildArch: noarch
Requires: python%{python3_pkgversion}-setuptools
%if 0%{?rhel} == 8
# Became python3.12-clang in LLVM 20
Obsoletes: python3-lit < 19.9
%else
# This optional dependency is not available for python3.12 on RHEL 8.
Recommends: python%{python3_pkgversion}-psutil
%endif

%description -n python%{python3_pkgversion}-lit
lit is a tool used by the LLVM project for executing its test suites.
%endif
#endregion

#region LLVM packages

%package -n %{pkg_name_llvm}-devel
Summary:	Libraries and header files for LLVM
Requires:	%{pkg_name_llvm}%{?_isa} = %{version}-%{release}
Requires:	%{pkg_name_llvm}-libs%{?_isa} = %{version}-%{release}
# The installed LLVM cmake files will add -ledit to the linker flags for any
# app that requires the libLLVMLineEditor, so we need to make sure
# libedit-devel is available.
Requires:	libedit-devel
Requires:	libzstd-devel
# The installed cmake files reference binaries from llvm-test, llvm-static, and
# llvm-gtest.  We tried in the past to split the cmake exports for these binaries
# out into separate files, so that llvm-devel would not need to Require these packages,
# but this caused bugs (rhbz#1773678) and forced us to carry two non-upstream
# patches.
Requires:	%{pkg_name_llvm}-static%{?_isa} = %{version}-%{release}
Requires:	%{pkg_name_llvm}-test%{?_isa} = %{version}-%{release}
Requires:	%{pkg_name_llvm}-googletest%{?_isa} = %{version}-%{release}


Requires(post):	%{_sbindir}/alternatives
Requires(postun):	%{_sbindir}/alternatives

Provides:	llvm-devel(major) = %{maj_ver}

%description -n %{pkg_name_llvm}-devel
This package contains library and header files needed to develop new native
programs that use the LLVM infrastructure.

%package -n %{pkg_name_llvm}-doc
Summary:	Documentation for LLVM
BuildArch:	noarch
Requires:	%{pkg_name_llvm} = %{version}-%{release}

%description -n %{pkg_name_llvm}-doc
Documentation for the LLVM compiler infrastructure.

%package -n %{pkg_name_llvm}-libs
Summary:	LLVM shared libraries

%description -n %{pkg_name_llvm}-libs
Shared libraries for the LLVM compiler infrastructure.

%package -n %{pkg_name_llvm}-static
Summary:	LLVM static libraries
Conflicts:	%{pkg_name_llvm}-devel < 8

Provides:	llvm-static(major) = %{maj_ver}

%description -n %{pkg_name_llvm}-static
Static libraries for the LLVM compiler infrastructure.

%package -n %{pkg_name_llvm}-cmake-utils
Summary: CMake utilities shared across LLVM subprojects

%description -n %{pkg_name_llvm}-cmake-utils
CMake utilities shared across LLVM subprojects.
This is for internal use by LLVM packages only.

%package -n %{pkg_name_llvm}-test
Summary:	LLVM regression tests
Requires:	%{pkg_name_llvm}%{?_isa} = %{version}-%{release}
Requires:	%{pkg_name_llvm}-libs%{?_isa} = %{version}-%{release}

Provides:	llvm-test(major) = %{maj_ver}

%description -n %{pkg_name_llvm}-test
LLVM regression tests.

%package -n %{pkg_name_llvm}-googletest
Summary: LLVM's modified googletest sources

%description -n %{pkg_name_llvm}-googletest
LLVM's modified googletest sources.

%if %{with snapshot_build}
%package -n %{pkg_name_llvm}-build-stats
Summary: Statistics for the RPM build

%description -n %{pkg_name_llvm}-build-stats
Statistics for the RPM build. Only available in snapshot builds.
%endif

#endregion

#region CLANG packages

%package -n %{pkg_name_clang}
Summary:	A C language family front-end for LLVM

Requires:	%{pkg_name_clang}-libs%{?_isa} = %{version}-%{release}

# clang requires gcc, clang++ requires libstdc++-devel
# - https://bugzilla.redhat.com/show_bug.cgi?id=1021645
# - https://bugzilla.redhat.com/show_bug.cgi?id=1158594
Requires:	libstdc++-devel
Requires:	gcc-c++

Provides:	clang(major) = %{maj_ver}

Conflicts:	compiler-rt < 11.0.0

%description -n %{pkg_name_clang}
clang: noun
    1. A loud, resonant, metallic sound.
    2. The strident call of a crane or goose.
    3. C-language family front-end toolkit.

The goal of the Clang project is to create a new C, C++, Objective C
and Objective C++ front-end for the LLVM compiler. Its tools are built
as libraries and designed to be loosely-coupled and extensible.

Install compiler-rt if you want the Blocks C language extension or to
enable sanitization and profiling options when building, and
libomp-devel to enable -fopenmp.

%package -n %{pkg_name_clang}-libs
Summary: Runtime library for clang
Requires: %{pkg_name_clang}-resource-filesystem%{?_isa} = %{version}
Recommends: %{pkg_name_compiler_rt}%{?_isa} = %{version}
Requires: %{pkg_name_llvm}-libs = %{version}
# atomic support is not part of compiler-rt
Recommends: libatomic%{?_isa}
# libomp-devel is required, so clang can find the omp.h header when compiling
# with -fopenmp.
Recommends: %{pkg_name_libomp}-devel%{_isa} = %{version}
Recommends: %{pkg_name_libomp}%{_isa} = %{version}

%description -n %{pkg_name_clang}-libs
Runtime library for clang.

%package -n %{pkg_name_clang}-devel
Summary: Development header files for clang
Requires: %{pkg_name_clang}-libs = %{version}-%{release}
Requires: %{pkg_name_clang}%{?_isa} = %{version}-%{release}
# The clang CMake files reference tools from clang-tools-extra.
Requires: %{pkg_name_clang}-tools-extra%{?_isa} = %{version}-%{release}
Provides: clang-devel(major) = %{maj_ver}

%description -n %{pkg_name_clang}-devel
Development header files for clang.

%package -n %{pkg_name_clang}-resource-filesystem
Summary: Filesystem package that owns the clang resource directory
Provides: clang-resource-filesystem(major) = %{maj_ver}

%description -n %{pkg_name_clang}-resource-filesystem
This package owns the clang resouce directory: $libdir/clang/$version/

%package -n %{pkg_name_clang}-analyzer
Summary:	A source code analysis framework
License:	Apache-2.0 WITH LLVM-exception OR NCSA OR MIT
BuildArch:	noarch
Requires:	%{pkg_name_clang} = %{version}-%{release}

%description -n %{pkg_name_clang}-analyzer
The Clang Static Analyzer consists of both a source code analysis
framework and a standalone tool that finds bugs in C and Objective-C
programs. The standalone tool is invoked from the command-line, and is
intended to run in tandem with a build of a project or code base.

%package -n %{pkg_name_clang}-tools-extra
Summary:	Extra tools for clang
Requires:	%{pkg_name_clang}-libs%{?_isa} = %{version}-%{release}
Requires:	emacs-filesystem

%description -n %{pkg_name_clang}-tools-extra
A set of extra tools built using Clang's tooling API.

%package -n %{pkg_name_clang}-tools-extra-devel
Summary: Development header files for clang tools
Requires: %{pkg_name_clang}-tools-extra = %{version}-%{release}

%description -n %{pkg_name_clang}-tools-extra-devel
Development header files for clang tools.

# Put git-clang-format in its own package, because it Requires git
# and we don't want to force users to install all those dependenices if they
# just want clang.
%package -n git-clang-format%{pkg_suffix}
Summary:	Integration of clang-format for git
Requires:	%{pkg_name_clang}-tools-extra = %{version}-%{release}
Requires:	git
Requires:	python%{python3_pkgversion}

%description -n git-clang-format%{pkg_suffix}
clang-format integration for git.

%if %{without compat_build}
%package -n python%{python3_pkgversion}-clang
Summary:       Python3 bindings for clang
Requires:      %{pkg_name_clang}-devel%{?_isa} = %{version}-%{release}
Requires:      python%{python3_pkgversion}
%if 0%{?rhel} == 8
# Became python3.12-clang in LLVM 20
Obsoletes: python3-clang < 19.9
%endif
%description -n python%{python3_pkgversion}-clang
%{summary}.


%endif

#endregion

#region COMPILER-RT packages

%package -n %{pkg_name_compiler_rt}
Summary:	LLVM "compiler-rt" runtime libraries

License:	Apache-2.0 WITH LLVM-exception OR NCSA OR MIT

Requires: clang-resource-filesystem%{?isa} = %{version}
Provides: compiler-rt(major) = %{maj_ver}

%description -n %{pkg_name_compiler_rt}
The compiler-rt project is a part of the LLVM project. It provides
implementation of the low-level target-specific hooks required by
code generation, sanitizer runtimes and profiling library for code
instrumentation, and Blocks C language extension.

#endregion

#region OPENMP packages

%package -n %{pkg_name_libomp}
Summary: OpenMP runtime for clang

URL: http://openmp.llvm.org

Requires: elfutils-libelf%{?isa}

%description -n %{pkg_name_libomp}
OpenMP runtime for clang.

%package  -n %{pkg_name_libomp}-devel
Summary: OpenMP header files

URL: http://openmp.llvm.org

Requires: %{name}%{?isa} = %{version}-%{release}
Requires: clang-resource-filesystem%{?isa} = %{version}

%description  -n %{pkg_name_libomp}-devel
OpenMP header files.
URL: http://openmp.llvm.org

#endregion

#region LLD packages

%package -n %{pkg_name_lld}
Summary:	The LLVM Linker

Requires(post): %{_sbindir}/update-alternatives
Requires(preun): %{_sbindir}/update-alternatives

Requires: %{pkg_name_lld}-libs = %{version}-%{release}

%description -n %{pkg_name_lld}
The LLVM project linker.

%package -n %{pkg_name_lld}-devel
Summary:	Libraries and header files for LLD
Requires: %{pkg_name_lld}-libs%{?_isa} = %{version}-%{release}
%if %{without compat_build}
# lld tools are referenced in the cmake files, so we need to add lld as a
# dependency.
Requires: %{pkg_name_lld}%{?_isa} = %{version}-%{release}
%endif
Provides: lld-devel(major) = %{maj_ver}

%description -n %{pkg_name_lld}-devel
This package contains library and header files needed to develop new native
programs that use the LLD infrastructure.

%package -n %{pkg_name_lld}-libs
Summary:	LLD shared libraries

%description -n %{pkg_name_lld}-libs
Shared libraries for LLD.

#endregion

#region Toolset package
%if 0%{?rhel}
%package -n %{pkg_name_llvm}-toolset
Summary:	Package that installs llvm-toolset
Requires:	clang = %{version}
Requires:	llvm = %{version}
Requires:	lld = %{version}

%description -n %{pkg_name_llvm}-toolset
This is the main package for llvm-toolset.
%endif
#endregion

#region LLDB packages
%if %{with lldb}
%package -n %{pkg_name_lldb}
Summary:	Next generation high-performance debugger
License:	Apache-2.0 WITH LLVM-exception OR NCSA
URL:		http://lldb.llvm.org/

Requires:	python%{python3_pkgversion}-lldb

%description -n %{pkg_name_lldb}
LLDB is a next generation, high-performance debugger. It is built as a set
of reusable components which highly leverage existing libraries in the
larger LLVM Project, such as the Clang expression parser and LLVM
disassembler.

%package -n %{pkg_name_lldb}-devel
Summary:	Development header files for LLDB
Requires:	%{pkg_name_lldb}%{?_isa} = %{version}-%{release}

%description -n %{pkg_name_lldb}-devel
The package contains header files for the LLDB debugger.

%package -n python%{python3_pkgversion}-lldb
%{?python_provide:%python_provide python%{python3_pkgversion}-lldb}
Summary:	Python module for LLDB

Requires:	%{pkg_name_lldb}%{?_isa} = %{version}-%{release}

%if 0%{?rhel} == 8
# Became python3.12-lldb in LLVM 20
Obsoletes: python3-lldb < 19.9
%endif

%description -n python%{python3_pkgversion}-lldb
The package contains the LLDB Python module.
%endif
#endregion
