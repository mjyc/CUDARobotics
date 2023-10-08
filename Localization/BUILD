cc_library(
    name = "models_2d",
    hdrs = ["models_2d.h"],
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
        ":models_2d",
        "//Localization/extended_kalman_filter",
        "@google_benchmark//:benchmark_main",
    ],
)
