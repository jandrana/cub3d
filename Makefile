# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/18 03:35:21 by ana-cast          #+#    #+#              #
#    Updated: 2025/05/29 17:12:55 by ana-cast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
##                               COMPILATION INFO                             ##
################################################################################

# Check if gcc is installed
HAS_GCC := $(shell command -v gcc 2> /dev/null)

# Check if clang is installed
HAS_CLANG := $(shell command -v clang 2> /dev/null)

ifdef HAS_CLANG
  CC = clang
else ifdef HAS_GCC
  CC = gcc
else
  $(error No compiler found)
endif

# EXECUTABLES #
NAME = cub3D
NAME_BONUS = cub3D_bonus

# FOLDERS #
LIBFT = ./lib/libft/
MLX = ./sgoinfre/shared/MLX42/
#MLX = ./lib/MLX42/ # To use this one, add libmlx to all (all : head libmlx...)

# HEADERS #
HLIBFT = ./lib/libft/include
HMLX = /sgoinfre/shared/MLX42/include
HCORE = ./include/core
HCUB3D = ./include/mandatory
HCUB3D_BONUS = ./include/bonus
HEADERS = -I$(HCORE) -I$(HCUB3D) -I$(HLIBFT) -I$(HMLX)
HEADERS_BONUS = -I$(HCORE) -I$(HCUB3D_BONUS) -I$(HLIBFT) -I$(HMLX)

# STATIC #
LLIBFT = ./lib/libft/libft.a
LMLX = /sgoinfre/shared/MLX42/build/libmlx42.a
MLX_DEPS = -ldl -lglfw -pthread -lm
LIBS = $(LLIBFT) $(LMLX) $(MLX_DEPS)


CFLAGS = -Wall -Wextra -Werror -O3 -march=native -mtune=native -ffast-math -flto -fomit-frame-pointer -funroll-loops -ftree-vectorize

# Sanitizer flags
#SAN_FLAGS := $(CFLAGS) -fsanitize=address,undefined -g

SAN_FLAGS = -g -O0


RM = rm -rf

################################################################################
##                              SOURCES AND OBJECTS                           ##
################################################################################

# CORE SOURCES #
SRC_CORE =  src/core/error_handler.c \
			src/core/utils.c \
			src/core/parser/init.c \
			src/core/parser/parser.c \
			src/core/parser/file.c \
			src/core/parser/elements/textures.c \
			src/core/parser/elements/colors.c \
			src/core/parser/elements/check.c \
			src/core/parser/map.c \
			src/core/parser/validate_map.c \
			src/core/parser/utils.c \
			src/core/parser/hlst_utils.c \
			src/core/parser/print_utils.c \
			src/core/renderer/init_player.c \
			src/core/renderer/render_scene.c \
			src/core/renderer/manage_color.c \
			src/core/renderer/find_wall_hit.c \
			src/core/renderer/color_utils.c \
			src/core/renderer/format_fps.c

# MANDATORY SOURCES #
SRC =	$(SRC_CORE) \
		src/mandatory/main.c \
		src/mandatory/parser.c \
		src/mandatory/render.c \
		src/mandatory/free_utils.c \
		src/mandatory/manage_input.c \
		src/mandatory/manage_resize.c \

# BONUS SOURCES #
SRC_BONUS = $(SRC_CORE) \
			src/bonus/main_bonus.c \
			src/bonus/init_bonus.c \
			src/bonus/parser_bonus.c \
			src/bonus/elements_bonus.c \
			src/bonus/free_bonus.c \
			src/bonus/render_bonus.c \
			src/bonus/manage_input_bonus.c \
			src/bonus/manage_resize_bonus.c \
			src/bonus/minimap/minimap.c \
			src/bonus/minimap/vision_utils.c \
			src/bonus/minimap/item_utils.c \
			src/bonus/minimap/utils.c \
			src/bonus/items/items_handler_bonus.c \
			src/bonus/draw_items.c \
			src/bonus/item_utils.c \
			src/bonus/doors/door_handler_bonus.c \


# OBJECTS #
OBJECTS = $(SRC:.c=.o)
OBJECTS_BONUS = $(SRC_BONUS:.c=.o)

################################################################################
##                                    COLORS                                 ##
################################################################################

END=\033[0m
BOLD=\033[1m
GREEN=\033[0;32m
RED=\033[0;31m
BLUE=\033[0;34m
YELLOW=\033[33m
MAGENTA=\033[35m
TURQUOISE=\033[36m

################################################################################
##                                     RULES                                  ##
################################################################################

# New targets:

all : head libft $(NAME)

bonus : head libft
	@$(MAKE) CFLAGS="$(CFLAGS) -D IS_BONUS" $(NAME_BONUS)

debug_all: fclean
	@$(MAKE) CFLAGS="$(CFLAGS) $(SAN_FLAGS)" all

debug_bonus: fclean
	@$(MAKE) CFLAGS="$(CFLAGS) $(SAN_FLAGS)" bonus

# Font name: ANSI Shadow
head :
	@echo "\n$(MAGENTA)"
	@echo " ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ "
	@echo "██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗"
	@echo "██║     ██║   ██║██████╔╝ █████╔╝██║  ██║"
	@echo "██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║"
	@echo "╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝"
	@echo " ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ "
	@echo ""
	@echo " 42MLG: by ana-cast && jorvarea"
	@echo " Executable: \033[36m cub3d $(MAGENTA)"
	@echo " Commands:\033[36m all clean fclean re bonus $(BLUE)"
	@echo " 🛠   Compiler: $(CC) $(END)\n"

libmlx:
	@cmake $(MLX) -B $(MLX)/build
	@make -s -C $(MLX)/build -j4

libft :
	@echo "$(GREEN)$(BOLD)  COMPILING...$(END) $(GREEN)"
	@make bonus -s -C $(LIBFT)
	@echo "$(GREEN)$(BOLD)  ✓ Libft ready $(END)"

$(NAME) : $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(BOLD)  ✓ Mandatory part compiled $(END)"

$(NAME_BONUS) : $(OBJECTS_BONUS)
	@$(CC) $(CFLAGS) $(OBJECTS_BONUS) $(LIBS) -o $(NAME_BONUS)
	@echo "$(GREEN)$(BOLD)  ✓ Bonus part compiled $(END)"

src/core/%.o : src/core/%.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@echo "$(GREEN)  ✓ Compiled core: $(notdir $<)$(END)"

src/mandatory/%.o : src/mandatory/%.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@echo "$(GREEN)  ✓ Compiled mandatory: $(notdir $<)$(END)"

src/bonus/%.o : src/bonus/%.c
	@$(CC) $(CFLAGS) $(HEADERS_BONUS) -c $< -o $@
	@echo "$(GREEN)  ✓ Compiled bonus: $(notdir $<)$(END)"

clean :
	@echo "$(RED)$(BOLD)  CLEANING...$(END)"
	@$(RM) $(OBJECTS) $(OBJECTS_BONUS)
	@make clean -s -C $(LIBFT)
	@echo  "$(RED)  ✓  Removed objects$(END)"

fclean : clean
	@$(RM) $(NAME) $(NAME_BONUS)
	@echo "$(RED)  ✓  Removed executables $(END)"
	@make fclean -s -C $(LIBFT)
	@echo "$(RED)  ✓  Removed libraries $(END)"

re : fclean all

rebonus : fclean bonus

.PHONY: all bonus head clean fclean re rebonus debug_all debug_bonus
