#region LLVM files

%files -n %{pkg_name_llvm}
%license llvm/LICENSE.TXT
%exclude %{_mandir}/man1/llvm-config*
%{_mandir}/man1/*
%{_bindir}/*

%exclude %{_bindir}/llvm-config%{exec_suffix}
%exclude %{install_bindir}/llvm-config%{exec_suffix}-%{__isa_bits}

%if %{without compat_build}
%exclude %{_bindir}/llvm-config-%{maj_ver}
%exclude %{install_bindir}/llvm-config-%{maj_ver}-%{__isa_bits}
%exclude %{_bindir}/not
%exclude %{_bindir}/count
%exclude %{_bindir}/yaml-bench
%exclude %{_bindir}/lli-child-target
%exclude %{_bindir}/llvm-isel-fuzzer
%exclude %{_bindir}/llvm-opt-fuzzer
%{_datadir}/opt-viewer
%else
%{install_bindir}
%endif

%files -n %{pkg_name_llvm}-libs
%license llvm/LICENSE.TXT
%{install_libdir}/libLLVM-%{maj_ver}%{?llvm_snapshot_version_suffix:%{llvm_snapshot_version_suffix}}.so
%if %{without compat_build}
%if %{with gold}
%{_libdir}/LLVMgold.so
%{_libdir}/bfd-plugins/LLVMgold.so
%endif
%{_libdir}/libLLVM-%{maj_ver}.%{min_ver}*.so
%{_libdir}/libLTO.so*
%else
%config(noreplace) %{_sysconfdir}/ld.so.conf.d/%{pkg_name_llvm}-%{_arch}.conf
%if %{with gold}
%{_libdir}/%{pkg_name_clang}/lib/LLVMgold.so
%endif
%{install_libdir}/libLLVM-%{maj_ver}.%{min_ver}*.so
%{install_libdir}/libLTO.so*
%exclude %{install_libdir}/libLTO.so
%endif
%{install_libdir}/libRemarks.so*

%files -n %{pkg_name_llvm}-devel
%license llvm/LICENSE.TXT

%ghost %{_bindir}/llvm-config%{exec_suffix}
%{install_bindir}/llvm-config%{exec_suffix}-%{__isa_bits}
%{_mandir}/man1/llvm-config*

%{install_includedir}/llvm
%{install_includedir}/llvm-c
%{install_libdir}/libLLVM.so
%{install_libdir}/cmake/llvm
%if %{without compat_build}
%{install_bindir}/llvm-config-%{maj_ver}-%{__isa_bits}
%ghost %{_bindir}/llvm-config-%{maj_ver}
%else
%{pkg_includedir}/llvm
%{pkg_includedir}/llvm-c
%{install_libdir}/libLTO.so
%endif

%files -n %{pkg_name_llvm}-doc
%license llvm/LICENSE.TXT
%doc %{_pkgdocdir}/html

%files -n %{pkg_name_llvm}-static
%license llvm/LICENSE.TXT
%{install_libdir}/*.a
%if %{without compat_build}
%exclude %{install_libdir}/libLLVMTestingSupport.a
%exclude %{install_libdir}/libLLVMTestingAnnotations.a
%exclude %{install_libdir}/libllvm_gtest.a
%exclude %{install_libdir}/libllvm_gtest_main.a
%endif

%files -n %{pkg_name_llvm}-cmake-utils
%license llvm/LICENSE.TXT
%{pkg_datadir}/llvm/cmake

%if %{without compat_build}

%files -n %{pkg_name_llvm}-test
%license llvm/LICENSE.TXT
%{_bindir}/not
%{_bindir}/count
%{_bindir}/yaml-bench
%{_bindir}/lli-child-target
%{_bindir}/llvm-isel-fuzzer
%{_bindir}/llvm-opt-fuzzer

%files -n %{pkg_name_llvm}-googletest
%license llvm/LICENSE.TXT
%{install_libdir}/libLLVMTestingSupport.a
%{install_libdir}/libLLVMTestingAnnotations.a
%{install_libdir}/libllvm_gtest.a
%{install_libdir}/libllvm_gtest_main.a
%{install_includedir}/llvm-gtest
%{install_includedir}/llvm-gmock

%endif

#endregion

#region CLANG files

%if %{without compat_build}
%files -n %{pkg_name_clang}
%license clang/LICENSE.TXT
%{_bindir}/clang
%{_bindir}/clang++
%{_bindir}/clang-%{maj_ver}
%{_bindir}/clang++-%{maj_ver}
%{_bindir}/clang-cl
%{_bindir}/clang-cpp
%{_mandir}/man1/clang.1.gz
%{_mandir}/man1/clang++.1.gz
%{_mandir}/man1/clang-%{maj_ver}.1.gz
%{_mandir}/man1/clang++-%{maj_ver}.1.gz
%endif

%files -n %{pkg_name_clang}-libs
%{install_prefix}/lib/clang/%{maj_ver}/include/*
%{install_libdir}/*.so.*

%files -n %{pkg_name_clang}-devel
%if %{without compat_build}
%{_libdir}/*.so
%{_includedir}/clang/
%{_includedir}/clang-c/
%{_libdir}/cmake/*
%{_bindir}/clang-tblgen
%dir %{_datadir}/clang/
%{_rpmmacrodir}/macros.%{pkg_name_clang}
%else
%{install_libdir}/*.so
%{pkg_includedir}/clang/
%{pkg_includedir}/clang-c/
%{install_libdir}/cmake/
%endif

%files -n %{pkg_name_clang}-resource-filesystem
%dir %{install_libdir}/clang/
%dir %{install_libdir}/clang/%{maj_ver}/
%dir %{install_libdir}/clang/%{maj_ver}/include/
%dir %{install_libdir}/clang/%{maj_ver}/lib/
%dir %{install_libdir}/clang/%{maj_ver}/share/

%if %{without compat_build}
%files -n %{pkg_name_clang}-analyzer
%{_bindir}/scan-view
%{_bindir}/scan-build
%{_bindir}/analyze-build
%{_bindir}/intercept-build
%{_bindir}/scan-build-py
%{_libexecdir}/ccc-analyzer
%{_libexecdir}/c++-analyzer
%{_libexecdir}/analyze-c++
%{_libexecdir}/analyze-cc
%{_libexecdir}/intercept-c++
%{_libexecdir}/intercept-cc
%{_datadir}/scan-view/
%{_datadir}/scan-build/
%{_mandir}/man1/scan-build.1.*
%{python3_sitelib}/libear
%{python3_sitelib}/libscanbuild


%files -n %{pkg_name_clang}-tools-extra
%{_bindir}/amdgpu-arch
%{_bindir}/clang-apply-replacements
%{_bindir}/clang-change-namespace
%{_bindir}/clang-check
%{_bindir}/clang-doc
%{_bindir}/clang-extdef-mapping
%{_bindir}/clang-format
%{_bindir}/clang-include-cleaner
%{_bindir}/clang-include-fixer
%{_bindir}/clang-move
%{_bindir}/clang-offload-bundler
%{_bindir}/clang-offload-packager
%{_bindir}/clang-linker-wrapper
%{_bindir}/clang-pseudo
%{_bindir}/clang-query
%{_bindir}/clang-refactor
%{_bindir}/clang-rename
%{_bindir}/clang-reorder-fields
%{_bindir}/clang-repl
%{_bindir}/clang-scan-deps
%{_bindir}/clang-tidy
%{_bindir}/clangd
%{_bindir}/diagtool
%{_bindir}/hmaptool
%{_bindir}/nvptx-arch
%{_bindir}/pp-trace
%{_bindir}/c-index-test
%{_bindir}/find-all-symbols
%{_bindir}/modularize
%{_bindir}/clang-format-diff
%{_mandir}/man1/diagtool.1.gz
%{_emacs_sitestartdir}/clang-format.el
%{_emacs_sitestartdir}/clang-rename.el
%{_emacs_sitestartdir}/clang-include-fixer.el
%{_datadir}/clang/clang-format.py*
%{_datadir}/clang/clang-format-diff.py*
%{_datadir}/clang/clang-include-fixer.py*
%{_datadir}/clang/clang-tidy-diff.py*
%{_bindir}/run-clang-tidy
%{_datadir}/clang/run-find-all-symbols.py*
%{_datadir}/clang/clang-rename.py*

%files -n %{pkg_name_clang}-tools-extra-devel
%{_includedir}/clang-tidy/

%files -n git-clang-format
%{_bindir}/git-clang-format

%files -n python3-clang
%{python3_sitelib}/clang/
%endif

#endregion

#region COMPILER-RT files

%if %{without compat_build}

%files -n %{pkg_name_compiler_rt}
%license compiler-rt/LICENSE.TXT
%ifarch x86_64 aarch64
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
%{_libdir}/libomptarget.rtl.%{libomp_arch}.so.%{so_suffix}
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
%{_libdir}/libomptarget.rtl.%{libomp_arch}.so
%endif
%{_libdir}/libomptarget.devicertl.a
%{_libdir}/libomptarget-amdgpu-*.bc
%{_libdir}/libomptarget-nvptx-*.bc
%{_libdir}/libomptarget.so
%endif

%endif

#endregion
