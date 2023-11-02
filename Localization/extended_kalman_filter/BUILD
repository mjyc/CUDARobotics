load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_library(
    name = "extended_kalman_filter",
    hdrs = ["extended_kalman_filter.h"],
    includes = ["."],
    visibility = ["//visibility:public"],
    deps = [
        "//Localization:models_2d",
        "@eigen//:eigen3",
    ],
)

cc_binary(
    name = "simulate",
    srcs = ["simulate.cpp"],
    deps = [
        ":extended_kalman_filter",
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
    name = "benchmark",
    srcs = ["benchmark.cpp"],
    deps = [
        ":extended_kalman_filter",
        ":onlytailei",
        "//Localization:models_2d",
        "@google_benchmark//:benchmark_main",
    ],
)