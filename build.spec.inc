# TODO(kkleine): In clang we had this %ifarch s390 s390x aarch64 %ix86 ppc64le
# Decrease debuginfo verbosity to reduce memory consumption during final library linking.
%global reduce_debuginfo 0
%ifarch %ix86
%global reduce_debuginfo 1
%endif
%if 0%{?rhel} == 8
%global reduce_debuginfo 1
%endif

%if %reduce_debuginfo == 1
%global optflags %(echo %{optflags} | sed 's/-g /-g1 /')
%endif

%global projects clang;clang-tools-extra;lld
%if %{with lldb}
%global projects %{projects};lldb
%endif

# Copy CFLAGS into ASMFLAGS, so -fcf-protection is used when compiling assembly files.
export ASMFLAGS="%{build_cflags}"

# We set CLANG_DEFAULT_PIE_ON_LINUX=OFF and PPC_LINUX_DEFAULT_IEEELONGDOUBLE=ON to match the
# defaults used by Fedora's GCC.

#region BEGIN: COPIED FROM CLANG

# Disable dwz on aarch64, because it takes a huge amount of time to decide not to optimize things.
%ifarch aarch64
%define _find_debuginfo_dwz_opts %{nil}
%endif

#endregion

export LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:`pwd`/%{build_libdir}"

cd llvm

#region LLVM lit
%if %{with python_lit}
pushd utils/lit
%py3_build
popd
%endif
#endregion

%if 0%{?rhel} == 8
%undefine __cmake_in_source_build
%endif

# TODO(kkleine): Follow more closely the Distribution guidelines found here: https://llvm.org/docs/BuildingADistribution.html
# force off shared libs as cmake macros turns it on.
# TODO: Disable LLVM_UNREACHABLE_OPTIMIZE.
%cmake	-G Ninja \
	-DLLVM_ENABLE_PROJECTS="%{projects}" \
	\
	\
	-DCLANG_DEFAULT_PIE_ON_LINUX=OFF \
%if 0%{?fedora} || 0%{?rhel} > 9
	-DPPC_LINUX_DEFAULT_IEEELONGDOUBLE=ON \
%endif
	-DPython3_EXECUTABLE=%{__python3} \
	-DLLVM_INCLUDE_TESTS:BOOL=ON \
	-DCLANG_INCLUDE_TESTS:BOOL=ON \
	-DLLVM_BUILD_UTILS:BOOL=ON \
	-DCLANG_ENABLE_ARCMT:BOOL=ON \
	-DCLANG_ENABLE_STATIC_ANALYZER:BOOL=ON \
	-DCLANG_INCLUDE_DOCS:BOOL=ON \
	-DCLANG_PLUGIN_SUPPORT:BOOL=ON \
	-DENABLE_LINKER_BUILD_ID:BOOL=ON \
	-DLLVM_ENABLE_EH=ON \
	-DCLANG_LINK_CLANG_DYLIB=ON \
	-DCLANG_BUILD_EXAMPLES:BOOL=OFF \
	-DCLANG_REPOSITORY_STRING="%{?dist_vendor} %{version}-%{release}" \
%if %{with compat_build}
	-DCLANG_RESOURCE_DIR=../../../lib/clang/%{maj_ver} \
%else
	-DCLANG_RESOURCE_DIR=../lib/clang/%{maj_ver} \
%endif
	-DLLVM_EXTERNAL_CLANG_TOOLS_EXTRA_SOURCE_DIR=../clang-tools-extra \
	-DCLANG_CONFIG_FILE_SYSTEM_DIR=%{_sysconfdir}/%{pkg_name_clang}/ \
	-DCLANG_DEFAULT_UNWINDLIB=libgcc \
	\
	\
	\
	\
-DLLVM_ENABLE_RUNTIMES="compiler-rt;openmp;offload" \
	\
	\
	\
	\
	\
	-DCOMPILER_RT_INSTALL_PATH=%{_prefix}/lib/clang/%{maj_ver} \
	-DLLVM_ENABLE_PER_TARGET_RUNTIME_DIR=ON \
	-DCOMPILER_RT_INCLUDE_TESTS:BOOL=OFF \
	\
	\
	\
	\
	\
	-DLIBOMP_INSTALL_ALIASES=OFF \
	-DOPENMP_INSTALL_LIBDIR=%{unprefixed_libdir} \
	-DOFFLOAD_INSTALL_LIBDIR=%{unprefixed_libdir} \
	\
	\
	\
	\
	-DBUILD_SHARED_LIBS:BOOL=OFF \
	-DLLVM_PARALLEL_LINK_JOBS=1 \
	-DCMAKE_BUILD_TYPE=RelWithDebInfo \
	-DCMAKE_SKIP_RPATH:BOOL=ON \
%if %reduce_debuginfo == 1
	-DCMAKE_C_FLAGS_RELWITHDEBINFO="%{optflags} -DNDEBUG" \
	-DCMAKE_CXX_FLAGS_RELWITHDEBINFO="%{optflags} -DNDEBUG" \
%endif
%if %{without compat_build}
%if 0%{?__isa_bits} == 64
	-DLLVM_LIBDIR_SUFFIX=64 \
%else
	-DLLVM_LIBDIR_SUFFIX= \
