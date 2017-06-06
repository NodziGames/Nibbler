NAME = nibblers

SRC = src/main.cpp

OBJ = *.o

C_FLAGS = -Wall -Werror -Wextra

all: $(NAME)


$(NAME):
	@echo "Compiling all files"
	@g++ $(C_FLAGS) $(SRC)
	@g++ $(C_FLAGS) $(OBJ) -o $(NAME)
	@echo "Compiled all files..."

clean:
	@echo "Removing all obj files..."
	@rm -f $(OBJ)

fclean: clean
	@echo "Removing executable: $(NAME)"
	@rm -f $(NAME)

re: fclean all