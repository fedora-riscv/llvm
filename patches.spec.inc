# RHEL-specific patch to avoid unwanted python3-myst-parser dep
Patch1000:	0101-Deactivate-markdown-doc.patch

#region CLANG patches
Patch2001:     0001-PATCH-clang-Make-funwind-tables-the-default-on-all-a.patch
Patch2002:     0003-PATCH-clang-Don-t-install-static-libraries.patch
#endregion

# Workaround a bug in ORC on ppc64le.
# More info is available here: https://reviews.llvm.org/D159115#4641826
Patch2005:     0001-Workaround-a-bug-in-ORC-on-ppc64le.patch

# # Drop the following patch after debugedit adds support to DWARF-5:
# # https://sourceware.org/bugzilla/show_bug.cgi?id=28728
# Source2006:	0001-Produce-DWARF4-by-default.patch

%if %{with snapshot_build}
# Temporary patch to add back -fno-openmp-implicit-rpath until we no longer
# support Fedora 38 or older, which pass -fno-openmp-implicit-rpath in
# redhat-rpm-config.
Patch2009: 0001-Restore-fopenmp-implicit-rpath-disabled-by-default.patch
%endif

# RHEL specific patches
# Avoid unwanted dependency on python-myst-parser
Patch2100:  0009-disable-myst-parser.patch

%if %{without compat_build}
# Patches for clang-tools-extra
# See https://reviews.llvm.org/D120301
Patch2500:   0001-clang-tools-extra-Make-test-dependency-on-LLVMHello-.patch
%endif
