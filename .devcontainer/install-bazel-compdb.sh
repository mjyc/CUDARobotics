#!/usr/bin/env bash
set -e

mkdir -p /opt/bazel

BAZEL_COMPDB_VERSION=${1:-"none"}

if [ "${BAZEL_COMPDB_VERSION}" = "none" ]; then
    echo "No Compilation database with Bazel version specified, skipping Compilation database with Bazel installation"
    exit 0
fi

# Cleanup temporary directory and associated files when exiting the script.
cleanup() {
    EXIT_CODE=$?
    set +e
    if [[ -n "${TMP_DIR}" ]]; then
        echo "Executing cleanup of tmp files"
        rm -Rf "${TMP_DIR}"
    fi
    exit $EXIT_CODE
}
trap cleanup EXIT

echo "Installing bazel-compdb..."
TMP_DIR=$(mktemp -d -t bazel-compdb-XXXXXXXXXX)

cd ${TMP_DIR}
curl -L "https://github.com/grailbio/bazel-compilation-database/archive/${BAZEL_COMPDB_VERSION}.tar.gz" | tar -xz
ln -f -s "/opt/bazel/bazel-compilation-database-${BAZEL_COMPDB_VERSION}/generate.py" "/usr/local/bin/bazel-compdb"