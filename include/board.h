#ifndef BOARD_H
#define BOARD_H
#define SIZE 4
#include <vector>
#include "move.h"
#include "utils.h"
class Board
{
	private:
		std::vector<std::bitset<SIZE>> boardArr;
		bool turn;
	public:
		Board();
		std::vector<std::bitset<SIZE>> getBoard();
		Piece getPieceByIndex(int);
		void initialize();
		void parseFEN(std::string);
		std::string createFEN();
		void setSquare(int, Piece);
		void printBoard();
		void move(Move);
		bool getTurn();
};


#endif 
