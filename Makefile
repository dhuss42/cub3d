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
CFILES = cub.c\
		errors/error_handling.c

VPATH := $(dir $(CFILES))

OBJ_DIR = objs
OFILES = $(addprefix $(OBJ_DIR)/, $(notdir $(CFILES:.c=.o)))

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INCLUDES = -I $(LIBFT_DIR)

all: $(NAME)
	@echo "\033[32m cub3D built successfully! \033[0m"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) all
	@$(MAKE) -C $(LIBFT_DIR) bonus

$(NAME): $(OFILES) $(LIBFT)
	@$(CC) $(CFLAGS) $(OFILES) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(LIBFT_INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJDIR)

clean:
	@echo "\033[33m cleaning cub3D files \033[0m"
	@rm -f $(OBJ_DIR)/*
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean:
	@echo "\033[33m fcleaning cub3D \033[0m"
	@rm -f $(OBJ_DIR)/*
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re:
	@echo "\033[35m re making... \033[0m"
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re
