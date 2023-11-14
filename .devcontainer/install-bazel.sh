#!/usr/bin/env bash
set -e

mkdir -p /opt/bazel

BAZELISK_VERSION=${1:-"none"}

if [ "${BAZELISK_VERSION}" = "none" ]; then
    echo "No Bazelisk version specified, skipping Bazelisk installation"
    exit 0
fi

echo "Installing Bazelisk..."
curl -LSs "https://github.com/bazelbuild/bazelisk/releases/download/v${BAZELISK_VERSION}/bazelisk-linux-amd64" -o "/opt/bazel/bazelisk"

chmod +x "/opt/bazel/bazelisk"

ln -s "/opt/bazel/bazelisk" "/usr/local/bin/bazel"