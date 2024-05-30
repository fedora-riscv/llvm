%bcond_without snapshot_build
# Components enabled if supported by target architecture:
%define gold_arches %{ix86} x86_64 aarch64 %{power64} s390x
%ifarch %{gold_arches}
  %bcond_without gold
%else
  %bcond_with gold
%endif
%bcond_with compat_build
%bcond_without check

# Disable LTO on x86 and riscv in order to reduce memory consumption.
%ifarch %ix86 riscv64
%bcond_with lto_build
%else
%bcond_without lto_build
%endif

%if %{without lto_build}
%global _lto_cflags %nil
%endif

# We are building with clang for faster/lower memory LTO builds.
# See https://docs.fedoraproject.org/en-US/packaging-guidelines/#_compiler_macros
%global toolchain clang

# Opt out of https://fedoraproject.org/wiki/Changes/fno-omit-frame-pointer
# https://bugzilla.redhat.com/show_bug.cgi?id=2158587
%undefine _include_frame_pointers

# Suffixless tarball name (essentially: basename -s .tar.xz llvm-project-17.0.6.src.tar.xz)
%global src_tarball_dir llvm-project-%{maj_ver}.%{min_ver}.%{patch_ver}%{?rc_ver:rc%{rc_ver}}.src
%if %{with snapshot_build}
%global src_tarball_dir llvm-project-%{llvm_snapshot_git_revision}
%endif

#region LLVM globals

%if %{with compat_build}
%global pkg_name_llvm llvm%{maj_ver}
%global exec_suffix -%{maj_ver}
%global install_prefix %{_libdir}/%{pkg_name_llvm}
%global install_bindir %{install_prefix}/bin
%global install_includedir %{install_prefix}/include
%global install_libdir %{install_prefix}/lib
%global install_datadir %{install_prefix}/share
%global install_libexecdir %{install_prefix}/libexec
%global install_docdir %{install_datadir}/doc

%global pkg_includedir %{_includedir}/%{pkg_name_llvm}
%global pkg_datadir %{install_prefix}/share
%else
%global pkg_name_llvm llvm
%global install_prefix /usr
%global install_bindir %{_bindir}
%global install_datadir %{_datadir}
%global install_libdir %{_libdir}
%global install_includedir %{_includedir}
%global install_libexecdir %{_libexecdir}
%global install_docdir %{_docdir}
%global pkg_datadir %{_datadir}
%global exec_suffix %{nil}
%endif

%if 0%{?rhel}
%global targets_to_build "X86;AMDGPU;PowerPC;NVPTX;SystemZ;AArch64;ARM;Mips;BPF;WebAssembly"
%global experimental_targets_to_build ""
%else
%global targets_to_build "all"
%global experimental_targets_to_build "AVR"
%endif

%global build_install_prefix %{buildroot}%{install_prefix}

# Lower memory usage of dwz on s390x
%global _dwz_low_mem_die_limit_s390x 1
%global _dwz_max_die_limit_s390x 1000000

%global llvm_triple %{_target_platform}

# https://fedoraproject.org/wiki/Changes/PythonSafePath#Opting_out
# Don't add -P to Python shebangs
# The executable Python scripts in /usr/share/opt-viewer/ import each other
%undefine _py3_shebang_P

#endregion

#region CLANG globals

%global pkg_name_clang clang

%if %{with compat_build}
%global pkg_name_clang clang%{maj_ver}
# Install clang to same prefix as llvm, so that apps that use llvm-config
# will also be able to find clang libs.
%global pkg_includedir %{install_prefix}/include
%endif

%ifarch ppc64le
# Too many threads on ppc64 systems causes OOM errors.
# TODO(kkleine): Is this really needed when building together with llvm? 
%global _smp_mflags -j8
%endif

#endregion

#region COMPILER-RT globals

%if %{without compat_build}

%global pkg_name_compiler_rt compiler-rt

# TODO(kkleine): do these optflags hurt llvm and/or clang?

# see https://sourceware.org/bugzilla/show_bug.cgi?id=25271
%global optflags %(echo %{optflags} -D_DEFAULT_SOURCE)

# see https://gcc.gnu.org/bugzilla/show_bug.cgi?id=93615
%global optflags %(echo %{optflags} -Dasm=__asm__)

# Copy CFLAGS into ASMFLAGS, so -fcf-protection is used when compiling assembly files.
# export ASMFLAGS=$CFLAGS

%endif

#endregion

#region OPENMP globals

%if %{without compat_build}

%global pkg_name_libomp libomp

%global so_suffix %{maj_ver}.%{min_ver}

%if %{with snapshot_build}
%global so_suffix %{maj_ver}.%{min_ver}%{llvm_snapshot_version_suffix}
%endif

%ifarch ppc64le
%global libomp_arch ppc64
%else
%global libomp_arch %{_arch}
%endif

%endif

#endregion

#region LLD globals
%if %{with compat_build}
%global pkg_name_lld lld%{maj_ver}
%else
%global pkg_name_lld lld
%endif
#endregion
