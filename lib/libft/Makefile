# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/15 21:00:35 by ana-cast          #+#    #+#              #
#    Updated: 2024/07/16 15:27:55 by ana-cast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


################################################################################
##                               COMPILATION INFO                             ##
################################################################################

NAME = libft.a

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

FLAGS = -Wall -Wextra -Werror -fPIC
RM = rm -f
LIBFT = include
DEPS = -I include

################################################################################
##                              SOURCES AND OBJECTS                           ##
################################################################################

CC_SRCS = src/originals/character_classification/ft_isascii.c \
	src/originals/character_classification/ft_isdigit.c \
	src/originals/character_classification/ft_isprint.c \
	src/originals/character_classification/ft_isalnum.c \
	src/originals/character_classification/ft_isalpha.c \
	src/originals/character_classification/ft_str_is_alpha.c \
	src/originals/character_classification/ft_str_is_numeric.c \
	src/originals/character_classification/ft_str_is_printable.c

CC2_SRCS = src/originals/case_conversion/ft_tolower.c \
	src/originals/case_conversion/ft_toupper.c

MM_SRCS = src/originals/memory_manipulation/ft_bzero.c \
	src/originals/memory_manipulation/ft_calloc.c \
	src/originals/memory_manipulation/ft_strdup.c \
	src/originals/memory_manipulation/ft_memcmp.c \
	src/originals/memory_manipulation/ft_memcpy.c \
	src/originals/memory_manipulation/ft_memmove.c \
	src/originals/memory_manipulation/ft_memset.c \
	src/originals/memory_manipulation/ft_memchr.c

SM_SRCS = src/originals/string_manipulation/ft_atoi.c \
	src/originals/string_manipulation/ft_atol.c \
	src/originals/string_manipulation/ft_strlcat.c \
	src/originals/string_manipulation/ft_strlcpy.c \
	src/originals/string_manipulation/ft_strlen.c

SS_SRCS = src/originals/string_search/ft_strchr.c \
	src/originals/string_search/ft_strncmp.c \
	src/originals/string_search/ft_strnstr.c \
	src/originals/string_search/ft_strrchr.c

A_SRCS = src/additionals/ft_itoa.c \
	src/additionals/ft_split.c \
	src/additionals/ft_striteri.c \
	src/additionals/ft_strjoin.c \
	src/additionals/ft_strmapi.c \
	src/additionals/ft_strtrim.c \
	src/additionals/ft_substr.c

AO_SRCS = src/additionals/output_functions/ft_putchar_fd.c \
	src/additionals/output_functions/ft_putendl_fd.c \
	src/additionals/output_functions/ft_putnbr_fd.c \
	src/additionals/output_functions/ft_putstr_fd.c

CC_OBJECTS = $(CC_SRCS:.c=.o)
CC2_OBJECTS = $(CC2_SRCS:.c=.o)
MM_OBJECTS = $(MM_SRCS:.c=.o)
SM_OBJECTS = $(SM_SRCS:.c=.o)
SS_OBJECTS = $(SS_SRCS:.c=.o)
A_OBJECTS = $(A_SRCS:.c=.o)
AO_OBJECTS = $(AO_SRCS:.c=.o)

OBJECTS = $(CC_OBJECTS) $(CC2_OBJECTS) $(MM_OBJECTS) $(SM_OBJECTS) $(SS_OBJECTS) $(A_OBJECTS) $(AO_OBJECTS)

BONUS_SR = src/bonus/ft_lstadd_back_bonus.c \
	src/bonus/ft_lstadd_front_bonus.c \
	src/bonus/ft_lstclear_bonus.c \
	src/bonus/ft_lstdelone_bonus.c \
	src/bonus/ft_lstiter_bonus.c \
	src/bonus/ft_lstlast_bonus.c \
	src/bonus/ft_lstnew_bonus.c \
	src/bonus/ft_lstsize_bonus.c \
	src/bonus/ft_lstmap_bonus.c

GNL_SRC = src/get_next_line/get_next_line.c \
	src/get_next_line/get_next_line_utils.c \
	src/get_next_line/get_next_line_bonus.c

BONUS_OB = $(BONUS_SR:.c=.o) $(GNL_SRC:.c=.o)

################################################################################
##                                    COLOURS                                 ##
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

all : $(NAME)

$(NAME) : $(OBJECTS)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)
	@echo "\n$(TURQUOISE)✦ ---------------------- ✦$(BOLD)"
	@echo "      COMPILED LIBFT$(END)$(TURQUOISE)"
	@echo "✦ ---------------------- ✦$(END)"

bonus : $(OBJECTS) $(BONUS_OB)
	@ar rc $(NAME) $(OBJECTS) $(BONUS_OB)
	@ranlib $(NAME)
	@echo "\n$(TURQUOISE)✦ ---------------------- ✦$(BOLD)"
	@echo "  COMPILED BONUS LIBFT$(END)$(TURQUOISE)"
	@echo "✦ ---------------------- ✦$(END)"

%.o : %.c $(LIBFT)
	@$(CC) $(FLAGS) -c $< -o $@ $(DEPS)

clean :
	@$(RM) $(OBJECTS) $(BONUS_OB)

fclean: clean
	@$(RM) $(NAME)

re :
	@$(MAKE) fclean
	@clear
	@$(MAKE) all

rebonus :
	@$(MAKE) fclean
	@clear
	@$(MAKE) bonus

.PHONY: all bonus clean fclean re rebonus