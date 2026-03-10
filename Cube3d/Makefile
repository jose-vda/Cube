# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/05 17:57:02 by jose-vda          #+#    #+#              #
#    Updated: 2026/02/19 16:42:28 by jose-vda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cube3d
# minilibx: Linux = X11 (minilibx/). macOS = Cocoa/OpenGL (minilibx_macos/).
UNAME_S		:=	$(shell uname -s)
ifeq ($(UNAME_S),Darwin)
MLX			=	minilibx_macos/
MLX_A		=	$(addprefix $(MLX), libmlx.a)
LDFLAGS		=	-L$(MLX) -lmlx -framework OpenGL -framework AppKit -lm -lz
INCLUDE		=	-Iincludes -Iminilibx_macos
else
MLX			=	minilibx/
MLX_A		=	$(addprefix $(MLX), libmlx_Linux.a)
LDFLAGS		=	-L$(MLX) -lmlx_Linux -lXext -lX11 -lm -lz
INCLUDE		=	-Iincludes -I.
endif
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror $(INCLUDE) -g
RM			=	rm -f
SRCS		=	src/main.c \
				src/init_mlx.c \
				src/free_resources.c \
				src/utils.c \
				src/utils2.c \
				src/parsing/parser.c \
				src/parsing/parser_utils.c \
				src/parsing/parser_ident.c \
				src/parsing/parser_map.c \
				src/parsing/parser_free.c \
				src/parsing/parser_loop.c \
				src/raycasting/renderization.c \
				src/raycasting/minimap.c \
				src/raycasting/raycasting.c \
				src/raycasting/ray_draw.c \
				src/raycasting/moves.c \
				src/raycasting/moves_door.c \
				src/raycasting/moves_move.c \
				src/raycasting/moves_rot.c \
				src/raycasting/get_next_line.c

OBJS		=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)  $(MLX_A)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "Linked into executable \033[0;32mCUBE3D\033[0m."

$(MLX_A):
	@$(MAKE) -s -C $(MLX)
	@echo "Compiled $(MLX_A)."

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiling $<."

localclean:
	@$(RM) $(OBJS)
	@echo "Removed object files."

clean: localclean
	@$(MAKE) clean -s -C $(MLX)
	@echo "Clean mlx."

fclean: localclean
	@$(MAKE) clean -s -C $(MLX)
	@echo "Clean mlx."
	@$(RM) $(NAME)
	@echo "Removed executable."

re: fclean all

.PHONY: all clean fclean re localclean bonus