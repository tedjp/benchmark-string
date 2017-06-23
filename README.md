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
    2017-06-23 14:07:32
    -------------------------------------------------------------------
    Benchmark                            Time           CPU Iterations
    -------------------------------------------------------------------
    BM_constexpr_version                 4 ns          4 ns  161956705
    BM_constexpr_lookuptable             4 ns          4 ns  189888838
    BM_lookuptable_fast                  3 ns          3 ns  228398394
    BM_lookuptable_fast_inline           2 ns          2 ns  380867112
    BM_lookuptable_string                7 ns          7 ns   98330688
    BM_lookuptable_string_v2             9 ns          9 ns   77897460
    BM_lookuptable_string_v3             9 ns          9 ns   77926789
    BM_lookuptable_string_v3b            9 ns          9 ns   77906011
    BM_lookuptable_string_v4             4 ns          4 ns  163726662
    BM_string_direct                     2 ns          2 ns  380637077
    BM_string_direct_noinline            9 ns          9 ns   78401115
    BM_lookup256                         6 ns          6 ns  125625413
    BM_lookup256_direct                  7 ns          7 ns  102880619
    BM_lookup256Digits                   9 ns          9 ns   75783416
    BM_lookup256Digits_direct            7 ns          7 ns  102897115
    BM_lookup256HexDigits                3 ns          3 ns  248603557
    BM_lookup256HexDigitsInline          2 ns          2 ns  380661413
    BM_snprintf_version                 69 ns         69 ns    9995511
    BM_snprintf_string                  68 ns         68 ns   10194407
    BM_fmt_version                      54 ns         54 ns   12820814
    BM_fmt_braces                       49 ns         49 ns   14301296
    BM_stringstream                    551 ns        551 ns    1249464


How to run this test
====================

Dependencies
------------

- [fmt](https://github.com/fmtlib/fmt)
- [Google benchmark](https://github.com/google/benchmark)

Update the paths to libfmt.a, libbenchmark.a & the benchmark include
directory in the `Makefile`.

`make run` to build & run the benchmarks.
