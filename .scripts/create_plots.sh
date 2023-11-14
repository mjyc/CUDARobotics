#!/usr/bin/env bash
set -e

if [ "$#" -gt 0 ]; then
    ALGORITHMS=("$@")  # This syntax collects all arguments into an array.
else
    ALGORITHMS=(
        "Localization/extended_kalman_filter"
        "Planning/astar"
    )
fi

for ALGORITHM in "${ALGORITHMS[@]}"; do
    WORKSPACE="$(bazel info workspace)"
    INFILE="${WORKSPACE}/.scripts/${ALGORITHM}/$(basename ${ALGORITHM}).log"
    OUTFILE="${WORKSPACE}/.scripts/${ALGORITHM}/$(basename ${ALGORITHM}).png"
    SCRIPTFILE="${WORKSPACE}/.scripts/${ALGORITHM}/$(basename ${ALGORITHM}).py"

    # Generate data
    CC=clang bazel run //${ALGORITHM}:simulate > "${INFILE}"

    # Create gif
    python3 "${SCRIPTFILE}" "${INFILE}" "${OUTFILE}"
done