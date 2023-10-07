load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_library(
    name = "unscented_kalman_filter",
    hdrs = ["unscented_kalman_filter.h"],
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
        ":unscented_kalman_filter",
    ],
)