NAME = program
FLAGS = -O3
SRC = main.cpp $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
GCC = g++

all: $(NAME)

$(NAME): $(OBJ)
	@$(GCC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	@$(GCC) $(FLAGS) -Iinclude -c $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
