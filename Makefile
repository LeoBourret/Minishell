NAME = minishell

CC = clang
CFLAGS = -Wall -Wextra

SRC =	main.c \
		ft_split_args.c \
		ft_split_cmd.c \
		get_next_line.c \
		utils.c \
		ft_lstnew_env.c \
		built_minishell.c \
		built_cd.c \
		built_echo.c \
		set_canonic.c \

OBJ = $(SRC:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -L. -lft -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
