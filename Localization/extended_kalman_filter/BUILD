load("@plot_deps//:requirements.bzl", "requirement")
load("@rules_cc//cc:defs.bzl", "cc_binary")
load("@rules_python//python:defs.bzl", "py_binary")

cc_library(
    name = "utils",
    hdrs = ["utils.h"],
    deps = [
        "//Localization:models_2d",
        "@eigen//:eigen3",
    ],
)

cc_library(
    name = "mjyc",
    hdrs = ["mjyc.h"],
    deps = [
        ":utils",
        "//Localization:models_2d",
        "@eigen//:eigen3",
    ],
)

cc_library(
    name = "onlytailei",
    hdrs = ["onlytailei.h"],
    deps = ["@eigen//:eigen3"],
)

cc_binary(
    name = "benchmark",
    srcs = ["benchmark.cpp"],
    deps = [
        ":utils",
        ":mjyc",
        ":onlytailei",
        "//Localization:models_2d",
        "@google_benchmark//:benchmark_main",
    ],
)

cc_binary(
    name = "simulate",
    srcs = ["simulate.cpp"],
    deps = [
        ":mjyc",
        "//Localization:models_2d",
        "@eigen//:eigen3",
    ],
)

py_binary(
  name = "plot",
  srcs = ["plot.py"],
  deps =[
    requirement("numpy"),
    requirement("matplotlib"),
  ]
)

genrule(
    name = "generate_plot",
    outs = ["simulate_output.txt", "plot.png"],
    cmd = "./$(location :simulate) $(location simulate_output.txt) && ./$(location :plot) $(location simulate_output.txt) $(location plot.png)",
    tools = [":simulate", ":plot"],
)
