#region LLVM lit files
%if %{with python_lit}
%files -n python3-lit
%license llvm/utils/lit/LICENSE.TXT
%doc llvm/utils/lit/README.rst
%{python3_sitelib}/lit/
%{python3_sitelib}/lit-*-info/
%{_bindir}/lit
%endif
#endregion

#region LLVM files

%files -n %{pkg_name_llvm}
%license llvm/LICENSE.TXT
%exclude %{_mandir}/man1/llvm-config*

%{_mandir}/man1/bugpoint%{exec_suffix}.1.gz
%{_mandir}/man1/clang-tblgen%{exec_suffix}.1.gz
%{_mandir}/man1/dsymutil%{exec_suffix}.1.gz
%{_mandir}/man1/FileCheck%{exec_suffix}.1.gz
%{_mandir}/man1/lit%{exec_suffix}.1.gz
%{_mandir}/man1/llc%{exec_suffix}.1.gz
%{_mandir}/man1/lldb-tblgen%{exec_suffix}.1.gz
%{_mandir}/man1/lli%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-addr2line%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-ar%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-as%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-bcanalyzer%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-cov%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-cxxfilt%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-cxxmap%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-debuginfo-analyzer%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-diff%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-dis%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-dwarfdump%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-dwarfutil%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-exegesis%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-extract%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-ifs%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-install-name-tool%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-lib%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-libtool-darwin%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-link%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-lipo%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-locstats%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-mc%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-mca%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-nm%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-objcopy%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-objdump%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-opt-report%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-otool%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-pdbutil%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-profdata%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-profgen%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-ranlib%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-readelf%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-readobj%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-reduce%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-remarkutil%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-size%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-stress%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-strings%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-strip%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-symbolizer%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-tblgen%{exec_suffix}.1.gz
%{_mandir}/man1/llvm-tli-checker%{exec_suffix}.1.gz
%{_mandir}/man1/mlir-tblgen%{exec_suffix}.1.gz
%{_mandir}/man1/opt%{exec_suffix}.1.gz
%{_mandir}/man1/tblgen%{exec_suffix}.1.gz

%{install_bindir}/bugpoint
%{install_bindir}/dsymutil
%{install_bindir}/FileCheck
%{install_bindir}/llc
%{install_bindir}/lli
%{install_bindir}/llvm-addr2line
%{install_bindir}/llvm-ar
%{install_bindir}/llvm-as
%{install_bindir}/llvm-bcanalyzer
%{install_bindir}/llvm-bitcode-strip
%{install_bindir}/llvm-c-test
%{install_bindir}/llvm-cat
%{install_bindir}/llvm-cfi-verify
%{install_bindir}/llvm-cov
%{install_bindir}/llvm-cvtres
%{install_bindir}/llvm-cxxdump
%{install_bindir}/llvm-cxxfilt
%{install_bindir}/llvm-cxxmap
%{install_bindir}/llvm-debuginfo-analyzer
%{install_bindir}/llvm-debuginfod
%{install_bindir}/llvm-debuginfod-find
%{install_bindir}/llvm-diff
%{install_bindir}/llvm-dis
%{install_bindir}/llvm-dlltool
%{install_bindir}/llvm-dwarfdump
%{install_bindir}/llvm-dwarfutil
%{install_bindir}/llvm-dwp
%{install_bindir}/llvm-exegesis
%{install_bindir}/llvm-extract
%{install_bindir}/llvm-gsymutil
%{install_bindir}/llvm-ifs
%{install_bindir}/llvm-install-name-tool
%{install_bindir}/llvm-jitlink
%{install_bindir}/llvm-jitlink-executor
%{install_bindir}/llvm-lib
%{install_bindir}/llvm-libtool-darwin
%{install_bindir}/llvm-link
%{install_bindir}/llvm-lipo
%{install_bindir}/llvm-lto
%{install_bindir}/llvm-lto2
%{install_bindir}/llvm-mc
%{install_bindir}/llvm-mca
%{install_bindir}/llvm-ml
%{install_bindir}/llvm-modextract
%{install_bindir}/llvm-mt
%{install_bindir}/llvm-nm
%{install_bindir}/llvm-objcopy
%{install_bindir}/llvm-objdump
%{install_bindir}/llvm-opt-report
%{install_bindir}/llvm-otool
%{install_bindir}/llvm-pdbutil
%{install_bindir}/llvm-PerfectShuffle
%{install_bindir}/llvm-profdata
%{install_bindir}/llvm-profgen
%{install_bindir}/llvm-ranlib
%{install_bindir}/llvm-rc
%{install_bindir}/llvm-readelf
%{install_bindir}/llvm-readobj
%{install_bindir}/llvm-readtapi
%{install_bindir}/llvm-reduce
%{install_bindir}/llvm-remarkutil
%{install_bindir}/llvm-rtdyld
%{install_bindir}/llvm-sim
%{install_bindir}/llvm-size
%{install_bindir}/llvm-split
%{install_bindir}/llvm-stress
%{install_bindir}/llvm-strings
%{install_bindir}/llvm-strip
%{install_bindir}/llvm-symbolizer
%{install_bindir}/llvm-tblgen
%{install_bindir}/llvm-tli-checker
%{install_bindir}/llvm-undname
%{install_bindir}/llvm-windres
%{install_bindir}/llvm-xray
%{install_bindir}/reduce-chunk-list
%{install_bindir}/obj2yaml
%{install_bindir}/opt
%{install_bindir}/sancov
%{install_bindir}/sanstats
%{install_bindir}/split-file
%{install_bindir}/UnicodeNameMappingGenerator
%{install_bindir}/verify-uselistorder
%{install_bindir}/yaml2obj


