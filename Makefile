NAME = minishell

RED="\033[0;31m"
YLW="\033[0;33m"
END="\033[0m"

SRCS_DIR_BUILTIN = builtin/
SRCS_DIR_SRCS = srcs/

CC = clang
CFLAGS = -Wall -Wextra -Werror

SRC_BUILTIN =	built_cd.c \
				built_echo.c \

SRC =	main.c \
		ft_split_args.c \
		ft_split_cmd.c \
		get_next_line.c \
		utils.c \
		ft_lstnew_env.c \
		built_minishell.c \
		set_canonic.c \

SRCS_A = $(addprefix $(SRCS_DIR_SRCS), $(SRCS))
SRCS_B = $(addprefix $(SRCS_DIR_BUILTIN), $(SRCS_BUILTIN))

OBJ = $(SRC_A:.c=.o) $(SRC_B:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -L. -lft -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(NAME_A) : $(OBJSRCS_A)
	@echo $(YLW)"[Libft compilation...]"
	@make -C libft
	@echo $(RED)"[Remove last version...]"
	@rm -rf checker
	@echo $(YLW)"[Checker compilation..]"
	@gcc $(SRCS_A) -I libft/ -lft -L libft/ -o $(NAME_A)
	@echo $(RED)"[Done !]"
	@echo $(END)
	@echo $(RED)"[Remove last version...]"
	@rm -rf push_swap
	@echo $(YLW)"[Push_swap compilation..]"
	@gcc $(SRCS_B) -I libft/ -lft -L libft/ -o $(NAME_B)
	@echo $(RED)"[Done !]"
	@echo $(END)



$(NAME_B) : $(OBJSRCS_B)
	@echo $(YLW)"[Libft compilation...]"
	@make -C libft

all : $(NAME_B) $(NAME_A)

clean :
	@rm -rf $(OBJSRCS_A)
	@rm -rf $(OBJSRCS_B)
