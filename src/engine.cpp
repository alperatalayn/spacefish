#include <iostream>
#include "engine.h"
#include "utils.h"
#include "board.h"
#include "move.h"
#include "generator.h"
#include <bitset>
#include <queue>
int Engine::heuristicEval(Board b,Generator *g)
{
	int score = 0;
	std::vector<std::bitset<SIZE>> boardArr;
	boardArr= b.getBoard();
	/*
	if(g->isCheckMate(b))
	{
		if(b.getTurn())
		{
			score +=int(Value::MATE);
		}
		else
		{
			score -=int(Value::MATE);
		}
	}
	if(g->isCheck(b))
		{
			if(b.getTurn())
			{
				score +=int(Value::WP);
			}
			else
			{
				score -=int(Value::WP);
			}
		}
	*/
	while(!boardArr.empty())
    {
        Piece currentPiece=bitsetToPiece(boardArr.back());
        boardArr.pop_back();
        switch(currentPiece)
        {
            case Piece::WP:
            	score+=(int)Value::WP;
                break;
            case Piece::WB:
                score+=(int)Value::WB;
                break;
            case Piece::WR:
                score+=(int)Value::WR;
                break;
            case Piece::WU:
                score+=(int)Value::WU;
                break;
            case Piece::WN:
                score+=(int)Value::WN;
                break;
            case Piece::WQ:
                score+=(int)Value::WQ;
                break;
            case Piece::WK:
                score+=(int)Value::WK;
                break;
            case Piece::BP:
                score+=(int)Value::BP;
                break;
            case Piece::BN:
                score+=(int)Value::BN;
                break;
            case Piece::BB:
                score+=(int)Value::BB;
                break;
            case Piece::BU:
                score+=(int)Value::BU;
                break;
            case Piece::BR:
                score+=(int)Value::BR;
                break;
            case Piece::BQ:
                score+=(int)Value::BQ;
                break;
            case Piece::BK:
               	score+=(int)Value::BK;
                break;
            case Piece::FULL:
            	break;
            case Piece::NONE:
            	break;
        }
    }
    return score;
}

Move Engine::search(Board position,int depth
, int alpha, int beta,Generator *g)
{
	Move bestMove;
	if (depth == 0)
	{
		bestMove.eval=heuristicEval(position,g);
		return bestMove;
	}
	std::queue<Move> legals = g->pLegal(position);
	if (position.getTurn())
	{
		bestMove.eval = -3000;
		while(!legals.empty())
		{
			Move currentMove = legals.front();
			legals.pop();
			Move tempBest=search(g->afterMove(position,currentMove), depth - 1, alpha, beta,g);
			if (tempBest.eval>bestMove.eval)
			{
				currentMove.eval=tempBest.eval;
				bestMove=currentMove;
			}
			if (bestMove.eval>alpha)
			{
				alpha=bestMove.eval;
			}
			if (beta <= alpha)
				break;
		}
		return bestMove;
 	}
 	else
 	{
 		bestMove.eval = 3000;
 		while(!legals.empty())
 		{
 			Move currentMove = legals.front();
			legals.pop();
 			Move tempBest = search(g->afterMove(position,currentMove), depth - 1, alpha, beta,g);
 			if (tempBest.eval<bestMove.eval)
			{
				currentMove.eval=tempBest.eval;
				bestMove=currentMove;
			}
 			if (bestMove.eval<beta)
 			{
 				beta=bestMove.eval;
 			}
 			if (beta <= alpha)
 				break;
 		}
 		return bestMove;
  	}
}
