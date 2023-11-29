# BlipBoy : CS 32 Arcade Project

## What the project does, and why: 


## How to build the project:
Run the following commands to build/run the project:

```
g++ -c main.cpp -o main.o -I/opt/homebrew/include   

g++ -c lib/Enemy.cpp -o Enemy.o -I/opt/homebrew/include  

g++ main.o Enemy.o -o my_program -L/opt/homebrew/lib -lGL -lglut

DISPLAY=:0 ./my_program    
```

## How to use the executables once they're built:


## An overview of how the code is organized:




