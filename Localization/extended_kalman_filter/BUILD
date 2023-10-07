load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_library(
    name = "extended_kalman_filter",
    hdrs = ["extended_kalman_filter.h"],
    includes = ["."],
    deps = [
        "@eigen//:eigen3",
        "//Localization:models_2d",
    ],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "simulate",
    srcs = ["simulate.cpp"],
    deps = [
        "@eigen//:eigen3",
        "//Localization:models_2d",
        ":extended_kalman_filter",
    ],
)

cc_binary(
    name = "benchmark",
    srcs = ["benchmark.cpp"],
    deps = [
        "@google_benchmark//:benchmark_main",
        "//Localization:models_2d",
        ":extended_kalman_filter",
    ],
)