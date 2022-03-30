# C++ String

This is a header only C++ string implementation that supports Short String
Optimisation(SSO) and Copy On Write (COW) for long string. The aim of this
repository is for learning purposes that prioritises readability.

## Features

1. Short String Optimisation:
  * No allocation for sting with less than 22 (non-inclusive of `\0`) characters.
2. Copy on Write:
  * Lazily copy long string (more than 256 characters) only when writer operations
  are invoked.
  * Utilises custom lock-free reference counting.
3. Allow for custom allocator

## Build and Testing

**Build**:
```shell
bazel build --cxxopt='-std=c++20' kstring 
```

**Test**
```shell
bazel test --test_output=streamed kstring_test 
```
