NAME = sneksnak
SRCS = -lncurses *.cpp
FLAGS = -Wall -Wextra -Werror

LIB_FILES = red.so blue.so green.so

$(NAME):
	make -C ./bluedll
	make -C ./reddll
	make -C ./greendll
	clang++ -o $(NAME) $(SRCS) $(FLAGS)

cleanlib:
	rm -rf $(LIB_FILES)

clean: cleanlib
	rm -rf $(NAME)

re: clean $(NAME)
