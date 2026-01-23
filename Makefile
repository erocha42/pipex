NAME 	=	pipex
LIBFT 	=	libft/libft.a
CFLAGS	=	-Wall -Wextra -Werror -g -I.

SRC 	=	parsing.c \
			utils.c

OBJ		= $(SRC:.c=.o)

$(NAME): $(LIBFT) $(OBJ)
	cc -g $(CFLAGS) $(OBJ) pipex.c $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

clean:
	$(MAKE) clean -C ./libft
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -f $(NAME)

re: fclean all
	make

.PHONY: all clean fclean re