# TODO(kkleine): Instead of deleting test files we should mark them as expected
# to fail. See https://llvm.org/docs/CommandGuide/lit.html#cmdoption-lit-xfail

%ifarch ppc64le
# TODO: Re-enable when ld.gold fixed its internal error.
rm llvm/test/tools/gold/PowerPC/mtriple.ll
%endif

# non reproducible errors
# TODO(kkleine): Add this to XFAIL instead?
rm llvm/test/tools/dsymutil/X86/swift-interface.test

%if %{with check}

cd llvm

#region Helper functions
# Call this function before setting up a next component to test.
function reset_test_opts()
{
    # Some libraries will not be found if we don't set this
    export LD_LIBRARY_PATH="%{buildroot}/%{install_libdir}:%{buildroot}/%{_libdir}";

    # See https://llvm.org/docs/CommandGuide/lit.html#general-options
    export LIT_OPTS="-vv"
    
    # Set to mark tests as expected to fail.
    # See https://llvm.org/docs/CommandGuide/lit.html#cmdoption-lit-xfail
    unset LIT_XFAIL
    
    # Set to mark tests to not even run.
    # See https://llvm.org/docs/CommandGuide/lit.html#cmdoption-lit-filter-out
    # Unfortunately LIT_FILTER_OUT is not accepting a list but a regular expression.
    # To make this easily maintainable, we'll create an associate array in bash,
    # to which you can append and later we'll join that array and escape dots (".")
    # in your test paths. The following line resets this array.
    # See also the function "test_list_to_regex".
    test_list_filter_out=()
    unset LIT_FILTER_OUT

    # Set for filtering out unit tests.
    # See http://google.github.io/googletest/advanced.html#running-a-subset-of-the-tests    
    unset GTEST_FILTER
}

# Convert array of test names into a regex.
# Call this function with an indexed array.
#
# Example:
#
#    testlist=()
#    testlist+=("foo")
#    testlist+=("bar")
#    export LIT_FILTER_OUT=$(test_list_to_regex testlist)
#
# Then $LIT_FILTER_OUT should evaluate to: (foo|bar)
function test_list_to_regex()
{
    local -n arr=$1 
    # Prepare LIT_FILTER_OUT regex from index bash array
    # Join each element with a pipe symbol (regex for "or")
    arr=$(printf "|%s" "${arr[@]}")
    # Remove the initial pipe symbol
    arr=${arr:1}
    # Properly escape path dots (".") for use in regular expression
    arr=$(echo $arr | sed 's/\./\\./g')
    # Add enclosing parenthesis
    echo "($arr)"
}
#endregion

#region Test LLVM
reset_test_opts
# Xfail testing of update utility tools
export LIT_XFAIL="tools/UpdateTestChecks"
%cmake_build --target check-llvm 
#endregion

#region Test CLANG
reset_test_opts
export LIT_XFAIL="$LIT_XFAIL;clang/test/CodeGen/profile-filter.c"
%cmake_build --target check-clang
#endregion

#region Test Clang Tools
reset_test_opts
%ifarch %ix86
# Clang Tools :: clang-tidy/checkers/altera/struct-pack-align.cpp
export LIT_XFAIL="$LIT_XFAIL;clang-tidy/checkers/altera/struct-pack-align.cpp"
%endif
%cmake_build --target check-clang-tools
#endregion

#region Test OPENMP
reset_test_opts

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
export LIT_XFAIL="api_tests/test_ompd_get_curr_task_handle.c"
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
test_list_filter_out+=("libomp :: ompt/teams/distribute_dispatch.c")
test_list_filter_out+=("libomp :: affinity/kmp-abs-hw-subset.c")
test_list_filter_out+=("libarcher :: races/task-taskgroup-unrelated.c")

%ifarch ppc64le s390x %ix86
# These tests fail more often than not, but not always.
test_list_filter_out+=("libomp :: worksharing/for/omp_collapse_many_GELTGT_int.c")
test_list_filter_out+=("libomp :: worksharing/for/omp_collapse_many_GTGEGT_int.c")
test_list_filter_out+=("libomp :: worksharing/for/omp_collapse_many_LTLEGE_int.c")
test_list_filter_out+=("libomp :: worksharing/for/omp_collapse_one_int.c")
%endif

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
%endif

export LIT_FILTER_OUT=$(test_list_to_regex test_list_filter_out)

%cmake_build --target check-openmp
#endregion

# Don't run LLDB tests on s390x because more than 150 tests are failing there
%ifnarch s390x
## TODO(kkleine): Come back and re-enable testing for LLDB
## #region LLDB unit tests
## reset_test_opts
## %%cmake_build --target check-lldb-unit
## #endregion
## 
## #region LLDB SB API tests
## reset_test_opts
## %%cmake_build --target check-lldb-api
## #endregion
## 
## #region LLDB shell tests
## reset_test_opts
## %%cmake_build --target check-lldb-shell
## #endregion
%endif


#region Test LLD
reset_test_opts
%cmake_build --target check-lld
#endregion

%endif

%if %{with snapshot_build}
# Do this here instead of in install so the check targets are also included.
cp %{_vpath_builddir}/.ninja_log %{buildroot}%{pkg_datadir}
%endif
