#include "snake.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Board {
	public:
		Board(int rows, int cols) : _rows(rows), _cols(cols), _snake() {};

		void print() const {
			vector<vector<string>> board(_rows, vector<string>(_cols));
			for (auto& line : board) {
				for (auto& characters : line) {
					characters = kSpace;
				}
			}
			// Add the snake to the board
			for (const SnakeNode* snakeNode : _snake.body()) {
				board[snakeNode->row][snakeNode->col] = snakeNode->symbol;
			}
			// Add the food to the board
			printBoard(board);
		}

		void clear() const {
			cout << "\033[2J\033[H";
		}

		void moveSnake(Direction direction) {
			_snake.move(direction, _rows, _cols);
		}

	private:
		// Size of the board
		int _rows;
		int _cols;
		// Board characters
		const string kWall = "# ";
		const string kSpace = ". ";

		Snake _snake;

		void printTopBottomWalls() const {
			cout << kWall;
			for (int i = 0; i < _cols; i++) {
				cout << kWall;
			}
			cout << kWall << "\n";
		}

		void printBoard(const vector<vector<string>>& board) const {
			printTopBottomWalls();
			for (auto line : board) {
				cout << kWall;
				for (auto characters : line) {
					cout << characters;
				}
				cout << kWall << "\n";
			}
			printTopBottomWalls();
		}

};