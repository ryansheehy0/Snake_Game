#include <iostream>
#include <string>
#include "board.cpp"
#include <termios.h>
#include <unistd.h>

using namespace std;

char usersMove();

const int kRows = 12;
const int kCols = 12;

int main() {
	Board board = Board(kRows, kCols);
	// Game loop
	while (true) {
		board.clear();
		board.print();
		Direction userDirection;
		switch (usersMove()) {
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
		if (!board.moveSnake(userDirection)) {
			board.printScore();
			break;
		}
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