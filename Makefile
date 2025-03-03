###############################################################################
#### executable program's name ################################################

NAME = cub3D

###############################################################################
#### path and variables #######################################################
###############################################################################

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

SRC_DIR = src
OBJ_DIR = build
INC = -Iinclude -Ilibft -I$(MLX_PATH) -I$(GNL_PATH)

GNL_PATH = ./get_next_line
GNL_NAME = get_next_line.a
GNL = $(GNL_PATH)/$(GNL_NAME)

LIBFT_PATH = ./libft
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_PATH)/$(LIBFT_NAME)

MLX_PATH = minilibx-linux
MLX_NAME = libmlx.a
MLX = $(MLX_PATH)/$(MLX_NAME)
MLXFLAGS = -lXext -lX11

GREEN = \033[0;32m
BLUE = \033[34m
VIOLET = \033[35m
BOLD = \033[1m
RESET = \033[0;m

###############################################################################
#### source files and objects #################################################
###############################################################################

PARSING_FILES = parsing/map_init.c parsing/map_parsing.c \
			parsing/map_security.c parsing/parsing_maze.c parsing/player.c \

CONTROL_FILES = control/exit.c control/key_events.c control/move.c \

RAYCASTING_FILES = raycasting/get_direction.c raycasting/get_distance.c \
			raycasting/get_point.c raycasting/raycasting.c raycasting/utils.c \

RENDERING_FILES = rendering/draw.c rendering/image.c rendering/minimap.c \

SRCS =  main.c debug.c $(PARSING_FILES) $(CONTROL_FILES) $(RAYCASTING_FILES) \
			 $(RENDERING_FILES)


SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

###############################################################################
#### rule by default ##########################################################
###############################################################################

all: $(LIBFT) $(GNL) $(NAME) $(MLX)

###############################################################################
#### create objects (.o) from source files (.c) ###############################
###############################################################################
	
$(OBJ_DIR)/%.o: %.c
	@echo Compiling $<
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

###############################################################################
#### linking objects in executable ############################################
###############################################################################

$(NAME): $(OBJS) $(MLX)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX) $(LIBFT) $(GNL) $(INC) $(MLXFLAGS) -lm
	@echo "$(GREEN)$(BOLD)|-> cub3D ready ✔$(RESET)"

###############################################################################
#### compile external libraries ###############################################
###############################################################################

$(MLX):
	@make -sC $(MLX_PATH) > /dev/null 2>&1
	@echo "$(VIOLET)$(BOLD)Compilation success -> MLX$(RESET)"

$(LIBFT):
	@make -C $(LIBFT_PATH) > /dev/null
	@echo "$(VIOLET)$(BOLD)Compilation success -> LIBFT$(RESET)"

$(GNL):
	@make -C $(GNL_PATH) > /dev/null
	@echo "$(VIOLET)$(BOLD)Compilation success -> GNL$(RESET)"

###############################################################################
#### Clean objects + external lib #############################################
###############################################################################

clean:
	@echo "$(BLUE)$(BOLD)Cleaning up object files 🧹$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make clean -C $(MLX_PATH) > /dev/null
	@make clean -C $(LIBFT_PATH) > /dev/null
	@make clean -C $(GNL_PATH) > /dev/null

###############################################################################
#### Clean the executable + external lib ######################################
###############################################################################

fclean: clean
	@make clean -C $(MLX_PATH) > /dev/null
	@make fclean -C $(LIBFT_PATH) > /dev/null
	@make fclean -C $(GNL_PATH) > /dev/null
	@rm -rf $(NAME)

###############################################################################
###############################################################################

re: fclean all

###############################################################################
###############################################################################

.PHONY: all clean fclean re

###############################################################################
###############################################################################

command:  $(LIBFT) $(GNL) $(MLX) $(NAME)
	./$(NAME) map/mini.cub

valgrind_command:  $(LIBFT) $(GNL) $(MLX) $(NAME)
	@valgrind --leak-check=full \
	./$(NAME) map/mini.cub

giga_valgrind_command:  $(LIBFT) $(GNL) $(MLX) $(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all \
	./$(NAME) map/mini.cub