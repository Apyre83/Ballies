MY_SOURCES	=	src\main.cpp	\
				src\init.cpp	\
				src\Ball.cpp


MY_OBJECTS	=	$(MY_SOURCES:.cpp=.o)


INCLUDES	=	-Iinclude/ -ISFML/include

STD			=	-std=c++2a

FLAGS		=	$(STD) -Wall -Wextra -Werror $(INCLUDES) -LSFML/lib


NAME		=	ballies.exe
PATH_BIN	=	bin\$(NAME)

all: $(PATH_BIN)

.cpp.o:
	@g++ $(FLAGS) -c $< -o $(<:.cpp=.o)
	@echo Compiling : $@

$(PATH_BIN): $(LIB) $(MY_OBJECTS)
	@cls
	@g++ $(MY_OBJECTS) -o $(NAME) -LSFML/lib -lsfml-graphics -lsfml-window -lsfml-system
	@if not exist bin mkdir bin
	@move $(NAME) bin/
	@echo Compiled !

	@echo See $(PATH_BIN) for the executable.

run: all
	@./$(PATH_BIN)

clean:
	@del $(MY_OBJECTS)
	@echo .o files cleaned.

fclean: clean
	@del $(PATH_BIN)
	@echo Everything cleaned.

re: fclean all

.PHONY: all clean fclean re

