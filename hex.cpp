#include <benchmark/benchmark.h>
#include <fmt/format.h>
#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <ostream>
#include <iomanip>

#include "256.h"
#include "nibble.h"

using namespace std;

static void BM_constexpr_version(benchmark::State& state) {
    unsigned char c = 0;
    while (state.KeepRunning()) {
        string s;
        s.reserve(3);
        s += '%';
        HexDigits d = charToHex(c++);
        s.append(d.hex, 2);
    }
}

static void BM_constexpr_lookuptable(benchmark::State& state) {
    unsigned char c = 0;
    while (state.KeepRunning()) {
        string s;
        s.reserve(3);
        s += '%';
        HexDigits d = charToHexLookup(c++);
        s.append(d.hex, 2);
    }
}

static void BM_lookuptable_fast(benchmark::State& state) {
    unsigned char c = 0;
    while (state.KeepRunning()) {
        string s{"%00"};
        HexDigits d = charToHexLookup(c++);
        s[1] = d.hex[0];
        s[2] = d.hex[1];
    }
}

static void BM_lookuptable_fast_inline(benchmark::State& state) {
    unsigned char c = 0;
    while (state.KeepRunning()) {
        string s{"%00"};
        HexDigits d = inlineCharToHexLookup(c++);
        s[1] = d.hex[0];
        s[2] = d.hex[1];
    }
}

static void BM_lookuptable_string(benchmark::State& state) {
    unsigned char c = 0;
    while (state.KeepRunning()) {
        string s;
        s.reserve(3);
        s += '%';
        s.append(charToHexLookupString(c++));
    }
}

static void BM_lookuptable_string_v2(benchmark::State& state) {
    unsigned char c = 0;
    while (state.KeepRunning()) {
        string s;
        s.reserve(3);
        s += '%';
        benchmark::DoNotOptimize(s.append(charToHexLookupStringv2(c++)));
    }
}

static void BM_lookuptable_string_v3(benchmark::State& state) {
    unsigned char c = 0;
    while (state.KeepRunning()) {
        string s{"%"};
        s += charToHexLookupStringv2(c++);
    }
}

static void BM_lookuptable_string_v3b(benchmark::State& state) {
    unsigned char c = 0;
    while (state.KeepRunning()) {
        string s{"%"};
        s.append(charToHexLookupStringv2(c++));
    }
}

static void BM_lookuptable_string_v4(benchmark::State& state) {
    unsigned char c = 0;
    while (state.KeepRunning()) {
        string s{"%00"};
        string s2 = charToHexWithInlineLookup(c++);
        s[1] = s2[0];
        s[2] = s2[1];
    }
}

static void BM_string_direct(benchmark::State& state) {
    unsigned char c = 0;
    while (state.KeepRunning()) {
        string s{"%"};
        s += inlineCharToHexString(c++);
    }
}

// Same as BM_string_direct but not using the inline version
static void BM_string_direct_noinline(benchmark::State& state) {
    unsigned char c = 0;
    while (state.KeepRunning()) {
        string s{"%"};
        s += charToHexWithInlineLookup(c++);
    }
}

static void BM_snprintf_version(benchmark::State& state) {
    unsigned char c = 0;
    while (state.KeepRunning()) {
        string s;
        s.reserve(3);
        char buf[sizeof("%ff")];
        buf[0] = '%';
        snprintf(buf + 1, sizeof(buf) - 1, "%02x", c++);
        s.append(buf, 2);
    }
}

static void BM_snprintf_string(benchmark::State& state) {
    unsigned char c = 0;
    while (state.KeepRunning()) {
        string s;
        // Allow snprintf to write a trailing NUL-byte
        s.resize(4);
        s[0] = '%';
        // Obviously this is not ideal.
        snprintf(const_cast<char*>(s.data()) + 1, 3, "%02x", c++);
        s.resize(3); // trim the trailing NUL-byte
    }
}

static void BM_fmt_version(benchmark::State& state) {
    unsigned char c = 0;
    while (state.KeepRunning()) {
        string s;
        s.reserve(3);
        s.append(fmt::sprintf("%02x", c++));
    }
}

static void BM_fmt_braces(benchmark::State& state) {
    unsigned char c = 0;
    while (state.KeepRunning()) {
        string s;
        s.reserve(3);
        s.append(fmt::format("{:02x}", c++));
    }
}

static void BM_stringstream(benchmark::State& state) {
    unsigned char c = 0;
    while (state.KeepRunning()) {
        stringstream s;
        s << "%" << std::setw(2) << std::setfill('0') << std::hex << static_cast<short>(c);
        benchmark::DoNotOptimize(s.str());
    }
}

static void BM_lookup256(benchmark::State& state) {
    unsigned char c = 0;
    while (state.KeepRunning()) {
        string s{"%"};
        s += lookup256(c);
    }
}

// Of course we have to test the 256-entry lookup table with
// direct assignment appending :)
static void BM_lookup256_direct(benchmark::State& state) {
    unsigned char c = 0;
    while (state.KeepRunning()) {
        string s{"%00"};
        string hex = lookup256(c);
        s[1] = hex[0];
        s[2] = hex[1];
    }
}

static void BM_lookup256Digits(benchmark::State& state) {
    unsigned char c = 0;
    while (state.KeepRunning()) {
        string s{"%"};
        s += lookup256Digits(c);
    }
}

static void BM_lookup256Digits_direct(benchmark::State& state) {
    unsigned char c = 0;
    while (state.KeepRunning()) {
        string s{"%00"};
        string hex = lookup256(c);
        s[1] = hex[0];
        s[2] = hex[1];
    }
}

static void BM_lookup256HexDigits(benchmark::State& state) {
    unsigned char c = 0;
    while (state.KeepRunning()) {
        string s{"%00"};
        struct HexDigits d = lookup256HexDigits(c);
        s[1] = d.hex[0];
        s[2] = d.hex[1];
    }
}

static void BM_lookup256HexDigitsInline(benchmark::State& state) {
    unsigned char c = 0;
    while (state.KeepRunning()) {
        string s{"%00"};
        struct HexDigits d = inlineLookup256HexDigits(c);
        s[1] = d.hex[0];
        s[2] = d.hex[1];
    }
}

BENCHMARK(BM_constexpr_version);
BENCHMARK(BM_constexpr_lookuptable);
BENCHMARK(BM_lookuptable_fast);
BENCHMARK(BM_lookuptable_fast_inline);
BENCHMARK(BM_lookuptable_string);
BENCHMARK(BM_lookuptable_string_v2);
BENCHMARK(BM_lookuptable_string_v3);
BENCHMARK(BM_lookuptable_string_v3b);
BENCHMARK(BM_lookuptable_string_v4);
BENCHMARK(BM_string_direct);
BENCHMARK(BM_string_direct_noinline);
BENCHMARK(BM_lookup256);
BENCHMARK(BM_lookup256_direct);
BENCHMARK(BM_lookup256Digits);
BENCHMARK(BM_lookup256Digits_direct);
BENCHMARK(BM_lookup256HexDigits);
BENCHMARK(BM_lookup256HexDigitsInline);
BENCHMARK(BM_snprintf_version);
BENCHMARK(BM_snprintf_string);
BENCHMARK(BM_fmt_version);
BENCHMARK(BM_fmt_braces);
BENCHMARK(BM_stringstream);

BENCHMARK_MAIN();
