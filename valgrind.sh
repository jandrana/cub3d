MAP_DIR="assets/maps/"
MAP_FILE="simple.cub"
MAP_PATH=${MAP_DIR}${MAP_FILE}
SUP_FILE=valgrind.supp
GAME_COMMAND="./cub3D $MAP_PATH"

# Valgrind flags for leaks (default = --leak-check=full --show-leak-kinds=all)
LEAK_FLAGS="--leak-check=full --show-leak-kinds=all --track-origins=yes"

mkdir -p leaks

NO_SUP="all"

if [ "$#" -ne 1 ]; then
	mkdir -p leaks/sup
	LOG_FILE=leaks/sup/$(date +"%d%b%H_%M_%S").log
	valgrind ${LEAK_FLAGS} --suppressions=${SUP_FILE} --log-file=${LOG_FILE} -s $GAME_COMMAND
elif [ "$1" = "$NO_SUP" ]; then
	LOG_FILE=leaks/$(date +"%d%b%H_%M_%S").log
    valgrind ${LEAK_FLAGS} --log-file=${LOG_FILE} -s $GAME_COMMAND
fi

# Comando para terminal  (sin variables y sin logs)
# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=valgrind.supp -s ./cub3D assets/maps/simple.cub