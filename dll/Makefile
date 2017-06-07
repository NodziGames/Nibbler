NAME = MinMax.so

SRC = src/minMax.cpp

OBJ = ./*.o

C_FLAGS = -Wall -Werror -Wextra

DLL_FLAGS = -dynamiclib -flat_namespace

all: $(NAME)


$(NAME):
	@echo "Compiling into library $(NAME)."
	@g++ $(C_FLAGS) $(DLL_FLAGS) $(SRC) -o $(NAME)

clean:
	@echo "Removing all obj files..."
	@rm -f $(OBJ)

fclean: clean
	@echo "Removing $(name)"
	@rm -f $(NAME)

re: fclean all