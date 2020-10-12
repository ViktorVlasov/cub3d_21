# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddraco <ddraco@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/15 11:26:54 by efumiko           #+#    #+#              #
#    Updated: 2020/10/12 18:29:03 by ddraco           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = clang

SRC = main.c parser/ft_utils_parser.c parser/get_next_line.c \
parser/parse_map.c parser/parse_params.c parser/parse_resolution.c \
parser/parse_textures.c parser/parser.c \
graphics/start.c graphics/raycasting.c graphics/handle_press.c \
graphics/ft_paint.c graphics/get_coord_player.c

OBJ = $(SRC:.c=.o)

HEADER = includes/parser.h

FLAGS = -Wall -Werror -Wextra -g -I./includes

all: $(NAME)

$(NAME):$(OBJ)
	$(MAKE) -C mlx
	$(MAKE) bonus -C libft
	cp mlx/libmlx.dylib .
	cp libft/libft.a .
	gcc -o $(NAME) $(FLAGS) $(OBJ) -L. -lft libmlx*

clean:
	rm -rf libmlx.dylib
	rm -rf libft.a
	rm -rf $(OBJ)
	rm -f *.bmp
	$(MAKE) clean -C libft

fclean: clean
	rm -rf $(NAME)
	$(MAKE) fclean -C libft
	$(MAKE) clean -C minilibx

re: fclean all

.PHONY: all clean fclean re run