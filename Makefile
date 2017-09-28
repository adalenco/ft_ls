# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adalenco <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/10 17:12:17 by adalenco          #+#    #+#              #
#    Updated: 2017/09/27 20:45:15 by adalenco         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = $(addprefix $(SRCPATH)/,$(FC))

SRCPATH =	./src

FC =		main.c \
			lib.c \
			options.c

FCO =	$(FC:.c=.o)

FLAGS = -Wall -Wextra -Werror

FLAGS2 = -framework OpenGL -framework AppKit

INC = ./includes/
PRINTF = ./libft/includes
LIBFT = ./libft/libftcore/includes

all: $(NAME)

$(NAME): $(SRC)
	@gcc $(FLAGS2) $(FCO) ./libft/libft.a -o $(NAME)

$(SRC): makelib
	@gcc $(FLAGS)  -c $(SRC) -I $(INC) -I $(LIBFT) -I $(PRINTF)

makelib:
	@make -C ./libft

clean:
	@rm -f $(FCO)
	@make -C ./libft clean

fclean: clean
	@rm -f $(NAME)
	@make -C ./libft fclean

re: fclean all
