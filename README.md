Experimenting with different ways to produce a percent-encoded hex-encoding
of a char in C++.

There are generally two ways that the string is returned: as a two-byte
structure, or as a temporary string object.

Findings
========

- The quickest way to create & set a short, fixed-length C++ string is to
  use the braces initializer and direct character access.
  In particular, it's quicker than calling `string::reserve()` with a small
  constant value.
- Inlining makes things a lot faster.
- Including a default case in the switch statement (that is never used) is
  *twice as fast* as omitting it (branch predictor miss?).
- Returning a temporary string object is not *too* bad — takes about twice
  as long — but provides the nicest API.
- [fmt](https://github.com/fmtlib/fmt) is faster than `snprintf` in GNU libc.


Results
=======

    Run on (8 X 3300 MHz CPU s)
    2017-06-23 12:43:01
    ------------------------------------------------------------------
    Benchmark                           Time           CPU Iterations
    ------------------------------------------------------------------
    BM_constexpr_version               14 ns         14 ns   43028506
    BM_constexpr_lookuptable           14 ns         14 ns   49415430
    BM_lookuptable_fast                 3 ns          3 ns  232228673
    BM_lookuptable_fast_inline          2 ns          2 ns  381499205
    BM_lookuptable_string              14 ns         14 ns   50605648
    BM_lookuptable_string_v2           14 ns         14 ns   50584576
    BM_lookuptable_string_v3           10 ns         10 ns   68855632
    BM_lookuptable_string_v3b          10 ns         10 ns   69858716
    BM_lookuptable_string_v4            5 ns          5 ns  151546880
    BM_string_direct                    9 ns          9 ns   75860588
    BM_string_direct_noinline          10 ns         10 ns   68868896
    BM_snprintf_version                79 ns         79 ns    8840384
    BM_snprintf_string                 87 ns         87 ns    7968288
    BM_fmt_version                     57 ns         57 ns   11939420
    BM_fmt_braces                      54 ns         54 ns   12660690
    BM_stringstream                   553 ns        553 ns    1242517


How to run this test
====================

Dependencies
------------

- [fmt](https://github.com/fmtlib/fmt)
- [Google benchmark](https://github.com/google/benchmark)

Update the paths to libfmt.a, libbenchmark.a & the benchmark include
directory in the `Makefile`.

`make run` to build & run the benchmarks.
