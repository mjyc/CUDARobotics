load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_library(
    name = "unscented_kalman_filter",
    hdrs = ["unscented_kalman_filter.h"],
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
        ":unscented_kalman_filter",
        "//Localization:models_2d",
        "@eigen//:eigen3",
    ],
)