%if %{with compat_build}
# This is for all the binaries with the version suffix.
%{_bindir}/bugpoint%{exec_suffix}
%{_bindir}/dsymutil%{exec_suffix}
%{_bindir}/FileCheck%{exec_suffix}
%{_bindir}/llc%{exec_suffix}
%{_bindir}/lli%{exec_suffix}
%{_bindir}/llvm-addr2line%{exec_suffix}
%{_bindir}/llvm-ar%{exec_suffix}
%{_bindir}/llvm-as%{exec_suffix}
%{_bindir}/llvm-bcanalyzer%{exec_suffix}
%{_bindir}/llvm-bitcode-strip%{exec_suffix}
%{_bindir}/llvm-c-test%{exec_suffix}
%{_bindir}/llvm-cat%{exec_suffix}
%{_bindir}/llvm-cfi-verify%{exec_suffix}
%{_bindir}/llvm-cov%{exec_suffix}
%{_bindir}/llvm-cvtres%{exec_suffix}
%{_bindir}/llvm-cxxdump%{exec_suffix}
%{_bindir}/llvm-cxxfilt%{exec_suffix}
%{_bindir}/llvm-cxxmap%{exec_suffix}
%{_bindir}/llvm-debuginfo-analyzer%{exec_suffix}
%{_bindir}/llvm-debuginfod%{exec_suffix}
%{_bindir}/llvm-debuginfod-find%{exec_suffix}
%{_bindir}/llvm-diff%{exec_suffix}
%{_bindir}/llvm-dis%{exec_suffix}
%{_bindir}/llvm-dlltool%{exec_suffix}
%{_bindir}/llvm-dwarfdump%{exec_suffix}
%{_bindir}/llvm-dwarfutil%{exec_suffix}
%{_bindir}/llvm-dwp%{exec_suffix}
%{_bindir}/llvm-exegesis%{exec_suffix}
%{_bindir}/llvm-extract%{exec_suffix}
%{_bindir}/llvm-gsymutil%{exec_suffix}
%{_bindir}/llvm-ifs%{exec_suffix}
%{_bindir}/llvm-install-name-tool%{exec_suffix}
%{_bindir}/llvm-jitlink%{exec_suffix}
%{_bindir}/llvm-jitlink-executor%{exec_suffix}
%{_bindir}/llvm-lib%{exec_suffix}
%{_bindir}/llvm-libtool-darwin%{exec_suffix}
%{_bindir}/llvm-link%{exec_suffix}
%{_bindir}/llvm-lipo%{exec_suffix}
%{_bindir}/llvm-lto%{exec_suffix}
%{_bindir}/llvm-lto2%{exec_suffix}
%{_bindir}/llvm-mc%{exec_suffix}
%{_bindir}/llvm-mca%{exec_suffix}
%{_bindir}/llvm-ml%{exec_suffix}
%{_bindir}/llvm-modextract%{exec_suffix}
%{_bindir}/llvm-mt%{exec_suffix}
%{_bindir}/llvm-nm%{exec_suffix}
%{_bindir}/llvm-objcopy%{exec_suffix}
%{_bindir}/llvm-objdump%{exec_suffix}
%{_bindir}/llvm-opt-report%{exec_suffix}
%{_bindir}/llvm-otool%{exec_suffix}
%{_bindir}/llvm-pdbutil%{exec_suffix}
%{_bindir}/llvm-PerfectShuffle%{exec_suffix}
%{_bindir}/llvm-profdata%{exec_suffix}
%{_bindir}/llvm-profgen%{exec_suffix}
%{_bindir}/llvm-ranlib%{exec_suffix}
%{_bindir}/llvm-rc%{exec_suffix}
%{_bindir}/llvm-readelf%{exec_suffix}
%{_bindir}/llvm-readobj%{exec_suffix}
%{_bindir}/llvm-readtapi%{exec_suffix}
%{_bindir}/llvm-reduce%{exec_suffix}
%{_bindir}/llvm-remarkutil%{exec_suffix}
%{_bindir}/llvm-rtdyld%{exec_suffix}
%{_bindir}/llvm-sim%{exec_suffix}
%{_bindir}/llvm-size%{exec_suffix}
%{_bindir}/llvm-split%{exec_suffix}
%{_bindir}/llvm-stress%{exec_suffix}
%{_bindir}/llvm-strings%{exec_suffix}
%{_bindir}/llvm-strip%{exec_suffix}
%{_bindir}/llvm-symbolizer%{exec_suffix}
%{_bindir}/llvm-tblgen%{exec_suffix}
%{_bindir}/llvm-tli-checker%{exec_suffix}
%{_bindir}/llvm-undname%{exec_suffix}
%{_bindir}/llvm-windres%{exec_suffix}
%{_bindir}/llvm-xray%{exec_suffix}
%{_bindir}/reduce-chunk-list%{exec_suffix}
%{_bindir}/obj2yaml%{exec_suffix}
%{_bindir}/opt%{exec_suffix}
%{_bindir}/sancov%{exec_suffix}
%{_bindir}/sanstats%{exec_suffix}
%{_bindir}/split-file%{exec_suffix}
%{_bindir}/UnicodeNameMappingGenerator%{exec_suffix}
%{_bindir}/verify-uselistorder%{exec_suffix}
%{_bindir}/yaml2obj%{exec_suffix}

