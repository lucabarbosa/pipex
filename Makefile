NAME		=	pipex
CC			=	cc
CFLAGS	=	-Wall -Wextra -Werror
LIBFT		=	libft/libft.a
INC		=	-I ./src -I ./libft
OBJ		=	$(patsubst src/%.c, obj/%.o, $(SRC))
SRC		=	src/pipex.c \
				src/free_exit.c \
				src/get_path.c

all:		$(LIBFT) obj $(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)
			@echo "\033[32mPipex Compiled!\033[0m"

obj:
			@mkdir -p obj

obj/%.o:	src/%.c
			$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(LIBFT):		
			@make -s -C libft
			@echo "Libft compiled!"

clean:
			@make -s $@ -C libft
			@rm -rf $(OBJ) $(LIBFT) obj
			@echo "\033[1;35mObjects deleted.\033[0m"

fclean:	clean
			@make -s fclean -C libft
			@rm -rf $(NAME)
			@echo "\033[1;36mPipex deleted.\033[0m"

re:			fclean all

.PHONY:		all bonus clean fclean re
