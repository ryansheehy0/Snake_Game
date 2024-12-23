#include <vector>
#include <string>
#include <random>

using namespace std;

class Food {
	public:
		Food(vector<vector<char>> board, int snakeLength) {
			int rows = board.size();
			int cols = board[0].size();
			int numOfEmptySpaces = rows * cols - snakeLength;
			int randomEmptySpace = randomNum() * numOfEmptySpaces;
			// Loop through each of the board squares to find the empty spaces
			int emptySpaceI = 0;
			for (int rowI = 0; rowI < rows; rowI++) {
				for (int colI = 0; colI < cols; colI++) {
					char character = board[rowI][colI];
					if (character == '.') { // Found empty space
						if (emptySpaceI == randomEmptySpace) { // Is the empty space the randomly chosen one?
							_row = rowI;
							_col = colI;
							break;
						}
						emptySpaceI++;
					}
				}
			}
		}

		int row() const { return _row; }
		int col() const { return _col; }

	private:
		int _row;
		int _col;
		char _symbol = 'o';

		double randomNum() const {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> dis(0.0, 1.0);
			return dis(gen);
		}
};