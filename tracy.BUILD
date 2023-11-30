cc_library(
    name = "tracy",
    srcs = ["public/TracyClient.cpp"],
    hdrs = glob(["public/**"]),
    copts = ["-DTRACY_ENABLE"],
    includes = ["public"],
    linkopts = [
        "-ldl",
        "-pthread",
    ],
    visibility = ["//visibility:public"],
)
