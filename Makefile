
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/20 13:15:01 by dpoveda-          #+#    #+#              #
#   Updated: 2021/12/16 21:34:38 by                  ###   ########.fr       # #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                     VARS                                     #
# **************************************************************************** #

# COLORS
NOCOL=\033[0m
RED=\033[31m
GRN=\033[32m
YEL=\033[33m
BLU=\033[34m
MAG=\033[35m
CYN=\033[36m

# OS
UNAME_S := $(shell uname -s)

# **************************************************************************** #
#                                   PROGRAM                                    #
# **************************************************************************** #

NAME = cub3D

BIN_DIR ?= /usr/local/bin

# **************************************************************************** #
#                                   COMPILER                                   #
# **************************************************************************** #

MAKE = make

CC = gcc

CFLAGS += -Wall -Wextra -Werror

# **************************************************************************** #
#                                    PATHS                                     #
# **************************************************************************** #

SRC_PATH = src
OBJ_PATH = obj
INC_PATH = inc

# **************************************************************************** #
#                                    FLAGS                                     #
# **************************************************************************** #

CFLAGS += -I ./$(INC_PATH)

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #

SRC_DIR_MAIN	= main

OBJ_DIRS_NAME =	$(SRC_DIR_MAIN)		
OBJ_DIRS = $(addprefix $(OBJ_PATH)/, $(OBJ_DIRS_NAME))

SRC_ROOT =		main.c

SRC_MAIN = 		parse_map.c

SRC_NAME =	$(SRC_ROOT)														\
		$(SRC_MAIN)						\

OBJ_NAME = $(SRC_NAME:%.c=%.o)

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

# **************************************************************************** #
#                                     LIBS                                     #
# **************************************************************************** #

LFT_NAME = libft.a
LFT_DIR = libft
LFT = $(LFT_DIR)/$(LFT_NAME)

CFLAGS += -I ./$(LFT_DIR)/$(INC_PATH)

LDFLAGS = -L ./$(LFT_DIR)

LDLIBS = -lft

LDLIBS += -lreadline

# TODO remove this
ifeq ($(UNAME_S),Darwin)
	CFLAGS += -I /Users/$(USER)/.brew/opt/readline/include
	LDFLAGS += -L /Users/$(USER)/.brew/opt/readline/lib
endif

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

.PHONY: all sanitize thread clean fclean re norme

# ALL
all: $(NAME)

# NAME
$(NAME): $(OBJ) $(LFT_NAME)
	@printf "\n${YEL}LINKING:${NOCOL}\n"
	@printf "${BLU}"
	$(CC) $(CFLAGS) $(OBJ) $(LFT_NAME) -o $@ $(LDFLAGS) $(LDLIBS) $(CCFLAGS)
	@printf "${NOCOL}"
	@printf "\n${GRN}SUCCESS!${NOCOL}\n"
	@printf "${CYN}type \"./cub3D map.cub\" to start!${NOCOL}\n"

# INSTALL
install: $(NAME)
	install $(NAME) $(BIN_DIR)

# SANITIZE ADDRESS
ifeq ($(UNAME_S),Linux)
sanitize: CFLAGS += -pedantic -g3 -fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=bounds -fsanitize=null
endif
ifeq ($(UNAME_S),Darwin)
sanitize: CFLAGS += -pedantic -g3 -fsanitize=address
endif
sanitize: $(NAME)

# SANITIZE THREAD
thread: CFLAGS += -g3 -fsanitize=thread
thread: $(NAME)

# LIBFT
$(LFT_NAME): $(LFT)
	@printf "${MAG}"
	cp $(LFT) $(LFT_NAME)
	@printf "${NOCOL}"
$(LFT):
	@printf "\n${YEL}LIBFT:${NOCOL}\n"
	@printf "${MAG}"
	$(MAKE) all -sC $(LFT_DIR)
	@printf "${NOCOL}"

# OBJ
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_DIRS)
	@printf "${BLU}"
	$(CC) $(CFLAGS) -c $< -o $@
	@printf "${NOCOL}"

# OBJ DIRS
$(OBJ_DIRS): | $(OBJ_PATH)
	@printf "${MAG}"
	mkdir -p $(OBJ_DIRS)
	@printf "${NOCOL}"
$(OBJ_PATH):
	@printf "${MAG}"
	mkdir -p $(OBJ_PATH)
	@printf "${NOCOL}"

# CLEAN
clean:
	@printf "${RED}"
	$(MAKE) clean -sC $(LFT_DIR)
	rm -rf $(LFT_NAME)
	rm -rf $(OBJ_PATH)
	@printf "${NOCOL}"

# FULL CLEAN
fclean: clean
	@printf "${RED}"
	$(MAKE) fclean -sC $(LFT_DIR)
	rm -rf $(NAME)
	@printf "${NOCOL}"

# RE
re: fclean all

# NORMINETTE
norme:
	@printf "\n${GRN}##########${YEL} NORMINETTE ${GRN}##########${NOCOL}\n"
	@printf "\n${GRN}LIBFT:${BLU}\n\n"
	@norminette $(LFT_DIR)
	@printf "\n${GRN}CUB3D:${BLU}\n\n"
	@norminette $(INC_PATH)
	@norminette $(SRC_PATH)
	@printf "${NOCOL}"