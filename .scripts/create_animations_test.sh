#!/usr/bin/env bash

TMP_INFILE="$(mktemp)"
TMP_OUTFILE="$(mktemp)"
cleanup() {
    EXIT_CODE=$?
    set +e
    if [[ -n "${TMP_INFILE}" ]]; then
        echo "Executing cleanup of tmp file1"
        rm -Rf "${TMP_INFILE}"
    fi
    if [[ -n "${TMP_OUTFILE}" ]]; then
        echo "Executing cleanup of tmp file2"
        rm -Rf "${TMP_OUTFILE}"
    fi
    exit $EXIT_CODE
}
trap cleanup EXIT

# Run the create_animations.sh script
.scripts/create_animations.sh $TMP_INFILE $TMP_OUTFILE

# Check the exit code of create_animations.sh
if [[ $? -eq 0 ]]; then
    echo "✅ PASS"
else
    echo "❌ FAIL"
    exit 1
fi