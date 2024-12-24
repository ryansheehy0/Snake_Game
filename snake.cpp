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
			SnakeNode* body1 = new SnakeNode(0, 0, kBodySymbol);
			SnakeNode* body2 = new SnakeNode(0, 1, kBodySymbol);
			SnakeNode* head = new SnakeNode(0, 2, kHeadSymbol);
			_body.push_front(body1);
			_body.push_front(body2);
			_body.push_front(head);
		}
		~Snake() {
			for (auto& ele : _body) {
				delete ele;
			}
		}

		void eat() {
			_hasEaten = true;
			_length++;
		}

		bool move(Direction direction, int rows, int cols) {
			// Create new head's row an col
			int newHeadRow = _body.front()->row;
			int newHeadCol = _body.front()->col;
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
				return false;
			}
			// Change the symbol of the previous head
			_body.front()->symbol = kBodySymbol;
			// Create new head
			SnakeNode* newHead = new SnakeNode(newHeadRow, newHeadCol, kHeadSymbol);
			_body.push_front(newHead);
			// Move the tail
			if (_hasEaten) {
				_hasEaten = false;
			} else { // Remove the tail
				delete _body.back();
				_body.pop_back();
			}
			// The move was successful
			return true;
		}

		bool intersects(int row, int col) const {
			for (SnakeNode* node : _body) {
				if (node->row == row && node->col == col) return true;
			}
			return false;
		}

		bool intersectsHead(int row, int col) const {
			return (_body.front()->row == row && _body.front()->col == col);
		}

		const list<SnakeNode*>& body() const {
			return _body;
		}

		int length() const { return _length; }

	private:
		// Snake's symbols
		const char kHeadSymbol = '@';
		const char kBodySymbol = '+';
		// Other snake info
		list<SnakeNode*> _body;
		int _length = 3;
		bool _hasEaten = false;
};