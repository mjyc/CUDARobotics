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
    OUTFILE="${WORKSPACE}/.scripts/${ALGORITHM}/$(basename ${ALGORITHM})"
    SCRIPTFILE="${WORKSPACE}/.scripts/${ALGORITHM}/$(basename ${ALGORITHM})"

    # Generate data
    CC=clang bazel run //${ALGORITHM}:simulate > "${INFILE}"

    # Create gif
    if [[ ${ALGORITHM} == "Localization/extended_kalman_filter" ]]; then
        gnuplot -e "infile='${INFILE}'; outfile='${OUTFILE}.gif'" "${SCRIPTFILE}.plt"
    else
        python3 "${SCRIPTFILE}.py" "${INFILE}" "${OUTFILE}.png"
    fi
done