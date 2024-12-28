#include "snake.cpp"
#include "food.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <optional>

using namespace std;

class Board {
	public:
		Board(int rows, int cols) : _rows(rows), _cols(cols), _snake() {};

		void print() {
			printBoard(createBoard());
		}

		void clear() const {
			cout << "\033[2J\033[H";
		}

		bool moveSnake(Direction direction) {
			bool successfulMove = _snake.move(direction, _rows, _cols);
			if (_food) {
				if (_snake.intersectsHead(_food->row(), _food->col())) {
					_snake.eat();
					_food = nullopt;
				}
			}
			numOfTurns++;
			return successfulMove;
		}

		bool aStarMoveSnake() {
			static int foodRow = 0;
			static int foodCol = 0;
		}

		void printScore() const {
			cout << "Snake length: " << _snake.length() << "/" << (_rows * _cols) << "\n";
			cout << "Num of turns: " << numOfTurns << "\n";
		}

	private:
		// Size of the board
		int _rows;
		int _cols;
		// Board characters
		const char kWallSymbol = '#';
		const char kSpaceSymbol = '.';
		// Parts in the board
		Snake _snake;
		optional<Food> _food = nullopt;
		int numOfTurns = 0;

		void printTopBottomWalls() const {
			cout << kWallSymbol << " ";
			for (int i = 0; i < _cols; i++) {
				cout << kWallSymbol << " ";
			}
			cout << kWallSymbol << " \n";
		}

		void printBoard(const vector<vector<char>>& board) const {
			printTopBottomWalls();
			for (auto line : board) {
				cout << kWallSymbol << " ";
				for (auto characters : line) {
					cout << characters << " ";
				}
				cout << kWallSymbol << " \n";
			}
			printTopBottomWalls();
		}

		vector<vector<char>> createBoard() {
			vector<vector<char>> board(_rows, vector<char>(_cols));
			// Fill board with spaces
			for (auto& line : board) {
				for (auto& characters : line) {
					characters = kSpaceSymbol;
				}
			}
			// Add the snake to the board
			for (const SnakeNode* snakeNode : _snake.body()) {
				board[snakeNode->row][snakeNode->col] = snakeNode->symbol;
			}
			// If there is not food, create it
			if (!_food) {
				_food.emplace(board, _snake.length(), kSpaceSymbol);
			}
			// Add food to the board
			board[_food->row()][_food->col()] = _food->symbol();
			// Return board
			return board;
		}
};