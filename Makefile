# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fra <fra@student.codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2023/07/01 22:06:35 by fra           #+#    #+#                  #
#    Updated: 2023/08/01 12:53:58 by faru          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SHELL := /bin/bash

NAME := cub3d
SRC_DIR := sources
OBJ_DIR := objects
MLX42_DIR := MLX42
LIBFT_DIR := libft
MLX42 := $(MLX42_DIR)/build/libmlx42.a
LIBFT := $(LIBFT_DIR)/libft.a
# HEADERS := $(shell find include -type f -name '*.h')
HEADERS := include/app/app.h \
	include/check_map/check_map.h \
	include/cub3d/cub3d.h \
	include/cub3d/enum.h \
	include/init/init.h \
	include/parser/parser.h \
	include/render/render.h \
	include/tools/tools.h \
	include/vector/vector.h
# SOURCES := $(shell find $(SRC_DIR) -type f -name '*.c')
SOURCES := sources/app/app.c \
	sources/app/hooks.c \
	sources/app/minimap.c \
	sources/app/mov_pov.c \
	sources/app/pov.c \
	sources/check_map/check_map.c \
	sources/check_map/flood_fill.c \
	sources/check_map/stack.c \
	sources/init/free.c \
	sources/init/init.c \
	sources/init/torch_init.c \
	sources/main/main.c \
	sources/parser/checker.c \
	sources/parser/get_map_info.c \
	sources/parser/parse_config.c \
	sources/parser/parse_map.c \
	sources/parser/parser.c \
	sources/render/color_effects.c \
	sources/render/pixel.c \
	sources/render/render.c \
	sources/render/torch.c \
	sources/render/wall_attributes.c \
	sources/tools/tools.c \
	sources/vector/vector.c
OBJECTS := $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(SOURCES:.c=.o))

CC  := gcc
IFLAGS := -Iinclude -I$(MLX42_DIR)/include -I$(LIBFT_DIR)/include
CFLAGS := -Wall -Wextra -Werror -g3

LFLAGS := -L$(MLX42_DIR)/build -lmlx42 -L$(LIBFT_DIR) -lft
ifeq ($(shell uname -s),Darwin)			# Mac
	LFLAGS += -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
else ifeq ($(shell uname -s),Linux)		# Linux
	LFLAGS += -lglfw -ldl -pthread -lm
	CFLAGS += -fsanitize=address
endif

_DEBUG := 0
ifeq ($(_DEBUG),1)
	CFLAGS +=  -DDEBUG=1
endif

GREEN = \x1b[32;01m
RED = \x1b[31;01m
BLUE = \x1b[34;01m
RESET = \x1b[0m
YELLOW = \x1b[33;01m

all: $(MLX42) $(LIBFT) $(NAME)

run: all
	@clear
	@./$(NAME) maps/test1.cub

$(MLX42):
	@cmake $(MLX42_DIR) -B $(MLX42_DIR)/build
	@$(MAKE) -C $(MLX42_DIR)/build -j4 --quiet
	
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --quiet

$(NAME): $(OBJ_DIR) $(OBJECTS)
	@$(CC) $(CFLAGS) $(IFLAGS) $(OBJECTS) $(LFLAGS) -o $(NAME)
	@printf "(cub3D) $(GREEN)Created program $(NAME)$(RESET)\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@printf "(cub3D) $(BLUE)Created object $$(basename $@)$(RESET)\n"

clean:
	@$(MAKE) clean -C $(MLX42_DIR)/build -j4 --quiet
	@$(MAKE) clean -C $(LIBFT_DIR) --quiet
	@for file in $(shell find $(OBJ_DIR) -type f -name '*.o'); do \
		rm -f $$file;	\
		printf "(cub3D) $(RED)Removed object $$(basename $$file)$(RESET)\n"; \
	done

fclean: clean
	@$(MAKE) clean/fast -C $(MLX42_DIR)/build -j4 --quiet
	@$(MAKE) fclean -C $(LIBFT_DIR) --quiet
	@-rm -f $(NAME)
	@printf "(cub3D) $(RED)Removed program $(NAME)$(RESET)\n"

re: fclean all

.PHONY: all, clean, fclean, re