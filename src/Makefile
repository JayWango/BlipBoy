CXXFLAGS = -g -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter 
CXX      = g++

# These targets don't create any files:
.PHONY: blipboy clean

# Magic Variables!
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
#  $@ is the name of the target
#  $+ is a list of all the dependencies
#  $< is the first dependency

blipboy: main.o Boy.o Bullet.o Enemy.o
	${CXX} $(CXXFLAGS) -o $@ $+ -L/opt/homebrew/lib -lGL -lglut


main.o: main.cpp
	${CXX} -c -o $@ $< -I/opt/homebrew/include   

Boy.o: lib/Boy.cpp 
	${CXX} -c -o $@ $< -I/opt/homebrew/include 

Enemy.o: lib/Enemy.cpp
	${CXX} -c -o $@ $< -I/opt/homebrew/include 

Bullet.o: lib/Bullet.cpp
	${CXX} -c -o $@ $< -I/opt/homebrew/include 

clean:
	rm *.o blipboy