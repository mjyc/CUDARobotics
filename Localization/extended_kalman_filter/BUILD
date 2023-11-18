load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_library(
    name = "utils",
    hdrs = ["utils.h"],
    includes = ["."],
    visibility = ["//visibility:public"],
    deps = [
        "//Localization:models_2d",
        "@eigen//:eigen3",
    ],
)

cc_library(
    name = "mjyc",
    hdrs = ["mjyc.h"],
    includes = ["."],
    visibility = ["//visibility:public"],
    deps = [
        ":utils",
        "//Localization:models_2d",
        "@eigen//:eigen3",
    ],
)

cc_library(
    name = "onlytailei",
    hdrs = ["onlytailei.h"],
    includes = ["."],
    visibility = ["//visibility:public"],
    deps = [
        "@eigen//:eigen3",
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