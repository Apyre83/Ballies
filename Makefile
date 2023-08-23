UP			=	"\033[A"
CLEAR		=	"\033[K"


MY_SOURCES	=	src/main.cpp	\
				src/init.cpp	\
				src/Ball.cpp


MY_OBJECTS	=	$(MY_SOURCES:.cpp=.o)



INCLUDES	=	-Iinclude/ -ISFML/include

STD			=	-std=c++2a

FLAGS		=	$(STD) -Wall -Wextra -Werror $(INCLUDES) -LSFML/lib


NAME		=	ballies
PATH_BIN	=	bin/$(NAME)

all: $(PATH_BIN)

.cpp.o:
	@g++ $(FLAGS) -c $< -o $(<:.cpp=.o)
	@echo $(UP)"\033[0;93mCompiling : $@ \033[0;39m                       "

$(PATH_BIN): $(LIB) $(MY_OBJECTS)
	@clear
	@echo "\033[34mPassword required to move the SFML libraries to /usr/lib/"
	@sudo cp SFML/lib/libsfml-*.so.3.0 /usr/lib/
	@clear
	@g++ $(MY_OBJECTS) -o $(NAME) -LSFML/lib -lsfml-graphics -lsfml-window -lsfml-system
	@mkdir -p bin
	@mv $(NAME) bin/
	@echo "\033[0;32m ██████╗ ██████╗ ███╗   ███╗██████╗ ██╗██╗     ███████╗██████╗     ██╗"
	@echo "██╔════╝██╔═══██╗████╗ ████║██╔══██╗██║██║     ██╔════╝██╔══██╗    ██║"
	@echo "██║     ██║   ██║██╔████╔██║██████╔╝██║██║     █████╗  ██║  ██║    ██║"
	@echo "██║     ██║   ██║██║╚██╔╝██║██╔═══╝ ██║██║     ██╔══╝  ██║  ██║    ╚═╝"
	@echo "╚██████╗╚██████╔╝██║ ╚═╝ ██║██║     ██║███████╗███████╗██████╔╝    ██╗"
	@echo " ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚═╝     ╚═╝╚══════╝╚══════╝╚═════╝     ╚═╝"
	@echo "\033[0;92mSee $(PATH_BIN) for the executable.\033[0m"

run: all
	@./$(PATH_BIN)

clean:
	@rm -f $(MY_OBJECTS)
	@echo "\033[0;92m.o files cleaned.\033[0;39m"

fclean: clean
	@rm -f $(PATH_BIN)
	@echo "\033[0;92mEverything cleaned.\033[0;39m"

re: fclean all

.PHONY: all clean fclean re

