#!/bin/bash

# ---------------------------
# CONFIG
# ---------------------------
MAP_DIR="./assets/maps/"
MAP_FILE="lab.cub"
MAP_PATH="${MAP_DIR}${MAP_FILE}"
SAN_FLAGS="-fsanitize=undefined -g"
SKIP_BUILD=false
TARGET="debug_all"
BINARY="./cub3D"
TIMESTAMP=$(date +"%d%b%H_%M_%S")
LOG_DIR="logs/ubsan"
LOG_FILE="${LOG_DIR}/${TIMESTAMP}.log"

# ---------------------------
# ARG PARSING
# ---------------------------
if [ "$1" = "bonus" ]; then
    TARGET="debug_bonus"
    BINARY="./cub3D_bonus"
elif [ -z "$1" ]; then
    SKIP_BUILD=true
fi

# ---------------------------
# BUILD
# ---------------------------
if [ "$SKIP_BUILD" != true ]; then
	echo "Compiling with UndefinedBehaviorSanitizer..."
	make SAN_FLAGS="${SAN_FLAGS}" $TARGET || { echo "Build failed."; exit 1; }
fi

# ---------------------------
# RUN
# ---------------------------
mkdir -p "$LOG_DIR"

export UBSAN_OPTIONS="print_stacktrace=1"

echo -e "\nRunning: ${BINARY} ${MAP_PATH}"
echo "Logs will be saved to: ${LOG_FILE}"

"$BINARY" "$MAP_PATH" 2>&1 | tee "$LOG_FILE"
