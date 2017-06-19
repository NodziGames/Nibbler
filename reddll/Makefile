NAME = red.so

SRC = ./*.cpp ../global.cpp ../snek.cpp ../Imain.cpp

DLL_FLAGS = -dynamiclib -flat_namespace

C_FLAGS = -Wall -Werror -Wextra -lncurses

all: $(NAME)

$(NAME):
	clang++ $(C_FLAGS) $(DLL_FLAGS) $(SRC) -o $(NAME)
	mv $(NAME) .. 

fclean:
	rm -f $(NAME)

re: fclean all