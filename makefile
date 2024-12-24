snake: snake.o board.o snake_game.o food.o
	g++ snake.o board.o snake_game.o food.o -o snake

food.o: food.cpp
	g++ -c food.cpp

snake.o: snake.cpp
	g++ -c snake.cpp

board.o: board.cpp snake.cpp food.cpp
	g++ -c board.cpp snake.cpp food.cpp

snake_game.o: snake_game.cpp board.cpp snake.cpp food.cpp
	g++ -c snake_game.cpp board.cpp snake.cpp food.cpp

clean:
		rm -rf *.o snake