load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_library(
    name = "mjyc",
    hdrs = ["mjyc.h"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "simulate",
    srcs = ["simulate.cpp"],
    deps = [
        ":mjyc",
        "@nlohmann_json//:json",
    ],
)