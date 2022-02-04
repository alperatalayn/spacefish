#ifndef GENERATOR_H
#define GENERATOR_H

#include "move.h"
#include "utils.h"
#include <iostream>
#include <queue>

class Generator
{
	public:
		std::queue<Move> pLegal(std::vector<std::bitset<SIZE>>,bool);
		void printMoves(std::queue<Move>);
		bool isCheck(std::vector<std::bitset<SIZE>>,bool turn);
		std::queue<Move> legal(std::vector<std::bitset<SIZE>>,bool);
};

#endif
