#!/usr/bin/env bash
set -e

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

echo "Installing ibazel..."
TMP_DIR=$(mktemp -d -t ibazel-XXXXXXXXXX)

echo "${TMP_DIR}"

git clone https://github.com/bazelbuild/bazel-watcher.git "${TMP_DIR}"

cd ${TMP_DIR}
bazel build //cmd/ibazel

mv "${TMP_DIR}/bazel-bin/cmd/ibazel" /opt/ibazel
ln -s "/opt/ibazel/ibazel_/ibazel" /usr/local/bin/ibazel
