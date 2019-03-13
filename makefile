#OBJS specifies which files to compile as part of the project 
OBJS = src/main.c src/game.c src/game_initialization.c src/user_interface.c src/helper.c
OBJS2 = bin/main.o bin/game.o bin/game_initialization.o bin/user_interface.o bin/helper.o
#CC specifies which compiler we're using 
CC = gcc
#COMPILER_FLAGS specifies the additional compilation options we're using 
# -w suppresses all warnings 
COMPILER_FLAGS = -w -std=c11
#LINKER_FLAGS specifies the libraries we're linking against 
LINKER_FLAGS = -lSDL2 -lSDL2_image 
#OBJ_NAME specifies the name of our exectuable 
OBJ_NAME = 01_hello_SDL 
#This is the target that compiles our executable 
all:
	cc src/main.c $(COMPILER_FLAGS) $(LINKER_FLAGS) -c
	cc src/game.c $(COMPILER_FLAGS) $(LINKER_FLAGS) -c
	cc src/game_initialization.c $(COMPILER_FLAGS) $(LINKER_FLAGS) -c
	cc src/user_interface.c $(COMPILER_FLAGS) $(LINKER_FLAGS) -c
	cc src/helper.c $(COMPILER_FLAGS) $(LINKER_FLAGS) -c
	# g++ src/board.cpp $(COMPILER_FLAGS) $(LINKER_FLAGS) -c
	# g++ src/piece.cpp $(COMPILER_FLAGS) $(LINKER_FLAGS) -c
	# g++ src/TextureManager.cpp $(COMPILER_FLAGS) $(LINKER_FLAGS) -c
	make clean
	cc $(OBJS2) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o scrabble
	# make clean
	clear
main:
	cc src/main.c $(COMPILER_FLAGS) $(LINKER_FLAGS) -c
	make clean
	cc $(OBJS2) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o scrabble
	clear
game:
	cc src/game.c $(COMPILER_FLAGS) $(LINKER_FLAGS) -c
	make clean
	cc $(OBJS2) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o scrabble
	clear
# board:
# 	g++ src/board.cpp $(COMPILER_FLAGS) $(LINKER_FLAGS) -c
# 	make clean
# 	g++ $(OBJS2) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o chess
# 	clear
# piece:
# 	g++ src/piece.cpp $(COMPILER_FLAGS) $(LINKER_FLAGS) -c
# 	make clean
# 	g++ $(OBJS2) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o chess
# 	clear
# texturemanager:
# 	g++ src/TextureManager.cpp $(COMPILER_FLAGS) $(LINKER_FLAGS) -c
# 	make clean
# 	g++ $(OBJS2) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o chess
# 	clear
build:
	cc bin/main.o bin/game.o -o scrabble
	make clean
clean:
	cp *.o bin
	rm -rf *.o