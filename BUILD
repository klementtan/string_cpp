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
cc_binary(
    name = "benchmark",
    srcs = ["benchmark.cpp"],
    deps = [ "@benchmark//:benchmark", ":kstring"],
)
