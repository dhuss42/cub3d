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

LFLAGS = -ldl -lglfw -pthread -lm	#linux
#MAC: LFLAGS = -lglfw -framework Cocoa -framework OpenGL -framework IOKit #mac
# LFLAGS = -lglfw -framework Cocoa -framework OpenGL -framework IOKit #mac
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
		raycasting/mini_map_bonus.c\
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

MLX42_LIB = ./MLX42/build/libMLX42.a
MLX42_INCLUDES = -I./MLX42/include/MLX42 #for linux

all: $(OBJ_DIR) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) all
	@$(MAKE) -C $(LIBFT_DIR) bonus

$(MLX42_LIB):
	mlx_clone

# Git repo which traces mem leaks without conflicting with MLX.
LEAK_FINDER = -L./leak_finder -lft_malloc
LEAK_FINDER_INCLUDES = -I./leak_finder/includes
LEAK_FINDER_REPO = https://github.com/iwillenshofer/leak_finder.git

$(NAME): mlx_clone $(OFILES) $(LIBFT) $(MLX42_LIB)
	@$(CC) $(CFLAGS) $(MLX42_INCLUDES) $(OFILES) $(LIBFT) -o $(NAME) $(MLX42_LIB) $(LFLAGS)
	@echo "\033[32m cub3D built successfully! \033[0m"
#MAC	@$(CC) $(CFLAGS) $(OFILES) $(LIBFT) $(MLX42_LIB) $(LFLAGS) -o $(NAME)
#linux	@$(CC) $(CFLAGS) $(MLX42_INCLUDES) $(OFILES) $(LIBFT) -o $(NAME) $(MLX42_LIB) $(LFLAGS)

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) $(LIBFT_INCLUDES) $(MLX42_INCLUDES) $(LEAK_FINDER_INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

mlx_clone:
	@if [ -d "MLX42" ]; then \
		echo "MLX42 directory already exists."; \
	else \
		git clone https://github.com/codam-coding-college/MLX42.git; \
		cd MLX42 && git checkout ce254c3a19af8176787601a2ac3490100a5c4c61 && \
		cmake -B build && cd build && make && cd ../..;\
	fi

leaks:	mlx_clone $(LIBFT) $(MLX42) $(LEAK_FINDER) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX42_Flags) $(MLX42) $(LEAK_FINDER) $(LIBFT) -o $(NAME)

# With linux: Add in leakfinder Makefile at CCFlags: -D_GNU_SOURCE
$(LEAK_FINDER):
	@if [ -d ./leak_finder/ ]; then \
		echo "[leak_finder] already exists!"; \
	else \
		echo "	Cloning [leak_finder library]"; \
		git clone $(LEAK_FINDER_REPO) leak_finder; \
	fi
	@echo "Compiling [leak_finder]..."
	@$(MAKE) -C ./leak_finder
	@cp ./leak_finder/libft_malloc.so ./
	@cp ./leak_finder/libft_malloc_x86_64_Darwin.so ./
	@echo "To use leak_finder: \
	- include 'malloc.h' on the VERY TOP of your main header (will substitute the malloc()) \
	- Use the appropriate functions print_leaks() (show_alloc_mem_ex()) at the exit points"

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

destroy:
	@echo "\033[35m destroying... \033[0m"
	@$(MAKE) fclean
	rm -rf ./MLX42
	rm -rf ./leak_finder ./libft_malloc.so ./libft_malloc_x86_64_Darwin.so

.PHONY: all clean fclean re mlx_clone leaks destroy
