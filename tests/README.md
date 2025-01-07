# Gating testplans for LLVM

The tests for LLVM are in separate repos:

* llvm:  https://src.fedoraproject.org/tests/llvm.git/
* clang:  https://src.fedoraproject.org/tests/clang.git/
* compiler-rt:  https://src.fedoraproject.org/tests/compiler-rt.git/
* libomp:  https://src.fedoraproject.org/tests/libomp.git/
* python-lit:  https://src.fedoraproject.org/tests/python-lit.git/
* lld:  https://src.fedoraproject.org/tests/lld.git/
* lldb:  https://src.fedoraproject.org/tests/lldb.git/

This directory should contain only fmf plans (such as build-gating.fmf) which import
the tests from the tests repo. This can be done using the "url" parameter of the
plan's "discover" step. Reference: https://tmt.readthedocs.io/en/stable/spec/plans.html#fmf
