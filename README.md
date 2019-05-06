# slce
Standard Library Concepts Emulation Library

This header-only library provides type traits similar to things defined in C++20 standard library concepts.
This library is intended to use for backport C++20 codes to legacy C++ environment.

## Requirements

C++ compiler that supports at least C++11.

Boost Unit Test Framework (Only tests require this)

## Note

Since callable concepts depends on std::invoke that was introduced in C++17, corresponding type traits always return false in C++14 or prior.

