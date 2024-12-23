#include "snake.cpp"
#include "food.cpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Board {
	public:
		Board(int rows, int cols) : _rows(rows), _cols(cols), _snake() {
			Food* newFood = new Food()
		};

		void print() const {
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
		const char kWall = '#';
		const char kSpace = '.';

		Snake _snake;
		Food* _curFood = nullptr;

		void printTopBottomWalls() const {
			cout << kWall << " ";
			for (int i = 0; i < _cols; i++) {
				cout << kWall << " ";
			}
			cout << kWall << " \n";
		}

		void printBoard(const vector<vector<char>>& board) const {
			printTopBottomWalls();
			for (auto line : board) {
				cout << kWall << " ";
				for (auto characters : line) {
					cout << characters << " ";
				}
				cout << kWall << " \n";
			}
			printTopBottomWalls();
		}

		vector<vector<char>> createBoardWithoutFood() const {
			vector<vector<char>> board(_rows, vector<char>(_cols));
			for (auto& line : board) {
				for (auto& characters : line) {
					characters = kSpace;
				}
			}
			// Add the snake to the board
			for (const SnakeNode* snakeNode : _snake.body()) {
				board[snakeNode->row][snakeNode->col] = snakeNode->symbol;
			}
		}

		vector<vector<char>> createBoardWithFood() const {
			
		}
};