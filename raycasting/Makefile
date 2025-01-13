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
CFLAGS = -Wall -Wextra -Werror ../MLX42/build/libmlx42.a -lglfw -framework Cocoa -framework OpenGL -framework IOKit
CFILES = raycaster.c\
	helpers.c\
	player.c\
	mini_map.c\

OFILES = $(CFILES:.c=.o)

# LIBFT_DIR = ./libft
# LIBFT = $(LIBFT_DIR)/libft.a
# LIBFT_INCLUDES = -I $(LIBFT_DIR)

all: $(NAME)
	@echo "\033[32m cub3D built successfully! \033[0m"

# $(LIBFT):
# 	@$(MAKE) -C $(LIBFT_DIR) all
# 	@$(MAKE) -C $(LIBFT_DIR) bonus

$(NAME): $(OFILES) 
	@$(CC) $(CFLAGS) $(OFILES) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJDIR)

clean:
	@echo "\033[33m cleaning cub3D files \033[0m"
	@rm -f $(OBJ_DIR)/*

fclean:
	@echo "\033[33m fcleaning cub3D \033[0m"
	@rm -f $(OBJ_DIR)/*
	@rm -f $(NAME)

re:
	@echo "\033[35m re making... \033[0m"
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re
