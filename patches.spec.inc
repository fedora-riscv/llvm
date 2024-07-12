#region CLANG patches
Patch2001:     0001-PATCH-clang-Make-funwind-tables-the-default-on-all-a.patch
Patch2002:     0003-PATCH-clang-Don-t-install-static-libraries.patch
#endregion

# Workaround a bug in ORC on ppc64le.
# More info is available here: https://reviews.llvm.org/D159115#4641826
Patch2005:     0001-Workaround-a-bug-in-ORC-on-ppc64le.patch

#region LLD patches
Patch3002:     0001-Always-build-shared-libs-for-LLD.patch
#endregion

# # Drop the following patch after debugedit adds support to DWARF-5:
# # https://sourceware.org/bugzilla/show_bug.cgi?id=28728
# Source2006:	0001-Produce-DWARF4-by-default.patch

#region RHEL patches
Patch9002:     0001-Remove-myst_parser-dependency-for-RHEL.patch
#endregion
