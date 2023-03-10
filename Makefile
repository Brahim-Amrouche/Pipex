SRC_FILES =  ./src/exit_pipex.c  ./src/parsing/bonus_parser.c ./src/parsing/parser.c \
./src/parsing/parser_helper.c ./src/parsing/separtor_functions.c ./src/process/main_process.c ./src/utils/close_fd.c \
./src/utils/duplicat_util.c ./src/utils/join_util.c ./src/utils/putstr.c ./src/utils/split_util.c ./src/utils/strncmp.c ./src/utils/substr.c

NAME = pipex

INCLUDES = -I./includes -I./libft/includes 

FLAGS = -Wall -Wextra -Werror $(INCLUDES)

CC = cc

SRC_OBJS = ${SRC_FILES:%.c=%.o}

MAIN_FILE = ${SRC_FILES:./src/main.c=%.o}

BONUS_MAIN_FILE = ${SRC_FILES:./src/bonus_main.c=%.o}

%.o : %.c
	$(CC) $(FLAGS) -c $^ -o $@

all : $(NAME)

./libft/libft.a :
	@make -C ./libft

$(NAME) : ./libft/libft.a  ./src/main.o $(SRC_OBJS)
	if test -f ./src/bonus_main.o ; \
     then rm -rf ./src/bonus_main.o ; \
     fi
	$(CC) $(FLAGS) $^ -o $@

clean:
	@rm -rf $(SRC_OBJS) ./src/main.o ./src/bonus_main.o
	@make -C ./libft clean

fclean: clean
	@rm -rf $(NAME)
	@make -C ./libft fclean

bonus : ./libft/libft.a  ./src/bonus_main.o $(SRC_OBJS)
	if test -f ./src/main.o ; \
     then rm -rf ./src/main.o ; \
     fi
	$(CC) $(FLAGS) $^ -o $(NAME)

re : fclean all

.PHONY : all clean fclean re