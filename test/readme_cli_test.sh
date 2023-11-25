#!/usr/bin/env bash

FAILED_TESTS=()

# Test CC=clang bazel run --compilation_mode=opt //${ALGORITHM}:benchmark
ALGORITHMS=(
    "Localization/extended_kalman_filter"
)
for ALGORITHM in "${ALGORITHMS[@]}"; do
    # Run benchmark command
    CC=clang bazel run --compilation_mode=opt //${ALGORITHM}:benchmark

    # Check the exit code
    if [[ $? -eq 0 ]]; then
        echo "✅ PASS: \"CC=clang bazel run --compilation_mode=opt //${ALGORITHM}:benchmark\""
    else
        echo "❌ FAIL: \"CC=clang bazel run --compilation_mode=opt //${ALGORITHM}:benchmark\""
        FAILED_TESTS+=("${ALGORITHM}")
    fi

    # Run visualization command
    CC=clang bazel build //${ALGORITHM}:generate_plot

    # Check the exit code
    if [[ $? -eq 0 ]]; then
        echo "✅ PASS: \"CC=clang bazel build //${ALGORITHM}:generate_plot //${ALGORITHM}:generate_plot\""
    else
        echo "❌ FAIL: \"CC=clang bazel build //${ALGORITHM}:generate_plot //${ALGORITHM}:generate_plot\""
        FAILED_TESTS+=("${ALGORITHM}")
    fi
done

# Report result
if [ ${#FAILED_TESTS[@]} -ne 0 ]; then
    echo "❌ FAILED: FAILED_TESTS is not 0"
    exit 1
fi