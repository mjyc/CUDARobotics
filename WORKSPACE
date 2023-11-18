load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "eigen",
    urls = ["https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz"],
    sha256 = "8586084f71f9bde545ee7fa6d00288b264a2b7ac3607b974e54d13e7162c1c72",
    strip_prefix = "eigen-3.4.0",
    build_file = "@//:eigen.BUILD",
)

http_archive(
    name = "google_benchmark",
    urls = ["https://github.com/google/benchmark/archive/v1.6.0.tar.gz"],
    sha256 = "1f71c72ce08d2c1310011ea6436b31e39ccab8c2db94186d26657d41747c85d6",
    strip_prefix = "benchmark-1.6.0",
)

http_archive(
    name = "nlohmann_json",
    urls = ["https://github.com/nlohmann/json/releases/download/v3.11.2/include.zip"],
    sha256 = "e5c7a9f49a16814be27e4ed0ee900ecd0092bfb7dbfca65b5a421b774dccaaed",
    build_file = "@//:json.BUILD",
)