#!/usr/bin/env bash
set -e

mkdir -p /opt/bazel

BUILDIFIER_VERSION=${1:-"none"}

if [ "${BUILDIFIER_VERSION}" = "none" ]; then
    echo "No Buildifier version specified, skipping Buildifier installation"
    exit 0
fi

curl -LSs "https://github.com/bazelbuild/buildtools/releases/download/v${BUILDIFIER_VERSION}/buildifier-linux-amd64" -o "/opt/bazel/buildifier"

chmod +x "/opt/bazel/buildifier"

ln -s "/opt/bazel/buildifier" "/usr/local/bin/buildifier"