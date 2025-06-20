#!/bin/bash

# Move out of assets folder and execute in parent directory
PROJECT_DIR=$(pwd)
OUTPUT_FILE="$PROJECT_DIR/compile_commands.json"

# Include paths and flags from the Makefile
INCLUDE_PATH="-I$PROJECT_DIR/include/core -I$PROJECT_DIR/include/bonus -I$PROJECT_DIR/include/mandatory -I$PROJECT_DIR/lib/libft/include -I/home/ana-cast/Desktop/Repos/cub3d/lib/MLX42/include"
FLAGS="-Wall -Wextra -Werror"
CC="clang" 

echo "[" > $OUTPUT_FILE
for SRC_FILE in $(find src -name "*.c"); do
    OBJ_FILE="${SRC_FILE%.c}.o"
    COMMAND="$CC $FLAGS $INCLUDE_PATH -c $SRC_FILE -o $OBJ_FILE"
    echo "  {" >> $OUTPUT_FILE
    echo "    \"directory\": \"$PROJECT_DIR\"," >> $OUTPUT_FILE
    echo "    \"command\": \"$COMMAND\"," >> $OUTPUT_FILE
    echo "    \"file\": \"$SRC_FILE\"" >> $OUTPUT_FILE
    echo "  }," >> $OUTPUT_FILE
done
# Remove the last comma and close the JSON array
sed -i '$ s/,$//' $OUTPUT_FILE
echo "]" >> $OUTPUT_FILE
