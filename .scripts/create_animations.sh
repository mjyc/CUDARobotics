#!/usr/bin/env bash
set -e

if [ "$#" -gt 0 ]; then
    ALGORITHMS=("$@")  # This syntax collects all arguments into an array.
else
    ALGORITHMS=(
        "Localization/extended_kalman_filter"
    )
fi

for ALGORITHM in "${ALGORITHMS[@]}"; do
    WORKSPACE="$(bazel info workspace)"
    INFILE="${WORKSPACE}/.scripts/${ALGORITHM}/$(basename ${ALGORITHM}).csv"
    OUTFILE="${WORKSPACE}/.scripts/${ALGORITHM}/$(basename ${ALGORITHM}).gif"
    SCRIPTFILE="${WORKSPACE}/.scripts/${ALGORITHM}/$(basename ${ALGORITHM}).plt"

    # Generate data
    bazel run //${ALGORITHM}:simulate > "${INFILE}"

    # Create gif
    gnuplot -e "infile='${INFILE}'; outfile='${OUTFILE}'" "${SCRIPTFILE}"
done