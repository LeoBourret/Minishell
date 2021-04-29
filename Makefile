NAME = minishell

RED="\033[0;31m"
GRN="\033[1;32m"
YLW="\033[0;33m"
END="\033[0m"

DIR_BUILTIN = builtin/
DIR_SRCS = srcs/

CC = clang

SRC_BUILTIN =	built_cd.c \
				built_echo.c \
				built_export.c \
				built_env.c \
				built_pwd.c \
				built_exec.c \
				built_exit.c \
				built_unset.c \

SRC_SRCS =	main.c \
		ft_split_args.c \
		ft_split_cmd.c \
		get_next_line.c \
		utils.c \
		ft_lstnew_env.c \
		built_minishell.c \
		set_canonic.c \

SRC = 	$(addprefix $(DIR_SRCS), $(SRC_SRCS)) \
		$(addprefix $(DIR_BUILTIN), $(SRC_BUILTIN))

OBJ = $(SRC:.c=.o)

RM = rm -f

all: $(NAME)

libft: 
	@echo $(YLW) "[Libft compilation...]"
	@make -C libft/
	@echo $(GRN)"[Libft done !]"

$(NAME):	libft $(OBJ) 
	@echo $(YLW)"[Minishell compilation...]"
	@$(CC) $(OBJ) -I libft/ -lft -L libft/ -o $(NAME)
	@echo $(GRN)"[Minishell ready !]"

clean:
	@echo $(RED)"[Libft remove...]"
	@make fclean -C libft
	@$(RM) libft.a
	@$(RM) libft.h
	@echo $(RED)"[Minishell remove...]"
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
