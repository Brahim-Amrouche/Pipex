SRC_FILES = ${wildcard ./src/*.c}

NAME = pipex

INCLUDES = ./libft/includes ./includes

FLAGS = -Wall -Wextra -Werror $(INCLUDES)

CC = cc

SRC_OBJS = ${SRC_FILES:%.c=%.o}

%.o : %.c
	$(CC) $(INCLUDES) -c $^ -o $@

all : $(NAME)

./libft/libft.a :
	@make -C ./libft

$(NAME) : ./libft/libft.a $(SRC_OBJS)
	$(CC) $(INCLUDES) @^ -o $@

clean:
	@rm -rf $(SRC_OBJS)
	@make -C ./libft clean

fclean: clean
	@rm -rf $(NAME)
	@make -C ./libft fclean

re : fclean all

.PHONY : all clean fclean re