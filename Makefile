NAME = minishell

CC = clang
CFLAGS = -Wall -Wextra

SRC = main.c \
	  ft_split_args.c \
	  ft_split_cmd.c \
	  get_next_line.c \
		utils.c
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