%endif

%exclude %{_bindir}/llvm-config%{exec_suffix}
%exclude %{install_bindir}/llvm-config%{exec_suffix}-%{__isa_bits}

%exclude %{_bindir}/llvm-config-%{maj_ver}
%exclude %{install_bindir}/llvm-config-%{maj_ver}-%{__isa_bits}
%exclude %{install_bindir}/not
%exclude %{install_bindir}/count
%exclude %{install_bindir}/yaml-bench
%exclude %{install_bindir}/lli-child-target
%exclude %{install_bindir}/llvm-isel-fuzzer
%exclude %{install_bindir}/llvm-opt-fuzzer
%{pkg_datadir}/opt-viewer

%files -n %{pkg_name_llvm}-libs
%license llvm/LICENSE.TXT
%{install_libdir}/libLLVM-%{maj_ver}%{?llvm_snapshot_version_suffix:%{llvm_snapshot_version_suffix}}.so
%if %{with gold}
%{install_libdir}/LLVMgold.so
%if %{without compat_build}
%{_libdir}/bfd-plugins/LLVMgold.so
%endif
%endif
%{install_libdir}/libLLVM.so.%{maj_ver}.%{min_ver}%{?llvm_snapshot_version_suffix:%{llvm_snapshot_version_suffix}}
%{install_libdir}/libLTO.so*
%{install_libdir}/libRemarks.so*
%if %{with compat_build}
%config(noreplace) /etc/ld.so.conf.d/%{name}-%{_arch}.conf
%endif

