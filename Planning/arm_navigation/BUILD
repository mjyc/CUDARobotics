load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_library(
    name = "mjyc",
    hdrs = ["mjyc.h"],
    includes = ["."],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "simulate",
    srcs = ["simulate.cpp"],
    deps = [
        ":mjyc",
        "@eigen//:eigen3",
        "@nlohmann_json//:json",
    ],
)