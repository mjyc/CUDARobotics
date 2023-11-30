load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "eigen",
    build_file = "@//:eigen.BUILD",
    sha256 = "8586084f71f9bde545ee7fa6d00288b264a2b7ac3607b974e54d13e7162c1c72",
    strip_prefix = "eigen-3.4.0",
    urls = ["https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz"],
)

http_archive(
    name = "google_benchmark",
    sha256 = "1f71c72ce08d2c1310011ea6436b31e39ccab8c2db94186d26657d41747c85d6",
    strip_prefix = "benchmark-1.6.0",
    urls = ["https://github.com/google/benchmark/archive/v1.6.0.tar.gz"],
)

http_archive(
    name = "nlohmann_json",
    build_file = "@//:json.BUILD",
    sha256 = "e5c7a9f49a16814be27e4ed0ee900ecd0092bfb7dbfca65b5a421b774dccaaed",
    urls = ["https://github.com/nlohmann/json/releases/download/v3.11.2/include.zip"],
)

http_archive(
    name = "tracy",
    build_file = "@//:tracy.BUILD",
    sha256 = "a76017d928f3f2727540fb950edd3b736caa97b12dbb4e5edce66542cbea6600",
    strip_prefix = "tracy-0.10",
    urls = ["https://github.com/wolfpld/tracy/archive/refs/tags/v0.10.tar.gz"],
)

http_archive(
    name = "rules_python",
    sha256 = "84aec9e21cc56fbc7f1335035a71c850d1b9b5cc6ff497306f84cced9a769841",
    strip_prefix = "rules_python-0.23.1",
    url = "https://github.com/bazelbuild/rules_python/releases/download/0.23.1/rules_python-0.23.1.tar.gz",
)

load("@rules_python//python:repositories.bzl", "py_repositories")

py_repositories()

load("@rules_python//python:pip.bzl", "pip_parse")

pip_parse(
    name = "plot_deps",
    requirements_lock = "//:requirements.txt",
)

load("@plot_deps//:requirements.bzl", "install_deps")

install_deps()
