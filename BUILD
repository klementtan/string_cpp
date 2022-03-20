load("@hedron_compile_commands//:refresh_compile_commands.bzl", "refresh_compile_commands")

cc_library(
  name = "kstring",
  hdrs = ["kstring.hpp"]
)

cc_test(
  name = "kstring_test",
  size = "small",
  srcs = ["kstring_test.cpp"],
  deps = ["@com_google_googletest//:gtest_main", ":kstring"]
)
