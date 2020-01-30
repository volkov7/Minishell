NAME = minishell

LIB = -lft -L./libft

SRCS_DIR = ./srcs/

FLAGS = -Wall -Wextra -Werror

SRCS = shell \
		cd_builtin \
		echo_builtin \
		exec_commands \
		get_input \
		set_unset_env \
		clean \
		environment \
		execution \
		misk \
	   

HEADER = 	-I./include \
			-I./libft \
			
OBJ =	$(addprefix obj/, $(addsuffix .o, $(SRCS)))

all: $(NAME)

obj/%.o: srcs/%.c
	@gcc -c $< $(HEADER) -o $@
	
$(NAME): obj $(OBJ)
	@tput setaf 7; tput bold; echo "Compiling LIB"
	@make -C libft
	@tput setaf 7; tput bold; echo "Compiling minishell"
	@gcc $(OBJ) $(HEADER) -o $(NAME) $(LIB)
	@tput setaf 2; tput bold; echo "DONE minishell"

obj:
	@mkdir obj

clean:
	@make -C libft clean
	@rm -rf obj
	@tput setaf 6; tput bold; echo "DONE Clean!"
	
fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)
	@tput setaf 6; tput bold; echo "DONE Fclean!"

re: fclean all
.PHONY: all clean fclean re