UP = "\033[A"
CLEAR = "\033[K"

MY_SOURCES =	main.cpp	Ball.cpp

MY_OBJECTS =  $(MY_SOURCES:.cpp=.o)

INCLUDES = includes/

NAME = kamlot

FLAGS =

STD = -std=c++2a

all: $(NAME)

.cpp.o:
	@g++ $(STD) $(FLAGS) -c $< -o $(<:.cpp=.o)
	@echo $(UP)"\033[0;93mCompiling : $@ \033[0;39m                       "

$(NAME): $(LIB) $(MY_OBJECTS)
	@clear
	@g++ $(STD) $(MY_OBJECTS) -o $(NAME) -lsfml-graphics -lsfml-window -lsfml-system
	@echo "\033[0;32m ██████╗ ██████╗ ███╗   ███╗██████╗ ██╗██╗     ███████╗██████╗     ██╗"
	@echo "██╔════╝██╔═══██╗████╗ ████║██╔══██╗██║██║     ██╔════╝██╔══██╗    ██║"
	@echo "██║     ██║   ██║██╔████╔██║██████╔╝██║██║     █████╗  ██║  ██║    ██║"
	@echo "██║     ██║   ██║██║╚██╔╝██║██╔═══╝ ██║██║     ██╔══╝  ██║  ██║    ╚═╝"
	@echo "╚██████╗╚██████╔╝██║ ╚═╝ ██║██║     ██║███████╗███████╗██████╔╝    ██╗"
	@echo " ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚═╝     ╚═╝╚══════╝╚══════╝╚═════╝     ╚═╝\033[0m"

run: all
	@./$(NAME)

clean:
	@rm -f $(MY_OBJECTS)
	@echo "\033[0;92m.o files cleaned.\033[0;39m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;92mEverything cleaned.\033[0;39m"

re: fclean all

.PHONY: all clean fclean re

