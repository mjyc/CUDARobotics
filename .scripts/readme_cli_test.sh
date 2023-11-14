#!/usr/bin/env bash

FAILED_TESTS=()

# Test bazel run --compilation_mode=opt //${ALGORITHM}:benchmark
ALGORITHMS=(
    "Localization/extended_kalman_filter"
)
for ALGORITHM in "${ALGORITHMS[@]}"; do
    bazel run --compilation_mode=opt //${ALGORITHM}:benchmark

    # Check the exit code
    if [[ $? -eq 0 ]]; then
        echo "✅ PASS: \"bazel run --compilation_mode=opt //${ALGORITHM}:benchmark\""
    else
        echo "❌ FAIL: \"bazel run --compilation_mode=opt //${ALGORITHM}:benchmark\""
        FAILED_TESTS+=("${ALGORITHM}")
    fi
done

# Test .scripts/create_plots.sh
.scripts/create_plots.sh

if [[ $? -eq 0 ]]; then
    echo "✅ PASS: \".scripts/create_plots.sh\""
else
    echo "❌ FAIL: \".scripts/create_plots.sh\""
    FAILED_TESTS+=("${ALGORITHM}")
fi

# Report result
if [ ${#FAILED_TESTS[@]} -ne 0 ]; then
    exit 1
fi