gameplay.o: gameplay.cpp gamemap.h
	g++ -c gameplay.cpp

gamemap.o: gamemap.cpp gamemap.h
	g++ -c gamemap.cpp

character.o: character.cpp character.h
	g++ -c character.cpp

game: gameplay.o gamemap.o character.o
	g++ gameplay.o gamemap.o character.o -o game
