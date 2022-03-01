#include<iostream>
#include<queue>
#include<bitset>
#include<string>
#include "generator.h"
#include "board.h"
#include "utils.h"
NMove nMoveArr[]={NMove::LUU,NMove::RUU,NMove::FUU,
	NMove::DFF,NMove::DRR,NMove::DLL,NMove::DBB,
	NMove::UFF,NMove::URR,NMove::ULL,NMove::UBB,
	NMove::LDD,NMove::RDD,NMove::FDD,NMove::BDD,
	NMove::LFF,NMove::LBB,NMove::BLL,NMove::BRR,
	NMove::RFF,NMove::RBB,NMove::FLL,NMove::FRR,
	NMove::BUU};

std::queue<Move> Generator::pLegal(Board b)
{
	std::vector<std::bitset<SIZE>> boardArr = b.getBoard();
	bool turn = b.getTurn();
	std::queue<Move> moves;
	Move temp;
	Piece currentPiece;
	std::queue<Direction> dirArr;
	std::queue<NMove> nMoveQ;
	for(int i=0;i<729;i++)
	{
		if(!boardArr[i].none()&&!boardArr[i].all())
		{
			if(boardArr[i][SIZE-1]!=turn)
			{
				//Sliding pieces
				currentPiece=bitsetToPiece(boardArr[i]);
				if(currentPiece==Piece::WQ
				||currentPiece==Piece::WR
				||currentPiece==Piece::BQ
				||currentPiece==Piece::BR)
				{
					dirArr.push(Direction::D);
					dirArr.push(Direction::U);
					dirArr.push(Direction::L);
					dirArr.push(Direction::R);
					dirArr.push(Direction::B);
					dirArr.push(Direction::F);
				}
				if(currentPiece==Piece::WB
				||currentPiece==Piece::WQ
				||currentPiece==Piece::BB
				||currentPiece==Piece::BQ)
				{
					dirArr.push(Direction::DL);
					dirArr.push(Direction::DR);
					dirArr.push(Direction::DF);
					dirArr.push(Direction::DB);
					dirArr.push(Direction::UL);
					dirArr.push(Direction::UR);
					dirArr.push(Direction::UF);
					dirArr.push(Direction::UB);
					dirArr.push(Direction::LF);
					dirArr.push(Direction::LB);
					dirArr.push(Direction::RF);
					dirArr.push(Direction::RB);
				}
				if(currentPiece==Piece::WU
				||currentPiece==Piece::BU)
				{
					dirArr.push(Direction::ULF);
					dirArr.push(Direction::ULB);
					dirArr.push(Direction::URF);
					dirArr.push(Direction::URB);
					dirArr.push(Direction::DLF);
					dirArr.push(Direction::DLB);
					dirArr.push(Direction::DRF);
					dirArr.push(Direction::DRB);  
				}
				while(!dirArr.empty())
				{
					Direction dir=dirArr.front();
					dirArr.pop();
					int j=i;
					while(true)
					{
						j+=dir;
						if(boardArr[j].all())
						{
							break;
						}
						else if(boardArr[j].none())
						{
							temp.setSrc(i);
							temp.setDest(j);
							moves.push(temp);
						}
						else if(!boardArr[j].none()
						&&(boardArr[j][SIZE-1]
						!=boardArr[i][SIZE-1]))
						{
							temp.setSrc(i);
							temp.setDest(j);
							moves.push(temp);
							break;		
						}
						else
						{
							break;
						}
						
					}
				}
				//Knights
				if(currentPiece==Piece::WN
				||currentPiece==Piece::BN)
				{
					for(NMove n:nMoveArr)
					{
						int j=i;
						j+=n;
						if(!boardArr[j].all()
						&&((boardArr[j][SIZE-1]
						!=boardArr[i][SIZE-1])
						||boardArr[j].none()))
						{
							temp.setSrc(i);
							temp.setDest(j);
							moves.push(temp);	
						}
					}
					
				}
				//Pawns
					//White Pawn
				if(currentPiece==Piece::WP)
				{
					//Non-capture moves
					dirArr.push(Direction::U);
					dirArr.push(Direction::F);
					while(!dirArr.empty())
					{
						Direction dir=dirArr.front();
						dirArr.pop();
						int j=i;
						j+=dir;
						if(boardArr[j].none())
						{
							temp.setSrc(i);
							temp.setDest(j);
							moves.push(temp);
						}
					}
					//Capture moves
					dirArr.push(Direction::UR);
					dirArr.push(Direction::UL);
					dirArr.push(Direction::RF);
					dirArr.push(Direction::LF);
					dirArr.push(Direction::UF);
					while(!dirArr.empty())
					{
						Direction dir=dirArr.front();
						dirArr.pop();
						int j=i;
						j+=dir;
						if(!boardArr[j].none()
						&&!boardArr[j].all()
						&&(boardArr[j][SIZE-1]
						!=boardArr[i][SIZE-1]))
						{
							temp.setSrc(i);
							temp.setDest(j);
							moves.push(temp);	
						}
					}
				}
					//Black Pawn
				if(currentPiece==Piece::BP)
				{
					//Non-capture moves
					dirArr.push(Direction::D);
					dirArr.push(Direction::B);
					while(!dirArr.empty())
					{
						Direction dir=dirArr.front();
						dirArr.pop();
						int j=i;
						j+=dir;
						if(boardArr[j].none())
						{
							temp.setSrc(i);
							temp.setDest(j);
							moves.push(temp);
						}
					}
					//Capture moves
					dirArr.push(Direction::DR);
					dirArr.push(Direction::DL);
					dirArr.push(Direction::RB);
					dirArr.push(Direction::LB);
					dirArr.push(Direction::DB);
					while(!dirArr.empty())
					{
						Direction dir=dirArr.front();
						dirArr.pop();
						int j=i;
						j+=dir;
						if(!boardArr[j].none()
						&&!boardArr[j].all()
						&&(boardArr[j][SIZE-1]
						!=boardArr[i][SIZE-1]))
						{
							temp.setSrc(i);
							temp.setDest(j);
							moves.push(temp);	
						}
					}
				}
				//Kings
				if(currentPiece==Piece::WK
				||currentPiece==Piece::BK)
				{
					dirArr.push(Direction::D);
					dirArr.push(Direction::U);
					dirArr.push(Direction::L);
					dirArr.push(Direction::R);
					dirArr.push(Direction::B);
					dirArr.push(Direction::F);
					dirArr.push(Direction::DL);
					dirArr.push(Direction::DR);
					dirArr.push(Direction::DF);
					dirArr.push(Direction::DB);
					dirArr.push(Direction::UL);
					dirArr.push(Direction::UR);
					dirArr.push(Direction::UF);
					dirArr.push(Direction::UB);
					dirArr.push(Direction::LF);
					dirArr.push(Direction::LB);
					dirArr.push(Direction::RF);
					dirArr.push(Direction::RB);
					while(!dirArr.empty())
					{
						Direction dir=dirArr.front();
						dirArr.pop();
						int j=i;
						j+=dir;
						if(!boardArr[j].all()
						&&(boardArr[j].none()
						||(boardArr[j][SIZE-1]
						!=boardArr[i][SIZE-1])))
						{
							temp.setSrc(i);
							temp.setDest(j);
							moves.push(temp);
						}
					}
				}
			}
		}
	}
	return moves;
}


