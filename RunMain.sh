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

./RunExecutable
