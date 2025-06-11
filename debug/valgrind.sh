#!/bin/bash

# Execution command in terminal:
# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=debug/valgrind.supp -s ./cub3D

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
LEAK_FLAGS="--leak-check=full --show-leak-kinds=all --track-origins=yes"
SKIP_BUILD=false

# ---------------------------
# ARG PARSING
# ---------------------------
if [ -z "$1" ]; then
	SKIP_BUILD=true
fi

if [ "$1" = "bonus" ]; then
    TARGET="debug_bonus"
    BINARY="./cub3D_bonus"
    shift
fi

mkdir -p "$LOG_DIR"

# ---------------------------
# BUILD
# ---------------------------
if [ "$SKIP_BUILD" != true ]; then
	echo "Compiling with Valgrind-safe build..."
	make $TARGET || { echo "Build failed."; exit 1; }
fi

# ---------------------------
# RUN
# ---------------------------
if [ "$1" = "all" ]; then
    valgrind ${LEAK_FLAGS} --suppressions=${SUP_FILE} \
        --log-file="${LOG_FILE}" -s "$BINARY" "$MAP_PATH"
else
    valgrind ${LEAK_FLAGS} --suppressions=${SUP_FILE} -v \
        --log-file="${LOG_FILE}" -s "$BINARY"
fi
