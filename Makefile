all:
	rm -f autour.exe autour autour.lex.cpp autour.bison.cpp autour.bison.h
	bison -d autour.y -o autour.bison.cpp
	flex -o autour.lex.cpp autour.l
	g++ -w *.cpp src/*.cpp -o autour `sdl2-config --libs --cflags` -ggdb3 -O0 -Wall -lSDL2_image -lm
	./autour demo/jeu_de_la_vie.autour