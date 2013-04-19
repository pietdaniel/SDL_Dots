objects = Main.o Global.o Timer.o Dot.o
flags = -lSDL -lSDL_ttf -lSDL_image

all: prgm

prgm : $(objects)
	g++ -o prgm $(objects) $(flags)
Main.o : Main.cpp Global.h Timer.h Dot.h
	g++ -c Main.cpp $(flags)
Timer.o : Timer.cpp Timer.h Global.h
	g++ -c Timer.cpp $(flags)
Dot.o : Dot.cpp Dot.h Global.h
	g++ -c Dot.cpp $(flags)
Global.o : Global.cpp Global.h
	g++ -c Global.cpp $(flags)
clean :
	rm *.o
	rm prgm
	rm log
