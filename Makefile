SRC_FILES = ${wildcard ./src/*.c} ${wildcard ./src/**/*.c}

NAME = pipex

INCLUDES = -I./includes -I./libft/includes 

FLAGS = -Wall -Wextra -fsanitize=address $(INCLUDES)

CC = cc

SRC_OBJS = ${SRC_FILES:%.c=%.o}

%.o : %.c
	$(CC) $(FLAGS) -c $^ -o $@

all : $(NAME)

./libft/libft.a :
	@make -C ./libft

$(NAME) : ./libft/libft.a $(SRC_OBJS)
	$(CC) $(FLAGS) $^ -o $@

clean:
	@rm -rf $(SRC_OBJS)
	@make -C ./libft clean

fclean: clean
	@rm -rf $(NAME)
	@make -C ./libft fclean

re : fclean all

.PHONY : all clean fclean re