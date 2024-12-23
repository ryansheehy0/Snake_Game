#include <list>
#include <string>
#include <iostream>

using namespace std;

enum class Direction {
	kUp, kLeft, kRight, kDown
};

struct SnakeNode {
	int row;
	int col;
	char symbol;

	SnakeNode() {};
	SnakeNode(int row, int col, char symbol) : row(row), col(col), symbol(symbol) {}
};

class Snake {
	public:
		Snake() {
			SnakeNode* body1 = new SnakeNode(0, 0, '+');
			SnakeNode* body2 = new SnakeNode(0, 1, '+');
			SnakeNode* head = new SnakeNode(0, 2, '@');
			_snake.push_front(body1);
			_snake.push_front(body2);
			_snake.push_front(head);
		}
		~Snake() {
			for (auto& ele : _snake) {
				delete ele;
			}
		}

		void eat() {
			_hasEaten = true;
		}

		void move(Direction direction, int rows, int cols, bool safeMove = true) {
			// Create new head's row an col
			int newHeadRow = _snake.front()->row;
			int newHeadCol = _snake.front()->col;
			switch (direction) {
				case Direction::kUp:
					newHeadRow--;
					break;
				case Direction::kLeft:
					newHeadCol--;
					break;
				case Direction::kRight:
					newHeadCol++;
					break;
				case Direction::kDown:
					newHeadRow++;
					break;
			}
			// Check if it hit a wall or intersects with the body
			if (newHeadRow < 0 ||
				  newHeadCol < 0 ||
					newHeadRow == rows ||
					newHeadCol == cols ||
					intersects(newHeadRow, newHeadCol)
			) {
				if (safeMove) return;
				cout << "You died.\n";
			}
			// Change the symbol of the previous head
			_snake.front()->symbol = '+';
			// Create new head
			SnakeNode* newHead = new SnakeNode(newHeadRow, newHeadCol, '@');
			_snake.push_front(newHead);
			// Move the tail
			if (_hasEaten) {
				_hasEaten = false;
				return;
			} else { // Remove the tail
				delete _snake.back();
				_snake.pop_back();
			}
		}

		bool intersects(int row, int col) const {
			for (SnakeNode* node : _snake) {
				if (node->row == row && node->col == col) return true;
			}
			return false;
		}

		const list<SnakeNode*>& body() const {
			return _snake;
		}

	private:
		int _headRow;
		int _headCol;
		list<SnakeNode*> _snake;
		Direction _direction;
		// int _length = 3;
		bool _hasEaten = false;
};