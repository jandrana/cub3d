#!/bin/bash

# ---------------------------
# CONFIG
# ---------------------------
MAP_DIR="./assets/maps/"
MAP_FILE="test.cub"
MAP_PATH="${MAP_DIR}${MAP_FILE}"
BINARY="./cub3D"

# ---------------------------
# ARG PARSING
# ---------------------------
if [ "$1" = "bonus" ]; then
    BINARY="./cub3D_bonus"
fi

# ---------------------------
# RUN
# ---------------------------
echo "Launching GDB with: ${BINARY} ${MAP_PATH}"
gdb --args "$BINARY" "$MAP_PATH"
