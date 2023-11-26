load("@plot_deps//:requirements.bzl", "requirement")
load("@rules_cc//cc:defs.bzl", "cc_binary")
load("@rules_python//python:defs.bzl", "py_binary")

cc_library(
    name = "types",
    hdrs = ["types.h"],
)

cc_library(
    name = "utils",
    hdrs = ["utils.h"],
    deps = [":types"],
)

cc_library(
    name = "mjyc",
    hdrs = ["mjyc.h"],
    deps = [
        ":types",
        ":utils",
    ],
)

cc_binary(
    name = "benchmark",
    srcs = ["benchmark.cpp"],
    deps = [
        ":mjyc",
        ":utils",
        "@google_benchmark//:benchmark_main",
        "@nlohmann_json//:json",
    ],
)

cc_binary(
    name = "simulate",
    srcs = ["simulate.cpp"],
    deps = [
        ":mjyc",
        "@nlohmann_json//:json",
    ],
)

py_binary(
    name = "plot",
    srcs = ["plot.py"],
    deps = [
        requirement("numpy"),
        requirement("matplotlib"),
    ],
)

genrule(
    name = "generate_plot",
    outs = [
        "simulate_output.txt",
        "plot.png",
    ],
    cmd = "./$(location :simulate) $(location simulate_output.txt) && ./$(location :plot) $(location simulate_output.txt) $(location plot.png)",
    tools = [
        ":plot",
        ":simulate",
    ],
)
