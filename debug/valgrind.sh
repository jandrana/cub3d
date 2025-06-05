#!/bin/bash

# ---------------------------
# CONFIG
# ---------------------------
MAP_DIR="./assets/maps/"
MAP_FILE="test.cub"
MAP_PATH="${MAP_DIR}${MAP_FILE}"
SUP_FILE=valgrind.supp
TARGET="debug_all"
BINARY="./cub3D"
TIMESTAMP=$(date +"%d%b%H_%M_%S")
LOG_DIR="logs/valgrind"
LOG_FILE="${LOG_DIR}/${TIMESTAMP}.log"

# ---------------------------
# ARG PARSING
# ---------------------------
if [ "$1" = "bonus" ]; then
    TARGET="debug_bonus"
    BINARY="./cub3D_bonus"
    shift
fi

mkdir -p "$LOG_DIR"

# ---------------------------
# BUILD
# ---------------------------
echo "Compiling with Valgrind-safe build..."
make $TARGET || { echo "Build failed."; exit 1; }

# ---------------------------
# RUN
# ---------------------------
if [ "$1" = "all" ]; then
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
        --log-file="${LOG_FILE}" -s "$BINARY" "$MAP_PATH"
else
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
        --suppressions=${SUP_FILE} --log-file="${LOG_FILE}" -s "$BINARY" "$MAP_PATH"
fi
