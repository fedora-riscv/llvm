#region LLVM files

%files -n %{pkg_name_llvm}
%license llvm/LICENSE.TXT
%exclude %{_mandir}/man1/llvm-config*
%{_mandir}/man1/*
%{install_bindir}/*
%if %{with compat_build}
# This is for all the binaries with the version suffix.
%{_bindir}/*%{exec_suffix}
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

%ghost %{_bindir}/llvm-config%{exec_suffix}
%{install_bindir}/llvm-config%{exec_suffix}-%{__isa_bits}
%{_mandir}/man1/llvm-config*

%{install_includedir}/llvm
%{install_includedir}/llvm-c
%{install_libdir}/libLLVM.so
%{install_libdir}/cmake/llvm
%{install_bindir}/llvm-config-%{maj_ver}-%{__isa_bits}
%ghost %{_bindir}/llvm-config-%{maj_ver}

%files -n %{pkg_name_llvm}-doc
%license llvm/LICENSE.TXT
%doc %{_pkgdocdir}/html

%files -n %{pkg_name_llvm}-static
%license llvm/LICENSE.TXT
%{install_libdir}/*.a
%exclude %{install_libdir}/libLLVMTestingSupport.a
%exclude %{install_libdir}/libLLVMTestingAnnotations.a
%exclude %{install_libdir}/libllvm_gtest.a
%exclude %{install_libdir}/libllvm_gtest_main.a

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

%files -n %{pkg_name_llvm}-googletest
%license llvm/LICENSE.TXT
%{install_libdir}/libLLVMTestingSupport.a
%{install_libdir}/libLLVMTestingAnnotations.a
%{install_libdir}/libllvm_gtest.a
%{install_libdir}/libllvm_gtest_main.a
%{install_includedir}/llvm-gtest
%{install_includedir}/llvm-gmock

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
%{_sysconfdir}/%{pkg_name_clang}/clang.cfg
%if %{without compat_build}
%{_mandir}/man1/clang.1.gz
%{_mandir}/man1/clang++.1.gz
%{_mandir}/man1/clang-%{maj_ver}.1.gz
%{_mandir}/man1/clang++-%{maj_ver}.1.gz
%else
%{_bindir}/clang-%{maj_ver}
%{_bindir}/clang++-%{maj_ver}
%{_bindir}/clang-cl-%{maj_ver}
%{_bindir}/clang-cpp-%{maj_ver}
%endif

%files -n %{pkg_name_clang}-libs
%{install_prefix}/lib/clang/%{maj_ver}/include/*
%{install_libdir}/*.so.*
%if 0%{?fedora} == 38
%{_sysconfdir}/%{name}/%{_target_platform}.cfg
%endif

%files -n %{pkg_name_clang}-devel
%{install_libdir}/*.so
%{install_includedir}/clang/
%{install_includedir}/clang-c/
%{install_libdir}/cmake/*
%{install_bindir}/clang-tblgen
%if %{with compat_build}
%{_bindir}/clang-tblgen-%{maj_ver}
%endif
%dir %{install_datadir}/clang/

%files -n %{pkg_name_clang}-resource-filesystem
%dir %{install_prefix}/lib/clang/
%dir %{install_prefix}/lib/clang/%{maj_ver}/
%ifarch x86_64 aarch64 %{ix86}
%dir %{install_prefix}/lib/clang/%{maj_ver}/bin/
%endif
%dir %{install_prefix}/lib/clang/%{maj_ver}/include/
%dir %{install_prefix}/lib/clang/%{maj_ver}/lib/
%dir %{install_prefix}/lib/clang/%{maj_ver}/share/
%if %{without compat_build}
%{_rpmmacrodir}/macros.%{pkg_name_clang}
%endif

%files -n %{pkg_name_clang}-analyzer
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
%if %{without compat_build}
%{_mandir}/man1/scan-build.1.*
%{python3_sitelib}/libear
%{python3_sitelib}/libscanbuild
%endif


%files -n %{pkg_name_clang}-tools-extra
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
%{_mandir}/man1/diagtool.1.gz
%{_emacs_sitestartdir}/clang-format.el
%{_emacs_sitestartdir}/clang-rename.el
%{_emacs_sitestartdir}/clang-include-fixer.el
%endif
%{install_datadir}/clang/clang-format.py*
%{install_datadir}/clang/clang-format-diff.py*
%{install_datadir}/clang/clang-include-fixer.py*
%{install_datadir}/clang/clang-tidy-diff.py*
%{install_datadir}/clang/run-find-all-symbols.py*
%{install_datadir}/clang/clang-rename.py*


%files -n %{pkg_name_clang}-tools-extra-devel
%{install_includedir}/clang-tidy/

%files -n git-clang-format
%{install_bindir}/git-clang-format
%if %{with compat_build}
%{_bindir}/git-clang-format-%{maj_ver}
%endif

%if %{without compat_build}
%files -n python3-clang
%{python3_sitelib}/clang/
%endif

#endregion

#region COMPILER-RT files

%if %{without compat_build}

%files -n %{pkg_name_compiler_rt}
%license compiler-rt/LICENSE.TXT
%ifarch x86_64 aarch64 %{ix86}
%{_prefix}/lib/clang/%{maj_ver}/bin/*
%endif
%{_prefix}/lib/clang/%{maj_ver}/include/*
%{_prefix}/lib/clang/%{maj_ver}/lib/*
%{_prefix}/lib/clang/%{maj_ver}/share/*
#%ifarch x86_64 aarch64
#{_bindir}/hwasan_symbolize
#%endif

%endif

#endregion

#region OPENMP files

%if %{without compat_build}

%files -n %{pkg_name_libomp}
%license openmp/LICENSE.TXT
%{_libdir}/libomp.so
%{_libdir}/libompd.so
%ifnarch %{arm}
%{_libdir}/libarcher.so
%endif
%ifnarch %{ix86} %{arm}
# libomptarget is not supported on 32-bit systems.
# s390x does not support the offloading plugins.
%ifnarch s390x
%{_libdir}/libomptarget.rtl.amdgpu.so.%{so_suffix}
%{_libdir}/libomptarget.rtl.cuda.so.%{so_suffix}
%{_libdir}/libomptarget.rtl.host.so.%{so_suffix}
%endif
%{_libdir}/libomptarget.so.%{so_suffix}
%endif

%files -n %{pkg_name_libomp}-devel
%{_prefix}/lib/clang/%{maj_ver}/include/omp.h
%{_prefix}/lib/clang/%{maj_ver}/include/ompx.h
%ifnarch %{arm}
%{_prefix}/lib/clang/%{maj_ver}/include/omp-tools.h
%{_prefix}/lib/clang/%{maj_ver}/include/ompt.h
%{_prefix}/lib/clang/%{maj_ver}/include/ompt-multiplex.h
%endif
%{_libdir}/cmake/openmp/FindOpenMPTarget.cmake
%ifnarch %{ix86} %{arm}
# libomptarget is not supported on 32-bit systems.
# s390x does not support the offloading plugins.
%ifnarch s390x
%{_libdir}/libomptarget.rtl.amdgpu.so
%{_libdir}/libomptarget.rtl.cuda.so
%{_libdir}/libomptarget.rtl.host.so
%endif
%{_libdir}/libomptarget.devicertl.a
%{_libdir}/libomptarget-amdgpu-*.bc
%{_libdir}/libomptarget-nvptx-*.bc
%{_libdir}/libomptarget.so
%endif

%endif

#endregion

#region LLD files

%files -n %{pkg_name_lld}
%license lld/LICENSE.TXT
%ghost %{_bindir}/ld
%{install_bindir}/lld*
%{install_bindir}/ld.lld
%{install_bindir}/ld64.lld
%{install_bindir}/wasm-ld
%if %{without compat_build}
%{_mandir}/man1/ld.lld.1*
%else
%{_bindir}/*-%{maj_ver}
%endif

%files -n %{pkg_name_lld}-devel
%{install_includedir}/lld
%{install_libdir}/liblld*.so
%{install_libdir}/cmake/lld/

%files -n %{pkg_name_lld}-libs
%{install_libdir}/liblld*.so.*

#endregion