%files -n %{pkg_name_llvm}-devel
%license llvm/LICENSE.TXT

%if %{without compat_build}
%ghost %{_bindir}/llvm-config
%{install_bindir}/llvm-config-%{__isa_bits}
%else
%{install_bindir}/llvm-config
%endif
%ghost %{_bindir}/llvm-config-%{maj_ver}
%{install_bindir}/llvm-config-%{maj_ver}-%{__isa_bits}

%{_mandir}/man1/llvm-config*
%{install_includedir}/llvm
%{install_includedir}/llvm-c
%{install_libdir}/libLLVM.so
%{install_libdir}/cmake/llvm

%files -n %{pkg_name_llvm}-doc
%license llvm/LICENSE.TXT
%doc %{_pkgdocdir}/html

%files -n %{pkg_name_llvm}-static
%license llvm/LICENSE.TXT
%{install_libdir}/libLLVM*.a
%exclude %{install_libdir}/libLLVMTestingSupport.a
%exclude %{install_libdir}/libLLVMTestingAnnotations.a

%files -n %{pkg_name_llvm}-cmake-utils
%license llvm/LICENSE.TXT
%{pkg_datadir}/llvm/cmake

%files -n %{pkg_name_llvm}-test
%license llvm/LICENSE.TXT
%{install_bindir}/not
%{install_bindir}/count
%{install_bindir}/yaml-bench
%{install_bindir}/lli-child-target
%{install_bindir}/llvm-isel-fuzzer
%{install_bindir}/llvm-opt-fuzzer
%if %{with compat_build}
%{_bindir}/not%{exec_suffix}
%{_bindir}/count%{exec_suffix}
%{_bindir}/yaml-bench%{exec_suffix}
%{_bindir}/lli-child-target%{exec_suffix}
%{_bindir}/llvm-isel-fuzzer%{exec_suffix}
%{_bindir}/llvm-opt-fuzzer%{exec_suffix}
%endif

%files -n %{pkg_name_llvm}-googletest
%license llvm/LICENSE.TXT
%{install_libdir}/libLLVMTestingSupport.a
%{install_libdir}/libLLVMTestingAnnotations.a
%{install_libdir}/libllvm_gtest.a
%{install_libdir}/libllvm_gtest_main.a
%{install_includedir}/llvm-gtest
%{install_includedir}/llvm-gmock

%if %{with snapshot_build}
%files -n %{pkg_name_llvm}-build-stats
%{pkg_datadir}/.ninja_log
%endif

#endregion

#region CLANG files

%files -n %{pkg_name_clang}
%license clang/LICENSE.TXT
%{install_bindir}/clang
%{install_bindir}/clang++
%{install_bindir}/clang-%{maj_ver}
%{install_bindir}/clang++-%{maj_ver}
%{install_bindir}/clang-cl
%{install_bindir}/clang-cpp
%{_sysconfdir}/%{pkg_name_clang}/%{_target_platform}-clang.cfg
%{_sysconfdir}/%{pkg_name_clang}/%{_target_platform}-clang++.cfg
%{_mandir}/man1/clang-%{maj_ver}.1.gz
%{_mandir}/man1/clang++-%{maj_ver}.1.gz
%if %{without compat_build}
%{_mandir}/man1/clang.1.gz
%{_mandir}/man1/clang++.1.gz
%else
%{_bindir}/clang-%{maj_ver}
%{_bindir}/clang++-%{maj_ver}
%{_bindir}/clang-cl-%{maj_ver}
%{_bindir}/clang-cpp-%{maj_ver}
%endif

