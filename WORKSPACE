load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "eigen",
    urls = ["https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz"],
    strip_prefix = "eigen-3.4.0",
    build_file = "@//:eigen.BUILD",
)

http_archive(
    name = "rules_cuda",
    urls = ["https://github.com/bazel-contrib/rules_cuda/archive/22a46e6b3e6aaecd1fd4d3769a669d2861115068.tar.gz"],
    strip_prefix = "rules_cuda-22a46e6b3e6aaecd1fd4d3769a669d2861115068",
)

http_archive(
    name = "google_benchmark",
    urls = ["https://github.com/google/benchmark/archive/v1.6.0.tar.gz"],
    strip_prefix = "benchmark-1.6.0",
)

load("@rules_cuda//cuda:repositories.bzl", "register_detected_cuda_toolchains", "rules_cuda_dependencies")
rules_cuda_dependencies()
register_detected_cuda_toolchains()