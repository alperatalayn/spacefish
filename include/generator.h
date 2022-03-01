#ifndef GENERATOR_H
#define GENERATOR_H

#include "move.h"
#include "utils.h"
#include "board.h"
#include <iostream>
#include <queue>

class Generator
{
	public:
		std::queue<Move> pLegal(Board);
		void printMoves(std::queue<Move>);
		bool isCheck(Board);
		bool isCheckMate(Board);
		Board afterMove(Board,Move);
		std::queue<Move> legal(Board);
		std::queue<Move> legalToRootFive(Board);
};

#endif
