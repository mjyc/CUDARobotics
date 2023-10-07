cc_library(
    name = "models_2d",
    hdrs = ["models_2d.h"],
    includes = ["."],
    deps = [
        "@eigen//:eigen3",
    ],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "benchmark",
    srcs = ["benchmark.cpp"],
    deps = [
        "@google_benchmark//:benchmark_main",
        ":models_2d",
        "//Localization/extended_kalman_filter:extended_kalman_filter",
        "//Localization/unscented_kalman_filter:unscented_kalman_filter",
    ],
)