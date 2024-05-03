# TODO(kkleine): Instead of deleting test files we should mark them as expected
# to fail. See https://llvm.org/docs/CommandGuide/lit.html#cmdoption-lit-xfail

# Disable check section on arm due to some kind of memory related failure.
# Possibly related to https://bugzilla.redhat.com/show_bug.cgi?id=1920183
%ifnarch %{arm}

# TODO: Fix the failures below
%ifarch %{arm}
rm llvm/test/tools/llvm-readobj/ELF/dependent-libraries.test
%endif
%ifarch ppc64le
# TODO: Re-enable when ld.gold fixed its internal error.
rm llvm/test/tools/gold/PowerPC/mtriple.ll
%endif

# non reproducible errors
# TODO(kkleine): Add this to XFAIL instead?
rm llvm/test/tools/dsymutil/X86/swift-interface.test

%if %{with check}

# See https://llvm.org/docs/CommandGuide/lit.html#cmdoption-lit-xfail
export LIT_XFAIL=""

# See https://llvm.org/docs/CommandGuide/lit.html#cmdoption-lit-filter-out
# Unfortunately LIT_FILTER_OUT is not accepting a list but a regular expression.
# To make this easily maintainable, we'll create an associate array in bash,
# to which you can append and later we'll join that array and escpate dots (".")
# in your test paths.
declare -a filter_out_tests

#region LLVM xfail tests 

# Xfail testing of update utility tools
# LLVM :: 
export LIT_XFAIL="$LIT_XFAIL;tools/UpdateTestChecks"

#endregion

#region CLANG xfail tests

# Clang :: 
export LIT_XFAIL="$LIT_XFAIL;clang/test/CodeGen/profile-filter.c"

#endregion

#region OPENMP xfail tests

# TODO(kkleine): OpenMP tests are currently not run on rawhide (see https://bugzilla.redhat.com/show_bug.cgi?id=2252966):
#
# + /usr/bin/cmake --build redhat-linux-build -j6 --verbose --target check-openmp
# Change Dir: '/builddir/build/BUILD/openmp-17.0.6.src/redhat-linux-build'
# Run Build Command(s): /usr/bin/ninja-build -v -j 6 check-openmp
# [1/1] cd /builddir/build/BUILD/openmp-17.0.6.src/redhat-linux-build && /usr/bin/cmake -E echo check-openmp\ does\ nothing,\ dependencies\ not\ found.
# 
# We're marking the tests that are failing with the follwing error as expected to fail (XFAIL):
#
#   gdb.error: No symbol "ompd_sizeof____kmp_gtid" in current context
#
# NOTE: It could be a different symbol in some tests.
export LIT_XFAIL="$LIT_XFAIL;api_tests/test_ompd_get_curr_task_handle.c"
export LIT_XFAIL="$LIT_XFAIL;api_tests/test_ompd_get_enclosing_parallel_handle.c"
export LIT_XFAIL="$LIT_XFAIL;api_tests/test_ompd_get_generating_task_handle.c"
export LIT_XFAIL="$LIT_XFAIL;api_tests/test_ompd_get_icv_from_scope.c"
export LIT_XFAIL="$LIT_XFAIL;api_tests/test_ompd_get_scheduling_task_handle.c"
export LIT_XFAIL="$LIT_XFAIL;api_tests/test_ompd_get_state.c"
export LIT_XFAIL="$LIT_XFAIL;api_tests/test_ompd_get_task_frame.c"
export LIT_XFAIL="$LIT_XFAIL;api_tests/test_ompd_get_task_function.c"
export LIT_XFAIL="$LIT_XFAIL;api_tests/test_ompd_get_task_in_parallel.c"
export LIT_XFAIL="$LIT_XFAIL;api_tests/test_ompd_get_task_parallel_handle.c"
export LIT_XFAIL="$LIT_XFAIL;api_tests/test_ompd_get_thread_id.c"
export LIT_XFAIL="$LIT_XFAIL;api_tests/test_ompd_get_thread_in_parallel.c"
export LIT_XFAIL="$LIT_XFAIL;api_tests/test_ompd_parallel_handle_compare.c"
export LIT_XFAIL="$LIT_XFAIL;api_tests/test_ompd_rel_parallel_handle.c"
export LIT_XFAIL="$LIT_XFAIL;api_tests/test_ompd_rel_task_handle.c"
export LIT_XFAIL="$LIT_XFAIL;api_tests/test_ompd_rel_thread_handle.c"
export LIT_XFAIL="$LIT_XFAIL;api_tests/test_ompd_task_handle_compare.c"
export LIT_XFAIL="$LIT_XFAIL;api_tests/test_ompd_thread_handle_compare.c"
export LIT_XFAIL="$LIT_XFAIL;openmp_examples/ompd_icvs.c"
export LIT_XFAIL="$LIT_XFAIL;api_tests/test_ompd_get_curr_parallel_handle.c"
export LIT_XFAIL="$LIT_XFAIL;api_tests/test_ompd_get_display_control_vars.c"
export LIT_XFAIL="$LIT_XFAIL;api_tests/test_ompd_get_thread_handle.c"

