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
    2017-06-23 13:48:15
    ------------------------------------------------------------------
    Benchmark                           Time           CPU Iterations
    ------------------------------------------------------------------
    BM_constexpr_version               13 ns         13 ns   52804596
    BM_constexpr_lookuptable           14 ns         14 ns   50653577
    BM_lookuptable_fast                 3 ns          3 ns  231107031
    BM_lookuptable_fast_inline          2 ns          2 ns  381351157
    BM_lookuptable_string              13 ns         13 ns   51645108
    BM_lookuptable_string_v2           14 ns         14 ns   51385126
    BM_lookuptable_string_v3           10 ns         10 ns   70737632
    BM_lookuptable_string_v3b          10 ns         10 ns   70749333
    BM_lookuptable_string_v4            4 ns          4 ns  163699393
    BM_string_direct                    9 ns          9 ns   75923238
    BM_string_direct_noinline          10 ns         10 ns   71162959
    BM_lookup256                        9 ns          9 ns   78598048
    BM_lookup256_direct                 8 ns          8 ns   90490319
    BM_lookup256Digits                  9 ns          9 ns   74773277
    BM_lookup256Digits_direct           8 ns          8 ns   90438880
    BM_snprintf_version                78 ns         78 ns    8852204
    BM_snprintf_string                 81 ns         81 ns    8560928
    BM_fmt_version                     57 ns         57 ns   12011347
    BM_fmt_braces                      53 ns         53 ns   13038189
    BM_stringstream                   551 ns        551 ns    1252955


How to run this test
====================

Dependencies
------------

- [fmt](https://github.com/fmtlib/fmt)
- [Google benchmark](https://github.com/google/benchmark)

Update the paths to libfmt.a, libbenchmark.a & the benchmark include
directory in the `Makefile`.

`make run` to build & run the benchmarks.
