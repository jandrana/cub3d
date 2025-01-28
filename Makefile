# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/18 03:35:21 by ana-cast          #+#    #+#              #
#    Updated: 2025/01/18 04:15:58 by ana-cast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
##                               COMPILATION INFO                             ##
################################################################################

NAME = cub3D
LIBFT = lib/libft/

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

# HOSTNAME_SUFFIX := $(shell hostname | awk -F '.' '{print $$NF}')

# ifeq ($(HOSTNAME_SUFFIX),42malaga.com)
# 	LIBMLX = /sgoinfre/shared/MLX42
# else
#	LIBMLX = $(shell pwd)/lib/MLX42
# endif

LIBMLX = $(shell pwd)/lib/MLX42 # uncomment block and comment this if dont want to download MLX submodule at 42

MLX42 = $(LIBMLX)/build/libmlx42.a
MLX42_HEADER_DIR = $(LIBMLX)/include/MLX42

FLAGS = -Wall -Wextra -Werror
RM = rm -f
CUB3D = include/
INCLUDE = -L ./lib/libft -L ./lib/MLX42 -lft -lm $(MLX42)
DEPS = -I include -I $(LIBFT)/include -I$(MLX42_HEADER_DIR)

################################################################################
##                              SOURCES AND OBJECTS                           ##
################################################################################

SRC = src/main.c

OBJECTS = $(SRC:.c=.o)

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

all : head libmlx libft $(NAME)

bonus : all

head :
	@echo "$(MAGENTA)"
	@echo  "     /\\\\\\\\\                /\\\            /\\\\\\\\\\          /\\\          "
	@echo  "   /\\\////////                \/\\\          /\\\///////\\\        \/\\\         "
	@echo  "  /\\\/                         \/\\\         \///      /\\\         \/\\\        "
	@echo  "  /\\\              /\\\    /\\\ \/\\\                /\\\//          \/\\\       "
	@echo  "  \/\\\             \/\\\   \/\\\ \/\\\\\\\\\         \////\\\    /\\\\\\\\\      "
	@echo  "   \//\\\            \/\\\   \/\\\ \/\\\////\\\           \//\\\  /\\\////\\\     "
	@echo  "     \///\\\          \/\\\   \/\\\ \/\\\  \/\\\  /\\\      /\\\  \/\\\  \/\\\    "
	@echo  "        \////\\\\\\\\\ \//\\\\\\\\\  \/\\\\\\\\\  \///\\\\\\\\\/   \//\\\\\\\/\\  "
	@echo  "            \/////////   \/////////   \/////////     \/////////      \///////\//  "
	@echo ""
	@echo "\t        42MLG: by ana-cast && jorvarea"
	@echo "\tProyect: \033[36m cub3d $(MAGENTA)"
	@echo "\tCommands:\033[36m all clean fclean re bonus $(BLUE)"
	@echo "\t🛠   Compiler: $(CC) $(END)\n"

libft :
	@make bonus -s -C $(LIBFT)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
	@echo "$(TURQUOISE)"
	@echo "✦ --------------- ✦"
	@echo "|  Created MLX42  |"
	@echo "✦ --------------- ✦$(WHITE)"

$(NAME) : line $(OBJECTS)
	@echo "✦ ---------------------- ✦$(END)"
	@$(CC) $(FLAGS) $(OBJECTS) $(INCLUDE) -o $(NAME)

%.o : %.c $(CUB3D)
	@$(CC) $(FLAGS) -c $< -o $@ $(DEPS)
	@echo "$(GREEN)  ✓ Compiled: $(notdir $<)"

line :
	@echo "$(GREEN) $(BOLD)"
	@echo "  COMPILING CUB3D...$(END) $(GREEN)"
	@echo "✦ ---------------------- ✦"

clean :
	@printf "\n$(YELLOW) 🗑   Removing objects$(END)"
	@$(RM) $(OBJECTS)
	@echo "$(GREEN)\r  ✓  $(RED)Removed  objects from $(NAME) $(END)"
	@make clean -s -C $(LIBFT)

fclean: clean
	@printf "$(YELLOW) 🗑   Removing $(NAME) $(END)"
	@$(RM) $(NAME)
	@make fclean -s -C $(LIBFT)
	@echo "$(GREEN)\r  ✓  $(RED)Removed  $(NAME) $(END)\n"

re :
	@$(MAKE) -s fclean
	@clear
	@$(MAKE) -s all

.PHONY: all bonus head line clean fclean re