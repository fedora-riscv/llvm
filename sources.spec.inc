%if %{with snapshot_build}
Source0:	https://github.com/llvm/llvm-project/archive/%{llvm_snapshot_git_revision}.tar.gz
%else
Source0:	https://github.com/llvm/llvm-project/releases/download/llvmorg-%{maj_ver}.%{min_ver}.%{patch_ver}%{?rc_ver:-rc%{rc_ver}}/%{src_tarball_dir}.tar.xz
Source1001:	https://github.com/llvm/llvm-project/releases/download/llvmorg-%{maj_ver}.%{min_ver}.%{patch_ver}%{?rc_ver:-rc%{rc_ver}}/%{src_tarball_dir}.tar.xz.sig
Source1006:	release-keys.asc
%endif

%if %{without compat_build}
Source2005:	macros.%{pkg_name_clang}
%endif
Source2006:	clang.cfg

# Sources we use to split up the main spec file in sections so that we can more
# easily see what specfile sections are touched by a patch.
Source1000: version.spec.inc
Source1001: build.spec.inc
Source1002: changelog.spec.inc
Source1003: check.spec.inc
Source1004: files.spec.inc
Source1014: files.compiler-rt.spec.inc
Source1005: globals.spec.inc
Source1006: install.spec.inc
Source1008: patches.spec.inc
Source1009: prep.spec.inc
Source1012: sources.spec.inc
Source1013: packages.spec.inc
