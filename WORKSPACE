load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "eigen",
    urls = ["https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz"],
    strip_prefix = "eigen-3.4.0",
    build_file = "@//:eigen.BUILD",
)

http_archive(
    name = "google_benchmark",
    urls = ["https://github.com/google/benchmark/archive/v1.6.0.tar.gz"],
    strip_prefix = "benchmark-1.6.0",
)