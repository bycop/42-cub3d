# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bycop <bycop@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/04 14:25:18 by bycop          #+#    #+#              #
#    Updated: 2021/01/03 15:46:16 by bycop         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SRCS = 	ft_strlen.c ft_strdup.c \
		ft_atoi.c ft_isalnum.c \
		ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c \
		ft_split.c ft_toupper.c \
		ft_strdup.c ft_putnbr_fd.c \
		ft_strncmp.c ft_tolower.c \
		ft_strlcat.c ft_strlcpy.c \
		ft_strrchr.c ft_strchr.c \
		ft_strnstr.c ft_memset.c \
		ft_memcpy.c ft_bzero.c \
		ft_memccpy.c ft_memchr.c \
		ft_memmove.c ft_memcmp.c \
		ft_calloc.c ft_itoa.c \
		ft_strjoin.c ft_substr.c \
		ft_strtrim.c ft_strmapi.c \
		ft_putchar_fd.c ft_putstr_fd.c \
		ft_putendl_fd.c get_next_line.c

SRCBONUS = 	ft_lstnew.c ft_lstadd_front.c \
			ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c \
			ft_lstclear.c ft_lstiter.c \
			ft_lstmap.c

OBJBONUS = ${SRCBONUS:.c=.o}

OBJS = ${SRCS:.c=.o}

HEADER = libft.h

NAME = libft.a

CC = gcc

RM = rm -f

FLAGS = -Wall -Wextra -Werror

%.o:	%.c ${HEADER}
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			ar rc ${NAME} ${OBJS}

bonus:		${OBJBONUS}
			@ar rc ${NAME} ${OBJBONUS}

all:		${NAME}
			
clean:
			${RM} ${OBJS} ${OBJBONUS}

fclean:		clean
			${RM} ${NAME}

re: fclean all

.PHONY: all bonus clean fclean re