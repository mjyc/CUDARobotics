#!/usr/bin/env bash

# Run the create_animations.sh script
.scripts/create_animations.sh

# Check the exit code of create_animations.sh
if [[ $? -eq 0 ]]; then
    echo "✅ PASS"
else
    echo "❌ FAIL"
    exit 1
fi