%files -n %{pkg_name_clang}-libs
%license clang/LICENSE.TXT
%{_prefix}/lib/clang/%{maj_ver}/include/*
%{install_libdir}/libclang.so.*
%{install_libdir}/libclang-cpp.so.*

%files -n %{pkg_name_clang}-devel
%license clang/LICENSE.TXT
%{install_libdir}/libclang-cpp.so
%{install_libdir}/libclang.so
%{install_includedir}/clang/
%{install_includedir}/clang-c/
%{install_libdir}/cmake/clang
%{install_bindir}/clang-tblgen
%if %{with compat_build}
%{_bindir}/clang-tblgen-%{maj_ver}
%endif
%dir %{install_datadir}/clang/

%files -n %{pkg_name_clang}-resource-filesystem
%license clang/LICENSE.TXT
%dir %{_prefix}/lib/clang/
%dir %{_prefix}/lib/clang/%{maj_ver}/
%dir %{_prefix}/lib/clang/%{maj_ver}/bin/
%dir %{_prefix}/lib/clang/%{maj_ver}/include/
%dir %{_prefix}/lib/clang/%{maj_ver}/lib/
%dir %{_prefix}/lib/clang/%{maj_ver}/share/
%{_rpmmacrodir}/macros.%{pkg_name_clang}

%files -n %{pkg_name_clang}-analyzer
%license clang/LICENSE.TXT
%{install_bindir}/scan-view
%{install_bindir}/scan-build
%{install_bindir}/analyze-build
%{install_bindir}/intercept-build
%{install_bindir}/scan-build-py
%if %{with compat_build}
%{_bindir}/scan-view-%{maj_ver}
%{_bindir}/scan-build-%{maj_ver}
%{_bindir}/analyze-build-%{maj_ver}
%{_bindir}/intercept-build-%{maj_ver}
%{_bindir}/scan-build-py-%{maj_ver}
%endif
%{install_libexecdir}/ccc-analyzer
%{install_libexecdir}/c++-analyzer
%{install_libexecdir}/analyze-c++
%{install_libexecdir}/analyze-cc
%{install_libexecdir}/intercept-c++
%{install_libexecdir}/intercept-cc
%{install_datadir}/scan-view/
%{install_datadir}/scan-build/
%{_mandir}/man1/scan-build%{exec_suffix}.1.*
%if %{without compat_build}
%{python3_sitelib}/libear
%{python3_sitelib}/libscanbuild
%endif


%files -n %{pkg_name_clang}-tools-extra
%license clang-tools-extra/LICENSE.TXT
%{install_bindir}/amdgpu-arch
%{install_bindir}/clang-apply-replacements
%{install_bindir}/clang-change-namespace
%{install_bindir}/clang-check
%{install_bindir}/clang-doc
%{install_bindir}/clang-extdef-mapping
%{install_bindir}/clang-format
%{install_bindir}/clang-include-cleaner
%{install_bindir}/clang-include-fixer
%{install_bindir}/clang-installapi
%{install_bindir}/clang-move
%{install_bindir}/clang-offload-bundler
%{install_bindir}/clang-offload-packager
%{install_bindir}/clang-linker-wrapper
%{install_bindir}/clang-nvlink-wrapper
%{install_bindir}/clang-pseudo
%{install_bindir}/clang-query
%{install_bindir}/clang-refactor
%{install_bindir}/clang-rename
%{install_bindir}/clang-reorder-fields
%{install_bindir}/clang-repl
%{install_bindir}/clang-scan-deps
%{install_bindir}/clang-tidy
%{install_bindir}/clangd
%{install_bindir}/diagtool
%{install_bindir}/hmaptool
%{install_bindir}/nvptx-arch
%{install_bindir}/pp-trace
%{install_bindir}/c-index-test
%{install_bindir}/find-all-symbols
%{install_bindir}/modularize
%{install_bindir}/clang-format-diff
%{install_bindir}/run-clang-tidy
%if %{with compat_build}
%{_bindir}/amdgpu-arch-%{maj_ver}
%{_bindir}/clang-apply-replacements-%{maj_ver}
%{_bindir}/clang-change-namespace-%{maj_ver}
%{_bindir}/clang-check-%{maj_ver}
%{_bindir}/clang-doc-%{maj_ver}
%{_bindir}/clang-extdef-mapping-%{maj_ver}
%{_bindir}/clang-format-%{maj_ver}
%{_bindir}/clang-include-cleaner-%{maj_ver}
%{_bindir}/clang-include-fixer-%{maj_ver}
%{_bindir}/clang-installapi-%{maj_ver}
%{_bindir}/clang-move-%{maj_ver}
%{_bindir}/clang-offload-bundler-%{maj_ver}
%{_bindir}/clang-offload-packager-%{maj_ver}
%{_bindir}/clang-linker-wrapper-%{maj_ver}
%{_bindir}/clang-nvlink-wrapper-%{maj_ver}
%{_bindir}/clang-pseudo-%{maj_ver}
%{_bindir}/clang-query-%{maj_ver}
%{_bindir}/clang-refactor-%{maj_ver}
%{_bindir}/clang-rename-%{maj_ver}
%{_bindir}/clang-reorder-fields-%{maj_ver}
%{_bindir}/clang-repl-%{maj_ver}
%{_bindir}/clang-scan-deps-%{maj_ver}
%{_bindir}/clang-tidy-%{maj_ver}
%{_bindir}/clangd-%{maj_ver}
%{_bindir}/diagtool-%{maj_ver}
%{_bindir}/hmaptool-%{maj_ver}
%{_bindir}/nvptx-arch-%{maj_ver}
%{_bindir}/pp-trace-%{maj_ver}
%{_bindir}/c-index-test-%{maj_ver}
%{_bindir}/find-all-symbols-%{maj_ver}
%{_bindir}/modularize-%{maj_ver}
%{_bindir}/clang-format-diff-%{maj_ver}
%{_bindir}/run-clang-tidy-%{maj_ver}
%else
%{_emacs_sitestartdir}/clang-format.el
%{_emacs_sitestartdir}/clang-rename.el
%{_emacs_sitestartdir}/clang-include-fixer.el
%endif
%{_mandir}/man1/diagtool%{exec_suffix}.1.gz
%{_mandir}/man1/extraclangtools%{exec_suffix}.1.gz
%{install_datadir}/clang/clang-format.py*
%{install_datadir}/clang/clang-format-diff.py*
%{install_datadir}/clang/clang-include-fixer.py*
%{install_datadir}/clang/clang-tidy-diff.py*
%{install_datadir}/clang/run-find-all-symbols.py*
%{install_datadir}/clang/clang-rename.py*


%files -n %{pkg_name_clang}-tools-extra-devel
%license clang-tools-extra/LICENSE.TXT
%{install_includedir}/clang-tidy/

%files -n git-clang-format%{pkg_suffix}
%license clang/LICENSE.TXT
%{install_bindir}/git-clang-format
%if %{with compat_build}
%{_bindir}/git-clang-format-%{maj_ver}
%endif

%if %{without compat_build}
%files -n python%{python3_pkgversion}-clang
%license clang/LICENSE.TXT
%{python3_sitelib}/clang/
%endif

#endregion

#region COMPILER-RT files

%files -n %{pkg_name_compiler_rt}
%license compiler-rt/LICENSE.TXT
%ifarch x86_64 aarch64 riscv64
%{_prefix}/lib/clang/%{maj_ver}/bin/hwasan_symbolize
%endif
%{_prefix}/lib/clang/%{maj_ver}/include/fuzzer
%{_prefix}/lib/clang/%{maj_ver}/include/orc
%{_prefix}/lib/clang/%{maj_ver}/include/profile
%{_prefix}/lib/clang/%{maj_ver}/include/sanitizer
%{_prefix}/lib/clang/%{maj_ver}/include/xray

%{_prefix}/lib/clang/%{maj_ver}/share/*.txt

# Files that appear on all targets
%{_prefix}/lib/clang/%{maj_ver}/lib/%{compiler_rt_triple}/libclang_rt.*

%ifnarch s390x
%{_prefix}/lib/clang/%{maj_ver}/lib/%{compiler_rt_triple}/clang_rt.crtbegin.o
%{_prefix}/lib/clang/%{maj_ver}/lib/%{compiler_rt_triple}/clang_rt.crtend.o
%endif

%ifnarch %{ix86} s390x
%{_prefix}/lib/clang/%{maj_ver}/lib/%{compiler_rt_triple}/liborc_rt.a
%endif

# Additional symlink if two triples are in use.
%if "%{llvm_triple}" != "%{compiler_rt_triple}"
%{_prefix}/lib/clang/%{maj_ver}/lib/%{llvm_triple}
%endif

#endregion

#region OPENMP files

%files -n %{pkg_name_libomp}
%license openmp/LICENSE.TXT
%{install_libdir}/libomp.so
%{install_libdir}/libompd.so
%{install_libdir}/libarcher.so
%ifnarch %{ix86}
# libomptarget is not supported on 32-bit systems.
# s390x does not support the offloading plugins.
%{install_libdir}/libomptarget.so.%{so_suffix}
%endif

%files -n %{pkg_name_libomp}-devel
%license openmp/LICENSE.TXT
%{_prefix}/lib/clang/%{maj_ver}/include/omp.h
%{_prefix}/lib/clang/%{maj_ver}/include/ompx.h
%{_prefix}/lib/clang/%{maj_ver}/include/omp-tools.h
%{_prefix}/lib/clang/%{maj_ver}/include/ompt.h
%{_prefix}/lib/clang/%{maj_ver}/include/ompt-multiplex.h
%{install_libdir}/cmake/openmp/
%ifnarch %{ix86}
# libomptarget is not supported on 32-bit systems.
# s390x does not support the offloading plugins.
%{install_libdir}/libomptarget.devicertl.a
%{install_libdir}/libomptarget-amdgpu-*.bc
%{install_libdir}/libomptarget-nvptx-*.bc
%{install_libdir}/libomptarget.so
%endif

#endregion

#region LLD files

%files -n %{pkg_name_lld}
%license lld/LICENSE.TXT
%ghost %{_bindir}/ld
%{install_bindir}/lld
%{install_bindir}/lld-link
%{install_bindir}/ld.lld
%{install_bindir}/ld64.lld
%{install_bindir}/wasm-ld
%if %{without compat_build}
%{_mandir}/man1/ld.lld.1*
%else
%{_bindir}/lld%{exec_suffix}
%{_bindir}/lld-link%{exec_suffix}
%{_bindir}/ld.lld%{exec_suffix}
%{_bindir}/ld64.lld%{exec_suffix}
%{_bindir}/wasm-ld%{exec_suffix}
%endif

%files -n %{pkg_name_lld}-devel
%license lld/LICENSE.TXT
%{install_includedir}/lld
%{install_libdir}/liblldCOFF.so
%{install_libdir}/liblldCommon.so
%{install_libdir}/liblldELF.so
%{install_libdir}/liblldMachO.so
%{install_libdir}/liblldMinGW.so
%{install_libdir}/liblldWasm.so
%{install_libdir}/cmake/lld/

%files -n %{pkg_name_lld}-libs
%license lld/LICENSE.TXT
%{install_libdir}/liblldCOFF.so.*
%{install_libdir}/liblldCommon.so.*
%{install_libdir}/liblldELF.so.*
%{install_libdir}/liblldMachO.so.*
%{install_libdir}/liblldMinGW.so.*
%{install_libdir}/liblldWasm.so.*

#endregion

#region Toolset files
%if 0%{?rhel}
%files -n %{pkg_name_llvm}-toolset
%license LICENSE.TXT
%endif
#endregion

#region LLDB files
%if %{with lldb}
%files -n %{pkg_name_lldb}
%license lldb/LICENSE.TXT
%{install_bindir}/lldb*
# Usually, *.so symlinks are kept in devel subpackages. However, the python
# bindings depend on this symlink at runtime.
%{install_libdir}/liblldb*.so
%{install_libdir}/liblldb.so.*
%{install_libdir}/liblldbIntelFeatures.so.*

%files -n %{pkg_name_lldb}-devel
%{install_includedir}/lldb

%files -n python%{python3_pkgversion}-lldb
%{python3_sitearch}/lldb
%endif
#endregion
