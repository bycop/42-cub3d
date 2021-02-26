# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfournio <sfournio@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/22 19:08:47 by sfournio          #+#    #+#              #
#    Updated: 2021/02/26 14:34:42 by sfournio         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SRCS = 	srcs/parsing/parsing.c 		srcs/parsing/textures.c			\
		srcs/struct.c 				srcs/utils.c cub3d.c 			\
		srcs/errors/file_verif.c	srcs/raycasting/calc_drawer.c	\
		srcs/raycasting/prog.c 		srcs/parsing/strsjoin.c			\
		srcs/errors/map_verif_errors.c 	srcs/raycasting/utils.c		\
		srcs/parsing/ft_parser.c	srcs/raycasting/screen.c		\
		srcs/raycasting/key_wasd.c	srcs/raycasting/key_rle.c		\

OBJS = ${SRCS:.c=.o}

LIBS = 	libmlx.dylib 			libft.a

HEADERF = includes

HEADER = cub3d.h

NAME = cub3D

CC = gcc

RM = rm -f

FLAGS = -Wall -Wextra -Werror -fsanitize=address -g3 

%.o:	%.c ${HEADERF}/${HEADER}
	${CC} ${FLAGS} -c $< -o ${<:.c=.o} -I${HEADERF} -g

$(NAME):	lib ${OBJS}
			${CC} ${FLAGS} -o ${NAME} ${OBJS} ${LIBS} -I${HEADERF}

all:		${NAME}
			
lib:
			make -C libft
			make -C minilibx_mms_20200219
			cp libft/libft.a .
			cp minilibx_mms_20200219/libmlx.dylib .

clean:
			${RM} ${OBJS} ${OBJBONUS}
			make -C libft fclean
			make -C minilibx_mms_20200219 clean

fclean:		clean
			${RM} ${NAME}
			make -C libft fclean
			make -C minilibx_mms_20200219 clean
			if [ -a libmlx.dylib ]; then rm libmlx.dylib; fi;
			if [ -a libft.a ]; then rm libft.a; fi;

re: fclean all

.PHONY: all clean fclean lib re