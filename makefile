UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
		HEAD := \"sdlheaders/mac.hpp\"
  	CCFLAGS= -framework SDL2 -framework SDL2_image -framework SDL2_ttf
else
		HEAD := \"sdlheaders/linux.hpp\"
		CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf
endif

all: test src/rsdl.o head

test: main.o src/rsdl.o button.o menu.o  user.o game.o ball.o brick.o
	g++ -g main.o rsdl.o menu.o game.o user.o button.o ball.o brick.o  $(CCFLAGS) -o test

main.o: main.cpp menu.cpp
	g++ -c -std=c++11 main.cpp menu.cpp
menu.o: menu.hpp menu.cpp user.hpp button.hpp game.hpp 
	g++ -c -std=c++11 menu.cpp 
user.o: user.hpp user.cpp
	g++ -c user.cpp
button.o: button.hpp button.cpp
	g++ -c button.cpp src/rsdl.cpp 
game.o: game.hpp game.cpp user.hpp ball.hpp brick.hpp
	g++ -c -std=c++11 game.cpp 
ball.o: ball.hpp ball.cpp
	g++ -c -std=c++11 ball.cpp src/rsdl.cpp  
brick.o: brick.hpp brick.cpp
	g++ -c -std=c++11 brick.cpp src/rsdl.cpp  
rsdl.o: src/rsdl.hpp src/rsdl.cpp
	g++ -c src/rsdl.cpp -o src/rsdl.o

head:
		echo "#include "$(HEAD) > ./src/sdlHeaders.hpp
clean:
	rm -r *.o
