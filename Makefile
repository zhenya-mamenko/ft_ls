# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/20 11:27:05 by emamenko          #+#    #+#              #
#    Updated: 2019/03/23 22:56:13 by emamenko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


.PHONY:		$(NAME) all clean fclean re reclean del reexec

NAME	=	ft_ls
SOURCES	=	ft_ls.c params.c error.c
DEBUG	=	-g -fsanitize=address

all:		$(NAME)

$(NAME):
			make -C libft/
			gcc -Wall -Wextra -Werror -o $(NAME) -Llibft -lft $(SOURCES)

clean:
			make -C libft/ clean

fclean:		clean
			make -C libft/ fclean
			rm -f $(NAME)

re: 		fclean all
			make -C libft/ re

reclean:	re; make clean;
			make -C libft/ reclean

del:
			rm -f $(NAME)

reexec:		del all
