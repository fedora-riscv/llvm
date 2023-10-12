%if %{without snapshot_build}
# llvm
%{gpgverify} --keyring='%{SOURCE1006}' --signature='%{SOURCE1}' --data='%{SOURCE0}'
%endif

# -T     : Do Not Perform Default Archive Unpacking (without this, the <n>th source would be unpacked twice)
# -b <n> : Unpack The nth Sources Before Changing Directory
# -n     : Set Name of Build Directory
#
# see http://ftp.rpm.org/max-rpm/s1-rpm-inside-macros.html
%autosetup -T -b 0 -p1 -n %{src_tarball_dir}

#region LLVM preparation

%py3_shebang_fix \
	llvm/test/BugPoint/compile-custom.ll.py \
	llvm/tools/opt-viewer/*.py \
	llvm/utils/update_cc_test_checks.py

#endregion

#region CLANG preparation

%if %{without compat_build}

%py3_shebang_fix \
	clang-tools-extra/clang-tidy/tool/ \
	clang-tools-extra/clang-include-fixer/find-all-symbols/tool/run-find-all-symbols.py

%py3_shebang_fix \
	clang/tools/clang-format/ \
	clang/tools/clang-format/git-clang-format \
	clang/utils/hmaptool/hmaptool \
	clang/tools/scan-view/bin/scan-view \
	clang/tools/scan-view/share/Reporter.py \
	clang/tools/scan-view/share/startfile.py \
	clang/tools/scan-build-py/bin/* \
	clang/tools/scan-build-py/libexec/*

%endif

#endregion

#region COMPILER-RT preparation

%if %{without compat_build}
%py3_shebang_fix compiler-rt/lib/hwasan/scripts/hwasan_symbolize
%endif

#endregion
