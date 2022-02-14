load("@hedron_compile_commands//:refresh_compile_commands.bzl", "refresh_compile_commands")

cc_library(
  name = "kstring",
  hdrs = ["kstring.hpp"]
)

refresh_compile_commands(
    name = "refresh_compile_commands",

    # Specify the targets of interest.
    # For example, specify a dict of targets and their arguments:
    targets = {
      "//:kstring_test": "--cxxopt='-std=c++20'"
    },
)

cc_test(
  name = "kstring_test",
  size = "small",
  srcs = ["kstring_test.cpp"],
  deps = ["@com_google_googletest//:gtest_main", ":kstring"]
)
