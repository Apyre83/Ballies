# Nom de votre fichier source (sans extension)
SOURCE = src/main src/init src/Ball

# Chemin vers les bibliothèques SFML
SFML_LIB_PATH = SFML/lib
SFML_INCLUDE_PATH = SFML/include

# Options de liaison (liens vers les bibliothèques SFML)
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system





# Cibles et règles
all: $(SOURCE)

$(SOURCE): $(SOURCE).cpp
	g++ -o $@ $< -L$(SFML_LIB_PATH) $(SFML_LIBS) -I$(SFML_INCLUDE_PATH) -Iinclude/

clean:
	del $(SOURCE).exe
