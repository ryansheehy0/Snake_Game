#include <iostream>
#include <string>
#include "board.cpp"
#include <termios.h>
#include <unistd.h>

using namespace std;

char usersMove();

const int kRows = 20;
const int kCols = 30;

int main() {
	Board board = Board(kRows, kCols);
	board.print();
	// Game loop
	while (true) {
		Direction userDirection;
		char userInput = usersMove();
		switch (userInput) {
			case 'w':
				userDirection = Direction::kUp;
				break;
			case 'a':
				userDirection = Direction::kLeft;
				break;
			case 'd':
				userDirection = Direction::kRight;
				break;
			case 's':
				userDirection = Direction::kDown;
				break;
		}
		board.moveSnake(userDirection);
		board.clear();
		board.print();
	}
}

char usersMove() {
	struct termios oldt, newt;
	char ch;
	// Get the current terminal attributes
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	// Disable canonical mode and echoing
	newt.c_lflag &= ~(ICANON | ECHO);
	// Apply the new terminal settings
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	// Read one character
	ch = getchar();
	// Restore the old terminal settings
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}