void Generator::printMoves(std::queue<Move> moves)
{
	Move temp;
	int src,dest;
	while(!moves.empty())
	{
		temp= moves.front();
		src=temp.getSrc();
		dest=temp.getDest();
		std::cout<<"src= "<<src<<" dest= "
		<<dest<<std::endl;
		moves.pop();
	}
}

bool Generator::isCheck(Board b)
{
	std::vector<std::bitset<SIZE>> boardArr = b.getBoard();
	bool turn = b.getTurn();
	bool isCheck = false;
	std::queue<Move> moves = pLegal(b);
	while(true)
	{
		Move currentMove= moves.front();
		moves.pop();
		Piece targetPiece = bitsetToPiece(boardArr[currentMove.getDest()]);
		if(targetPiece ==Piece::WK && !turn)
		{	
			isCheck=true;
		}else if(targetPiece==Piece::BK && turn)
		{
			isCheck=true;
		}
		if(moves.empty())
		{
			break;
		}
	}
	return isCheck;
}
bool Generator::isCheckMate(Board b)
{
	bool isCheckMate = false;
	if(legal(b).empty())
	{
		isCheckMate=true;
	}
	return isCheckMate;
}

std::queue<Move> Generator::legal(Board b)
{
	std::queue<Move> finalList;
	std::queue<Move> moves = pLegal(b);
	while(true)
	{
		Move currentMove= moves.front();
		moves.pop();
		bool flag = isCheck(afterMove(b,currentMove));
		if(!flag)
		{
			finalList.push(currentMove);
		}
		if(moves.empty())
		{
			break;
		}
	}
	return finalList;
}
std::queue<Move> Generator::legalToRootFive(Board b)
{
	std::queue<Move> finalList;
	std::queue<Move> moves = legal(b);
	while(true)
	{
		Move currentMove= moves.front();
		moves.pop();
		currentMove.setSrc(ninesToFives(currentMove.getSrc()));
		currentMove.setDest(ninesToFives(currentMove.getDest()));
		finalList.push(currentMove);
		if(moves.empty())
		{
			break;
		}
	}
	return finalList;
}

Board Generator::afterMove(Board b, Move m)
{
	b.move(m);
	return b;
}
