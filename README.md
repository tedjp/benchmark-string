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
    2017-06-23 13:35:32
    ------------------------------------------------------------------
    Benchmark                           Time           CPU Iterations
    ------------------------------------------------------------------
    BM_constexpr_version               13 ns         13 ns   52349021
    BM_constexpr_lookuptable           13 ns         13 ns   45261803
    BM_lookuptable_fast                 3 ns          3 ns  230050764
    BM_lookuptable_fast_inline          2 ns          2 ns  380388925
    BM_lookuptable_string              14 ns         14 ns   51484175
    BM_lookuptable_string_v2           14 ns         14 ns   51216081
    BM_lookuptable_string_v3           10 ns         10 ns   70966107
    BM_lookuptable_string_v3b          10 ns         10 ns   70923088
    BM_lookuptable_string_v4            4 ns          4 ns  162890586
    BM_string_direct                    9 ns          9 ns   75243324
    BM_string_direct_noinline          10 ns         10 ns   71001996
    BM_lookup256                        8 ns          8 ns   83206006
    BM_lookup256_direct                 7 ns          7 ns   96494529
    BM_snprintf_version                80 ns         79 ns    8629455
    BM_snprintf_string                 80 ns         80 ns    8681422
    BM_fmt_version                     57 ns         57 ns   12025920
    BM_fmt_braces                      54 ns         54 ns   12683390
    BM_stringstream                   548 ns        548 ns    1273815


How to run this test
====================

Dependencies
------------

- [fmt](https://github.com/fmtlib/fmt)
- [Google benchmark](https://github.com/google/benchmark)

Update the paths to libfmt.a, libbenchmark.a & the benchmark include
directory in the `Makefile`.

`make run` to build & run the benchmarks.
