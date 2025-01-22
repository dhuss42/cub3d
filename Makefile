# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/18 16:39:14 by maustel           #+#    #+#              #
#    Updated: 2024/12/18 16:39:14 by maustel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX42 = ./MLX42/build/libMLX42.a
#LFLAGS = MLX42/build/libmlx42.a -lglfw -framework Cocoa -framework OpenGL -framework IOKit #mac
LFLAGS = $(MLX42) -ldl -lglfw -pthread -lm #linux
CFILES = cub.c\
		error_free/error_handling.c\
		error_free/free_cub.c\
		parser/parser.c\
		parser/parse_line_content.c\
		parser/color_number.c\
		parser/get_map.c\
		parser/check_content.c\
		parser/check_map_helpers.c\
		raycasting/drawing.c\
		raycasting/helpers.c\
		raycasting/init_win_imgs.c\
		raycasting/key_inputs.c\
		raycasting/mini_map.c\
		raycasting/player.c\
		raycasting/raycaster.c\
		raycasting/rendering.c

VPATH := $(dir $(CFILES))
#VPATH specifies a list of directories that Make should search for source
#files when they are not found in the current directory.

OBJ_DIR = objs
OFILES = $(addprefix $(OBJ_DIR)/, $(notdir $(CFILES:.c=.o)))

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INCLUDES = -I $(LIBFT_DIR)

all: $(OBJ_DIR) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) all
	@$(MAKE) -C $(LIBFT_DIR) bonus

$(NAME): $(OFILES) $(LIBFT)
	@$(CC) -I./MLX42/include/MLX42 $(CFLAGS) $(OFILES) $(LIBFT) -o $(NAME) $(LFLAGS)
	@echo "\033[32m cub3D built successfully! \033[0m"
#MAC	@$(CC) $(CFLAGS) $(OFILES) $(LIBFT) $(LFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c 
	@$(CC) $(CFLAGS) $(LIBFT_INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "\033[33m cleaning cub3D files \033[0m"
	@rm -f $(OFILES)
	@rm -fd $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean:
	@echo "\033[33m fcleaning cub3D \033[0m"
	@rm -f $(OFILES)
	@rm -fd $(OBJ_DIR)
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re:
	@echo "\033[35m re making... \033[0m"
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re
