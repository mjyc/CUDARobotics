#!/usr/bin/env bash

TMP_OUTFILE="$(mktemp)"
cleanup() {
    EXIT_CODE=$?
    set +e
    if [[ -n "${TMP_OUTFILE}" ]]; then
        echo "Executing cleanup of tmp file"
        rm -Rf "${TMP_OUTFILE}"
    fi
    exit $EXIT_CODE
}
trap cleanup EXIT

# Run the update_animation.sh script
./update_animation.sh $TMP_OUTFILE

# Check the exit code of update_animation.sh
if [[ $? -eq 0 ]]; then
    echo "PASS"
else
    echo "FAIL"
    exit 1
fi