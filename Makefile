NAME = sneksnak
SRCS = -lncurses *.cpp
FLAGS = -Wall -Wextra -Werror

$(NAME):
	clang++ -o $(NAME) $(SRCS) $(FLAGS)

clean:
	rm -rf $(NAME)

re: clean $(NAME)
