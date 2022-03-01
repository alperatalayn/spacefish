#ifndef ENGINE_H
#define ENGINE_H
#include "board.h"
#include "generator.h"
#include "move.h"
class Engine{
	public:
		int heuristicEval(Board, Generator*);
		Move search(Board,int, int, int,Generator*);
};
#endif
