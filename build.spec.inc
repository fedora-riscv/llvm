# Disable LTO to speed up builds
%if %{with snapshot_build}
%global _lto_cflags %nil
%endif

# TODO(kkleine): In clang we had this %ifarch s390 s390x %{arm} aarch64 %ix86 ppc64le
%ifarch s390 s390x %{arm} %ix86
# Decrease debuginfo verbosity to reduce memory consumption during final library linking
%global optflags %(echo %{optflags} | sed 's/-g /-g1 /')
%endif

# Copy CFLAGS into ASMFLAGS, so -fcf-protection is used when compiling assembly files.
export ASMFLAGS="%{build_cflags}"

# We set CLANG_DEFAULT_PIE_ON_LINUX=OFF and PPC_LINUX_DEFAULT_IEEELONGDOUBLE=ON to match the
# defaults used by Fedora's GCC.

#region BEGIN: COPIED FROM CLANG

# And disable LTO on AArch64 entirely.
%ifarch aarch64
%define _lto_cflags %{nil}
%endif

# TODO(kkleine): Make sure the paths actually work. I have the feeling this needs adjustment
pwd
%if 0%{?__isa_bits} == 64
sed -i 's/\@FEDORA_LLVM_LIB_SUFFIX\@/64/g' llvm/test/lit.cfg.py
%else
sed -i 's/\@FEDORA_LLVM_LIB_SUFFIX\@//g' llvm/test/lit.cfg.py
%endif

# Disable dwz on aarch64, because it takes a huge amount of time to decide not to optimize things.
%ifarch aarch64
%define _find_debuginfo_dwz_opts %{nil}
%endif

#endregion

export LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:`pwd`/llvm/%{_vpath_builddir}/%{_lib}"

cd llvm

# TODO(kkleine): Follow more closely the Distribution guidelines found here: https://llvm.org/docs/BuildingADistribution.html
# force off shared libs as cmake macros turns it on.
# TODO: Disable LLVM_UNREACHABLE_OPTIMIZE.
# TODO: LIBOMP_HAVE_VERSION_SCRIPT_FLAG should be set automatically.
%cmake	-G Ninja \
	-DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra" \
	\
	\
	-DCLANG_DEFAULT_PIE_ON_LINUX=OFF \
%if 0%{?fedora} || 0%{?rhel} > 9
	-DPPC_LINUX_DEFAULT_IEEELONGDOUBLE=ON \
%endif
	-DPYTHON_EXECUTABLE=%{__python3} \
%if %{with compat_build}
	-DLLVM_INCLUDE_TESTS:BOOL=OFF \
	-DCLANG_INCLUDE_TESTS:BOOL=OFF \
	-DCLANG_BUILD_TOOLS:BOOL=OFF \
%else
	-DLLVM_INCLUDE_TESTS:BOOL=ON \
	-DCLANG_INCLUDE_TESTS:BOOL=ON \
	-DLLVM_BUILD_UTILS:BOOL=ON \
%endif
	-DCLANG_ENABLE_ARCMT:BOOL=ON \
	-DCLANG_ENABLE_STATIC_ANALYZER:BOOL=ON \
	-DCLANG_INCLUDE_DOCS:BOOL=ON \
	-DCLANG_PLUGIN_SUPPORT:BOOL=ON \
	-DENABLE_LINKER_BUILD_ID:BOOL=ON \
	-DLLVM_ENABLE_EH=ON \
	-DCLANG_LINK_CLANG_DYLIB=ON \
	-DCLANG_BUILD_EXAMPLES:BOOL=OFF \
	-DCLANG_REPOSITORY_STRING="%{?dist_vendor} %{version}-%{release}" \
	-DCLANG_RESOURCE_DIR=../lib/clang/%{maj_ver} \
	-DLLVM_EXTERNAL_CLANG_TOOLS_EXTRA_SOURCE_DIR=../clang-tools-extra \
	-DCLANG_CONFIG_FILE_SYSTEM_DIR=%{_sysconfdir}/%{pkg_name_clang}/ \
%ifarch %{arm}
	-DCLANG_DEFAULT_LINKER=lld \
%endif
	-DCLANG_DEFAULT_UNWINDLIB=libgcc \
	\
	\
	\
	\
%if %{without compat_build}
-DLLVM_ENABLE_RUNTIMES="compiler-rt;openmp" \
%endif
	\
	\
	\
	\
	\
%if %{without compat_build}
	-DCOMPILER_RT_INSTALL_PATH=%{_prefix}/lib/clang/%{maj_ver} \
	-DLLVM_ENABLE_PER_TARGET_RUNTIME_DIR=ON \
	-DCOMPILER_RT_INCLUDE_TESTS:BOOL=OFF \
%endif
	\
	\
	\
	\
	\
%if %{without compat_build}
	-DLIBOMP_HAVE_VERSION_SCRIPT_FLAG:BOOL=ON \
	-DLIBOMP_INSTALL_ALIASES=OFF \
%if 0%{?__isa_bits} == 64
	-DOPENMP_LIBDIR_SUFFIX=64 \
%else
	-DOPENMP_LIBDIR_SUFFIX= \
%endif
%endif
	\
	\
	\
	\
	-DBUILD_SHARED_LIBS:BOOL=OFF \
	-DLLVM_PARALLEL_LINK_JOBS=1 \
	-DCMAKE_BUILD_TYPE=RelWithDebInfo \
	-DCMAKE_SKIP_RPATH:BOOL=ON \
%ifarch s390 %{arm} %ix86
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
%if %{with compat_build}
	-DLLVM_INSTALL_GTEST:BOOL=OFF \
%else
	-DLLVM_INSTALL_GTEST:BOOL=ON \
%endif
	-DLLVM_LIT_ARGS=-vv \
	\
	-DLLVM_INCLUDE_EXAMPLES:BOOL=ON \
	-DLLVM_BUILD_EXAMPLES:BOOL=OFF \
	\
	-DLLVM_INCLUDE_UTILS:BOOL=ON \
%if %{with compat_build}
	-DLLVM_INSTALL_UTILS:BOOL=OFF \
%else
	-DLLVM_INSTALL_UTILS:BOOL=ON \
	-DLLVM_UTILS_INSTALL_DIR:PATH=%{_bindir} \
	-DLLVM_TOOLS_INSTALL_DIR:PATH=bin \
%endif
	\
	-DLLVM_INCLUDE_DOCS:BOOL=ON \
	-DLLVM_BUILD_DOCS:BOOL=ON \
	-DLLVM_ENABLE_SPHINX:BOOL=ON \
	-DLLVM_ENABLE_DOXYGEN:BOOL=OFF \
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
%ifarch x86_64
	-DCMAKE_SHARED_LINKER_FLAGS="$LDFLAGS -Wl,-z,cet-report=error" \
%endif
%if %{without snapshot_build}
	-DLLVM_UNITTEST_LINK_FLAGS="-Wl,-plugin-opt=O0"
%endif

# Build libLLVM.so first.  This ensures that when libLLVM.so is linking, there
# are no other compile jobs running.  This will help reduce OOM errors on the
# builders without having to artificially limit the number of concurrent jobs.
%cmake_build --target LLVM

%cmake_build

# If we don't build the runtimes target here, we'll have to wait for the %check
# section until these files are available but they need to be installed.
#
#   /usr/lib64/libomptarget.devicertl.a
#   /usr/lib64/libomptarget-amdgpu-*.bc
#   /usr/lib64/libomptarget-nvptx-*.bc

%cmake_build --target runtimes

cd ..
