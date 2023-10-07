#!/usr/bin/env bash
set -e

WORKSPACE="$(bazel info workspace)"
TMP_FILE="$(mktemp)"
cleanup() {
    EXIT_CODE=$?
    set +e
    if [[ -n "${TMP_FILE}" ]]; then
        echo "Executing cleanup of tmp file"
        rm -Rf "${TMP_FILE}"
    fi
    exit $EXIT_CODE
}
trap cleanup EXIT

# Generate data
bazel run //Localization/extended_kalman_filter:simulate > "${TMP_FILE}"

# Create gif
OUTPUT_FILE="${WORKSPACE}/Localization/extended_kalman_filter/animation.gif"
gnuplot -e "infile='${TMP_FILE}'; outfile='${OUTPUT_FILE}'" "${WORKSPACE}/Localization/extended_kalman_filter/animation.plt"