# The following test is flaky and we'll filter it out
filter_out_tests+=("libomp :: ompt/teams/distribute_dispatch.c")

# The following tests seem pass on ppc64le and x86_64 and aarch64 only:
%ifnarch ppc64le x86_64 s390x aarch64
# Passes on ppc64le: 
#   libomptarget :: powerpc64le-ibm-linux-gnu :: mapping/target_derefence_array_pointrs.cpp
#   libomptarget :: powerpc64le-ibm-linux-gnu-LTO :: mapping/target_derefence_array_pointrs.cpp
# Passes on x86_64:
#   libomptarget :: x86_64-pc-linux-gnu :: mapping/target_derefence_array_pointrs.cpp
#   libomptarget :: x86_64-pc-linux-gnu-LTO :: mapping/target_derefence_array_pointrs.cpp
# Passes on s390x:
#   libomptarget :: s390x-ibm-linux-gnu :: mapping/target_derefence_array_pointrs.cpp
#   libomptarget :: s390x-ibm-linux-gnu-LTO :: mapping/target_derefence_array_pointrs.cpp
export LIT_XFAIL="$LIT_XFAIL;mapping/target_derefence_array_pointrs.cpp" 
%endif

%ifnarch x86_64
# Passes on x86_64:
#   libomptarget :: x86_64-pc-linux-gnu :: api/ompx_3d.c
#   libomptarget :: x86_64-pc-linux-gnu :: api/ompx_3d.cpp
#   libomptarget :: x86_64-pc-linux-gnu-LTO :: api/ompx_3d.c
#   libomptarget :: x86_64-pc-linux-gnu-LTO :: api/ompx_3d.cpp
# libomptarget :: aarch64-unknown-linux-gnu :: 
export LIT_XFAIL="$LIT_XFAIL;api/ompx_3d.c" 
export LIT_XFAIL="$LIT_XFAIL;api/ompx_3d.cpp"
%endif

%ifarch %ix86
# Clang Tools :: clang-tidy/checkers/altera/struct-pack-align.cpp
export LIT_XFAIL="$LIT_XFAIL;clang-tidy/checkers/altera/struct-pack-align.cpp"
%endif