%endif
%endif
	\
	-DLLVM_TARGETS_TO_BUILD=%{targets_to_build} \
	-DLLVM_ENABLE_LIBCXX:BOOL=OFF \
	-DLLVM_ENABLE_ZLIB:BOOL=ON \
	-DLLVM_ENABLE_FFI:BOOL=ON \
	-DLLVM_ENABLE_RTTI:BOOL=ON \
	-DLLVM_USE_PERF:BOOL=ON \
%if %{with gold}
	-DLLVM_BINUTILS_INCDIR=%{_includedir} \
%endif
	-DLLVM_EXPERIMENTAL_TARGETS_TO_BUILD=%{experimental_targets_to_build} \
	\
	-DLLVM_BUILD_RUNTIME:BOOL=ON \
	\
	-DLLVM_INCLUDE_TOOLS:BOOL=ON \
	-DLLVM_BUILD_TOOLS:BOOL=ON \
	\
	-DLLVM_BUILD_TESTS:BOOL=ON \
	-DLLVM_INSTALL_GTEST:BOOL=ON \
	-DLLVM_LIT_ARGS="-vv" \
	\
	-DLLVM_INCLUDE_EXAMPLES:BOOL=ON \
	-DLLVM_BUILD_EXAMPLES:BOOL=OFF \
	\
	-DLLVM_INCLUDE_UTILS:BOOL=ON \
	-DLLVM_INSTALL_UTILS:BOOL=ON \
	-DLLVM_UTILS_INSTALL_DIR:PATH=bin \
	-DLLVM_TOOLS_INSTALL_DIR:PATH=bin \
	\
	-DLLVM_INCLUDE_DOCS:BOOL=ON \
	-DLLVM_BUILD_DOCS:BOOL=ON \
	-DLLVM_ENABLE_SPHINX:BOOL=ON \
	-DLLVM_ENABLE_DOXYGEN:BOOL=OFF \
	-DLLVM_APPEND_VC_REV:BOOL=OFF \
	\
%if %{with snapshot_build}
	-DLLVM_VERSION_SUFFIX="%{llvm_snapshot_version_suffix}" \
%else
%if %{without compat_build}
	-DLLVM_VERSION_SUFFIX='' \
%endif
%endif
	-DLLVM_UNREACHABLE_OPTIMIZE:BOOL=ON \
	-DLLVM_BUILD_LLVM_DYLIB:BOOL=ON \
	-DLLVM_LINK_LLVM_DYLIB:BOOL=ON \
	-DLLVM_BUILD_EXTERNAL_COMPILER_RT:BOOL=ON \
	-DLLVM_INSTALL_TOOLCHAIN_ONLY:BOOL=OFF \
	-DLLVM_DEFAULT_TARGET_TRIPLE=%{llvm_triple} \
	-DSPHINX_WARNINGS_AS_ERRORS=OFF \
	-DCMAKE_INSTALL_PREFIX=%{install_prefix} \
	-DLLVM_INSTALL_SPHINX_HTML_DIR=%{_pkgdocdir}/html \
	-DSPHINX_EXECUTABLE=%{_bindir}/sphinx-build-3 \
	-DLLVM_INCLUDE_BENCHMARKS=OFF \
	\
	\
	-DLLVM_DYLIB_COMPONENTS="all" \
	-DLLVM_COMMON_CMAKE_UTILS=%{install_datadir}/llvm/cmake \
	\
	\
	\
%if %{with lldb}
	-DLLDB_DISABLE_CURSES:BOOL=OFF \
	-DLLDB_DISABLE_LIBEDIT:BOOL=OFF \
	-DLLDB_DISABLE_PYTHON:BOOL=OFF \
%ifarch ppc64le
	-DLLDB_TEST_USER_ARGS=--skip-category=watchpoint \
%endif
%if 0%{?rhel} == 8
	-DLLDB_INCLUDE_TESTS:BOOL=OFF \
%else
	-DLLDB_ENFORCE_STRICT_TEST_REQUIREMENTS:BOOL=ON \
%endif
%endif
	\
	\
	\
%ifarch x86_64
	-DCMAKE_SHARED_LINKER_FLAGS="$LDFLAGS -Wl,-z,cet-report=error" \
%endif
%if 0%{?rhel} == 8
	-DLLVM_RAM_PER_COMPILE_JOB=2048 \
%endif
%if %{with lto_build}
%if 0%{?fedora} >= 41
	-DLLVM_UNITTEST_LINK_FLAGS="-fno-lto"
%else
	-DLLVM_UNITTEST_LINK_FLAGS="-Wl,-plugin-opt=O0"
%endif
%endif

# Build libLLVM.so first.  This ensures that when libLLVM.so is linking, there
# are no other compile jobs running.  This will help reduce OOM errors on the
# builders without having to artificially limit the number of concurrent jobs.
%cmake_build --target LLVM

# Also build libclang-cpp.so separately to avoid OOM errors.
# This is to fix occasional OOM errors on the ppc64le COPR builders.
%cmake_build --target libclang-cpp.so

%cmake_build

# If we don't build the runtimes target here, we'll have to wait for the %check
# section until these files are available but they need to be installed.
#
#   /usr/lib64/libomptarget.devicertl.a
#   /usr/lib64/libomptarget-amdgpu-*.bc
#   /usr/lib64/libomptarget-nvptx-*.bc

%cmake_build --target runtimes

cd ..
