#!/bin/bash

# Delete old Build folder
rm -rf Build

# Create new Build
mkdir -p Build && cd Build

# Construction
cmake ..
if cmake --build .; then
    echo "Build succeeded."
else
    echo "Build failed."
    exit 1
fi

# Run tests and main.cpp
if ./Tests/runTests; then
    echo "Tests passed."
else
    echo "Tests failed."
    exit 1
fi

