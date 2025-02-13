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

NAME = cub3D

# FOLDERS #
LIBFT = ./lib/libft/
MLX = /sgoinfre/shared/MLX42/
#MLX = ./lib/MLX42/ # To use this one, add libmlx to all (all : head libmlx...)

# HEADERS #
HLIBFT = $(LIBFT)/include
HMLX = $(MLX)/include
HCUB3D = ./include
HEADERS = -I$(HCUB3D) -I$(HLIBFT) -I$(HMLX)

# STATIC #
LLIBFT = $(LIBFT)/libft.a
LMLX = $(MLX)/build/libmlx42.a
MLX_DEPS = -ldl -lglfw -pthread -lm
LIBS = $(LLIBFT) $(LMLX) $(MLX_DEPS)

CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

################################################################################
##                              SOURCES AND OBJECTS                           ##
################################################################################

SRC = src/main.c \
	src/error_handler.c \
	src/parser/parser.c

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

all : head libft $(NAME)

bonus : all

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

%.o : %.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@echo "$(GREEN)  ✓ Compiled: $(notdir $<)$(END)"

clean :
	@echo "$(RED)$(BOLD)  CLEANING...$(END)"
	@$(RM) $(OBJECTS)
	@echo  "$(RED)  ✓  Removed $(NAME) objects$(END)"
	@make clean -s -C $(LIBFT)
	@echo  "$(RED)  ✓  Removed library objects$(END)"

fclean : clean
	@$(RM) $(NAME)
	@echo "$(RED)  ✓  Removed $(NAME) $(END)"
	@make fclean -s -C $(LIBFT)
	@echo "$(RED)  ✓  Removed libraries $(END)"


re : fclean all

.PHONY: all bonus head line clean fclean re
