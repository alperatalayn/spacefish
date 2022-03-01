#include <bitset>
#include <iostream>
#include "utils.h"

int squareToIndex(Level level,
File file, Rank rank)
{
    return ((int)level+2)*81+((int)rank+2)*9+(int)file+2;
}
int ninesToFives(int index)
{
	int file=0;
	int rank=0;
	int level=0;
	level=(int)(index/81)-2;
	rank=(int)((index/9)%9)-2;
	file=(int)(index%9)-2;
	return level*25+rank*5+file;
}

Piece bitsetToPiece(std::bitset<SIZE> set)
{
	if(set.none())
	{
		return Piece::NONE;
	}
	if(set.all())
	{
		return Piece::FULL;
	}
	if(set[SIZE-1])
	{
		if(!set[0]&&!set[1]&&!set[2])
		{
			return Piece::BP;
		}else if(set[0]&&!set[1]&&!set[2])
		{
			return Piece::BN;
		}else if(!set[0]&&set[1]&&!set[2])
		{
			return Piece::BB;
		}else if(set[0]&&set[1]&&!set[2])
		{
			return Piece::BR;
		}else if(!set[0]&&!set[1]&&set[2])
		{
			return Piece::BU;
		}else if(set[0]&&!set[1]&&set[2])
		{
			return Piece::BQ;
		}else if(!set[0]&&set[1]&&set[2])
		{
			return Piece::BK;
		}
	}else
	{
		if(set[0]&&!set[1]&&!set[2])
		{
			return Piece::WP;
		}else if(!set[0]&&set[1]&&!set[2])
		{
			return Piece::WN;
		}else if(set[0]&&set[1]&&!set[2])
		{
			return Piece::WB;
		}else if(!set[0]&&!set[1]&&set[2])
		{
			return Piece::WR;
		}else if(set[0]&&!set[1]&&set[2])
		{
			return Piece::WU;
		}else if(!set[0]&&set[1]&&set[2])
		{
			return Piece::WQ;
		}else if(set[0]&&set[1]&&set[2])
		{
			return Piece::WK;
		}
	}
	return Piece::NONE;
}
