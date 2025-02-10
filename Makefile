# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vafleith <vafleith@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/23 14:41:29 by vafleith          #+#    #+#              #
#    Updated: 2025/02/10 22:24:02 by vafleith         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -g3
# CFLAGS += -Werror

MLX_PATH = minilibx-linux
MLX_NAME = libmlx.a
MLX = $(MLX_PATH)/$(MLX_NAME)
MLXFLAGS = -lXext -lX11

LIBFT_PATH = libft
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_PATH)/$(LIBFT_NAME)

GNL_PATH = ./get_next_line
GNL_NAME = get_next_line.a
GNL = $(GNL_PATH)/$(GNL_NAME)

GREEN = \033[0;32m
BLUE = \033[34m
VIOLET = \033[35m
BOLD = \033[1m
RESET = \033[0;m

INC = -Iinclude -Ilibft -I$(MLX_PATH) -I$(GNL_PATH)

SRC_DIR = src

SRCS = main.c rendering/image.c rendering/exit.c rendering/init.c rendering/raycasting.c \
	   rendering/player.c rendering/key_events.c
SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))

OBJ_DIR = build
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

.PHONY: all
all: $(MLX) $(LIBFT) $(GNL) $(NAME)

$(OBJ_DIR)/%.o: %.c
	@echo Compiling $<
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(MLX):
	@make -sC $(MLX_PATH) > /dev/null 2>&1
	@echo "$(VIOLET)$(BOLD)Compilation success -> MLX$(RESET)"

$(LIBFT):
	@make -sC $(LIBFT_PATH) > /dev/null
	@echo "$(VIOLET)$(BOLD)Compilation success -> LIBFT$(RESET)"

$(GNL):
	@make -C $(GNL_PATH) > /dev/null
	@echo "$(VIOLET)$(BOLD)Compilation success -> GNL$(RESET)"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX) $(LIBFT) $(GNL) $(INC) $(MLXFLAGS) -lm
	@echo "$(GREEN)$(BOLD)cub3D ready.✔$(RESET)"

.PHONY: clean
clean:
	@echo "$(BLUE)$(BOLD)Cleaning up object files 🧹$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make clean -C $(MLX_PATH) > /dev/null
	@make clean -C $(LIBFT_PATH) > /dev/null
	@make clean -C $(GNL_PATH) > /dev/null

.PHONY: fclean
fclean: clean
	@make clean -C $(MLX_PATH) > /dev/null
	@make fclean -C $(LIBFT_PATH) > /dev/null
	@make fclean -C $(GNL_PATH) > /dev/null
	@rm -rf $(NAME)

.PHONY: re
re: fclean all


valgrind_flags: $(LIBFT) $(GNL) $(MLX) $(NAME)
	@valgrind --track-fds=yes --trace-children=yes \
		--leak-check=full --show-leak-kinds=all \
		--suppressions=fuck_readline \
	./$(NAME)
