UP			=	"\033[A"
CLEAR		=	"\033[K"


MY_SOURCES	=	src/main.cpp	\
				src/Ball.cpp


MY_OBJECTS	=	$(MY_SOURCES:.cpp=.o)



INCLUDES	=	include/

STD			=	-std=c++2a

FLAGS		=	$(STD) -Wall -Wextra -Werror -I $(INCLUDES)


NAME		=	ballies


all: $(NAME)

.cpp.o:
	@g++ $(FLAGS) -c $< -o $(<:.cpp=.o)
	@echo $(UP)"\033[0;93mCompiling : $@ \033[0;39m                       "

$(NAME): $(LIB) $(MY_OBJECTS)
	@clear
	@g++ $(MY_OBJECTS) -o $(NAME) -lsfml-graphics -lsfml-window -lsfml-system
	@mv $(NAME) bin/
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
	@rm -f bin/$(NAME)
	@echo "\033[0;92mEverything cleaned.\033[0;39m"

re: fclean all

.PHONY: all clean fclean re

