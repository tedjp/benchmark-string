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
    2017-06-23 12:08:42
    ------------------------------------------------------------------
    Benchmark                           Time           CPU Iterations
    ------------------------------------------------------------------
    BM_constexpr_version               13 ns         13 ns   52687225
    BM_constexpr_lookuptable           14 ns         14 ns   49417308
    BM_lookuptable_fast                 3 ns          3 ns  228489248
    BM_lookuptable_fast_inline          2 ns          2 ns  381032847
    BM_lookuptable_string              14 ns         14 ns   51630818
    BM_lookuptable_string_v2           14 ns         14 ns   51599368
    BM_lookuptable_string_v3           10 ns         10 ns   70479808
    BM_lookuptable_string_v3b          10 ns         10 ns   70702461
    BM_lookuptable_string_v4            5 ns          5 ns  150538971
    BM_snprintf_version                80 ns         80 ns    8676511
    BM_snprintf_string                 78 ns         78 ns    8862644
    BM_fmt_version                     57 ns         57 ns   12010787
    BM_fmt_braces                      54 ns         54 ns   12746910
    BM_stringstream                   531 ns        531 ns    1291741


How to run this test
====================

Dependencies
------------

- [fmt](https://github.com/fmtlib/fmt)
- [Google benchmark](https://github.com/google/benchmark)

Update the paths to libfmt.a, libbenchmark.a & the benchmark include
directory in the `Makefile`.

`make run` to build & run the benchmarks.
