#!/usr/bin/env bash
set -e

ALGORITHMS=(
    "Localization/extended_kalman_filter"
    "Localization/unscented_kalman_filter"
)

for ALGORITHM in "${ALGORITHMS[@]}"; do
    WORKSPACE="$(bazel info workspace)"
    INFILE="${1:-${WORKSPACE}/.scripts/${ALGORITHM}/$(basename ${ALGORITHM}).csv}"
    OUTFILE="${2:-${WORKSPACE}/.scripts/${ALGORITHM}/$(basename ${ALGORITHM}).gif}"
    SCRIPTFILE="${WORKSPACE}/.scripts/${ALGORITHM}/$(basename ${ALGORITHM}).plt"

    # Generate data
    bazel run //${ALGORITHM}:simulate > "${INFILE}"

    # Create gif
    gnuplot -e "infile='${INFILE}'; outfile='${OUTFILE}'" "${SCRIPTFILE}"
done