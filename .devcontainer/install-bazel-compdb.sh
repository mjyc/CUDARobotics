#!/usr/bin/env bash
set -e

mkdir -p /opt/bazel

BAZEL_COMPDB_VERSION=${1:-"none"}

if [ "${BAZEL_COMPDB_VERSION}" = "none" ]; then
    echo "No Compilation database with Bazel version specified, skipping Compilation database with Bazel installation"
    exit 0
fi

cd /opt/bazel

curl -L "https://github.com/grailbio/bazel-compilation-database/archive/${BAZEL_COMPDB_VERSION}.tar.gz" | tar -xz \

ln -f -s "/opt/bazel/bazel-compilation-database-${BAZEL_COMPDB_VERSION}/generate.py" "/usr/local/bin/bazel-compdb"