%ifarch ppc64le
export LIT_XFAIL="$LIT_XFAIL;barrier/barrier.c"
export LIT_XFAIL="$LIT_XFAIL;critical/critical.c"
export LIT_XFAIL="$LIT_XFAIL;critical/lock-nested.c"
export LIT_XFAIL="$LIT_XFAIL;critical/lock.c"
export LIT_XFAIL="$LIT_XFAIL;parallel/parallel-firstprivate.c"
export LIT_XFAIL="$LIT_XFAIL;parallel/parallel-nosuppression.c"
export LIT_XFAIL="$LIT_XFAIL;parallel/parallel-simple.c"
export LIT_XFAIL="$LIT_XFAIL;parallel/parallel-simple2.c"
export LIT_XFAIL="$LIT_XFAIL;races/critical-unrelated.c"
export LIT_XFAIL="$LIT_XFAIL;races/lock-nested-unrelated.c"
export LIT_XFAIL="$LIT_XFAIL;races/lock-unrelated.c"
export LIT_XFAIL="$LIT_XFAIL;races/parallel-simple.c"
export LIT_XFAIL="$LIT_XFAIL;races/task-dependency.c"
export LIT_XFAIL="$LIT_XFAIL;races/task-taskgroup-unrelated.c"
export LIT_XFAIL="$LIT_XFAIL;races/task-taskwait-nested.c"
export LIT_XFAIL="$LIT_XFAIL;races/task-two.c"
export LIT_XFAIL="$LIT_XFAIL;races/taskwait-depend.c"
export LIT_XFAIL="$LIT_XFAIL;reduction/parallel-reduction-nowait.c"
export LIT_XFAIL="$LIT_XFAIL;reduction/parallel-reduction.c"
export LIT_XFAIL="$LIT_XFAIL;task/omp_task_depend_all.c"
export LIT_XFAIL="$LIT_XFAIL;task/task-barrier.c"
export LIT_XFAIL="$LIT_XFAIL;task/task-create.c"
export LIT_XFAIL="$LIT_XFAIL;task/task-dependency.c"
export LIT_XFAIL="$LIT_XFAIL;task/task-taskgroup-nested.c"
export LIT_XFAIL="$LIT_XFAIL;task/task-taskgroup.c"
export LIT_XFAIL="$LIT_XFAIL;task/task-taskwait-nested.c"
export LIT_XFAIL="$LIT_XFAIL;task/task-taskwait.c"
export LIT_XFAIL="$LIT_XFAIL;task/task_early_fulfill.c"
export LIT_XFAIL="$LIT_XFAIL;task/task_late_fulfill.c"
export LIT_XFAIL="$LIT_XFAIL;task/taskwait-depend.c"
export LIT_XFAIL="$LIT_XFAIL;worksharing/ordered.c"
export LIT_XFAIL="$LIT_XFAIL;api/omp_dynamic_shared_memory.c"
export LIT_XFAIL="$LIT_XFAIL;jit/empty_kernel_lvl1.c"
export LIT_XFAIL="$LIT_XFAIL;jit/empty_kernel_lvl2.c"
export LIT_XFAIL="$LIT_XFAIL;jit/type_punning.c"
export LIT_XFAIL="$LIT_XFAIL;offloading/barrier_fence.c"
export LIT_XFAIL="$LIT_XFAIL;offloading/bug49334.cpp"
export LIT_XFAIL="$LIT_XFAIL;offloading/default_thread_limit.c"
export LIT_XFAIL="$LIT_XFAIL;offloading/ompx_bare.c"
export LIT_XFAIL="$LIT_XFAIL;offloading/ompx_coords.c"
export LIT_XFAIL="$LIT_XFAIL;offloading/ompx_saxpy_mixed.c"
export LIT_XFAIL="$LIT_XFAIL;offloading/small_trip_count.c"
export LIT_XFAIL="$LIT_XFAIL;offloading/small_trip_count_thread_limit.cpp"
export LIT_XFAIL="$LIT_XFAIL;offloading/spmdization.c"
export LIT_XFAIL="$LIT_XFAIL;offloading/target_critical_region.cpp"
export LIT_XFAIL="$LIT_XFAIL;offloading/thread_limit.c"
export LIT_XFAIL="$LIT_XFAIL;offloading/thread_state_1.c"
export LIT_XFAIL="$LIT_XFAIL;offloading/thread_state_2.c"
export LIT_XFAIL="$LIT_XFAIL;api/omp_dynamic_shared_memory.c"
export LIT_XFAIL="$LIT_XFAIL;jit/empty_kernel_lvl1.c"
export LIT_XFAIL="$LIT_XFAIL;jit/empty_kernel_lvl2.c"
export LIT_XFAIL="$LIT_XFAIL;jit/type_punning.c"
export LIT_XFAIL="$LIT_XFAIL;offloading/barrier_fence.c"
export LIT_XFAIL="$LIT_XFAIL;offloading/bug49334.cpp"
export LIT_XFAIL="$LIT_XFAIL;offloading/default_thread_limit.c"
export LIT_XFAIL="$LIT_XFAIL;offloading/ompx_bare.c"
export LIT_XFAIL="$LIT_XFAIL;offloading/ompx_coords.c"
export LIT_XFAIL="$LIT_XFAIL;offloading/ompx_saxpy_mixed.c"
export LIT_XFAIL="$LIT_XFAIL;offloading/small_trip_count.c"
export LIT_XFAIL="$LIT_XFAIL;offloading/small_trip_count_thread_limit.cpp"
export LIT_XFAIL="$LIT_XFAIL;offloading/spmdization.c"
export LIT_XFAIL="$LIT_XFAIL;offloading/target_critical_region.cpp"
export LIT_XFAIL="$LIT_XFAIL;offloading/thread_limit.c"
export LIT_XFAIL="$LIT_XFAIL;mapping/auto_zero_copy.cpp"
export LIT_XFAIL="$LIT_XFAIL;mapping/auto_zero_copy_globals.cpp"
export LIT_XFAIL="$LIT_XFAIL;offloading/workshare_chunk.c"
export LIT_XFAIL="$LIT_XFAIL;ompt/target_memcpy.c"
export LIT_XFAIL="$LIT_XFAIL;ompt/target_memcpy_emi.c"
%endif

%ifarch s390x ppc64le
export LIT_XFAIL="$LIT_XFAIL;offloading/thread_state_1.c"
export LIT_XFAIL="$LIT_XFAIL;offloading/thread_state_2.c"
export LIT_XFAIL="$LIT_XFAIL;worksharing/for/omp_collapse_many_GELTGT_int.c"
export LIT_XFAIL="$LIT_XFAIL;worksharing/for/omp_collapse_many_GTGEGT_int.c"
export LIT_XFAIL="$LIT_XFAIL;worksharing/for/omp_collapse_many_LTLEGE_int.c"
export LIT_XFAIL="$LIT_XFAIL;worksharing/for/omp_collapse_one_int.c"
%endif

#endregion

# Prepare LIT_FILTER_OUT regex from index bash array
# Join each element with a pipe symbol (regex for "or")
filter_out_tests=$(printf "|%s" "${filter_out_tests[@]}")
# Remove the initial pipe symbol
filter_out_tests=${filter_out_tests:1}
# Properly escape path dots (".") for use in regular expression 
filter_out_tests=$(echo $filter_out_tests | sed 's/\./\\./')
# Add enclosing parenthesis
export LIT_FILTER_OUT="($filter_out_tests)"


export LIT_OPTS="-vv"

export LD_LIBRARY_PATH="%{buildroot}/%{install_libdir}:%{buildroot}/%{_libdir}";

cd llvm
%cmake_build --target check-llvm check-clang check-lld

%endif

#region LLD

%if %{without compat_build}
%ldconfig_scriptlets libs
%endif

#endregion

%endif
