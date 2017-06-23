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
    2017-06-23 12:38:26
    ------------------------------------------------------------------
    Benchmark                           Time           CPU Iterations
    ------------------------------------------------------------------
    BM_constexpr_version               14 ns         14 ns   49969662
    BM_constexpr_lookuptable           14 ns         14 ns   51244515
    BM_lookuptable_fast                 3 ns          3 ns  224502718
    BM_lookuptable_fast_inline          2 ns          2 ns  380597469
    BM_lookuptable_string              14 ns         14 ns   50369353
    BM_lookuptable_string_v2           14 ns         14 ns   51408759
    BM_lookuptable_string_v3           10 ns         10 ns   70245084
    BM_lookuptable_string_v3b          10 ns         10 ns   70847817
    BM_lookuptable_string_v4            5 ns          5 ns  150748477
    BM_string_direct                    9 ns          9 ns   75267173
    BM_snprintf_version                79 ns         79 ns    8779360
    BM_snprintf_string                 80 ns         80 ns    8407058
    BM_fmt_version                     58 ns         58 ns   12013242
    BM_fmt_braces                      53 ns         53 ns   13116101
    BM_stringstream                   548 ns        548 ns    1246907


How to run this test
====================

Dependencies
------------

- [fmt](https://github.com/fmtlib/fmt)
- [Google benchmark](https://github.com/google/benchmark)

Update the paths to libfmt.a, libbenchmark.a & the benchmark include
directory in the `Makefile`.

`make run` to build & run the benchmarks.
