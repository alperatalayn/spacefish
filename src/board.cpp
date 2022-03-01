#include <iostream>
#include <bitset>
#include <cctype>
#include <vector>
#include "board.h"
#include "move.h"
#include "utils.h"

std::vector<std::bitset<SIZE>> Board::getBoard()
{
	return boardArr;
}
bool Board::getTurn()
{
	return turn;
}
void Board::initialize()
{
	parseFEN(START_POS);
	turn = Color::WHITE;
}

Board::Board()
{
	std::bitset<SIZE> temp;
	temp.set();
	for(int i=0;i<729;i++)
	{
		boardArr.push_back(temp);
	}
}

Piece Board::getPieceByIndex(int index)
{
	return bitsetToPiece(boardArr[index]);
}

void Board::parseFEN(std::string FEN)
{
	int counter = 0;
	int index;
	for(int i=0; i<FEN.length(); ++i)
	{
		const char ch = FEN[i];
		if(isdigit(ch))
		{
			for(int j=0; j<ch-'0'; j++)
			{
				index=squareToIndex(
				(Level)(counter/25),
				(File)(counter%5),
				(Rank)((counter%25)/5));
				setSquare(index,Piece::NONE);
				counter++;
			}
		}
		
		else if(isalpha(ch))
		{
			
			index=squareToIndex(
			(Level)(counter/25),
			(File)(counter%5),
			(Rank)((counter%25)/5));
			switch(ch)
			{
				case 'p':
					setSquare(index,Piece::BP);
					break;
				case 'n':
					setSquare(index,Piece::BN);
					break;
				case 'b':
					setSquare(index,Piece::BB);
				    break;
				case 'r':
					setSquare(index,Piece::BR);
					break;
				case 'u':
					setSquare(index,Piece::BU);
					break;
				case 'q':
					setSquare(index,Piece::BQ);
				 	break;
				case 'k':
					setSquare(index,Piece::BK);
					break;
				case 'P':
					setSquare(index,Piece::WP);
					break;
				case 'N':
					setSquare(index,Piece::WN);
					break;
				case 'B':
					setSquare(index,Piece::WB);
					break;
				case 'R':
					setSquare(index,Piece::WR);
					break;
				case 'U':
					setSquare(index,Piece::WU);
					break;
				case 'Q':
					setSquare(index,Piece::WQ);
					break;
				case 'K':
					setSquare(index,Piece::WK);
					break;
					
			}
			counter++;
		}
		else if(ch == '-')
		{
			if(FEN[i+1] == 'w')
			{
				turn=Color::WHITE;
				return;
			}
			turn=Color::BLACK;
			return;
		}
	}
}
std::string Board::createFEN()
{
	std::string FENString="";
	int spaceCounter=0;
	for(int i=0;i<729;i++)
	{	
		Piece currentPiece=bitsetToPiece(boardArr[i]);
		if(currentPiece!=Piece::NONE&&spaceCounter!=0)
		{
			FENString+=std::to_string(spaceCounter);
			spaceCounter=0;
		}
		if(i%9==2 &&currentPiece!=Piece::FULL
		&&!FENString.empty())
		{
			FENString+='/';
		}
		switch(currentPiece)
		{
			case Piece::NONE:
				spaceCounter+=1;
				break;
			case Piece::WP:
				FENString+='P';
				break;
			case Piece::WB:
				FENString+='B';
				break;
			case Piece::WR:
				FENString+='R';
				break;
			case Piece::WU:
				FENString+='U';
				break;
			case Piece::WN:
				FENString+='N';
				break;
			case Piece::WQ:
				FENString+='Q';
				break;
			case Piece::WK:
				FENString+='K';
				break;
			case Piece::BP:
				FENString+='p';
				break;
			case Piece::BN:
				FENString+='n';
				break;
			case Piece::BB:
				FENString+='b';
				break;
			case Piece::BU:
				FENString+='u';
				break;
			case Piece::BR:
				FENString+='r';
				break;
			case Piece::BQ:
				FENString+='q';
				break;
			case Piece::BK:
				FENString+='k';
				break;
			case Piece::FULL:
				break;
		}
	}
	if(turn == Color::WHITE)
	{
		FENString += " -w";
	}
	else
	{
		FENString += " -b";
	}
	return FENString;
}


void Board::setSquare(int index, Piece piece)
{
    boardArr[index]= piece;
}

void Board::printBoard()
{
	for(int i=0;i<729;i++)
	{	
		if(i%9==0)std::cout<<std::endl;
		if(i%81==0)std::cout<<std::endl;
		Piece currentPiece=bitsetToPiece(boardArr[i]);
		switch(currentPiece)
		{
			case Piece::NONE:
				std::cout<<'-';
				break;
			case Piece::WP:
				std::cout<<'P';
				break;
			case Piece::WB:
				std::cout<<'B';
				break;
			case Piece::WR:
				std::cout<<'R';
				break;
			case Piece::WU:
				std::cout<<'U';
				break;
			case Piece::WN:
				std::cout<<'N';
				break;
			case Piece::WQ:
				std::cout<<'Q';
				break;
			case Piece::WK:
				std::cout<<'K';
				break;
			case Piece::BP:
				std::cout<<'p';
				break;
			case Piece::BN:
				std::cout<<'n';
				break;
			case Piece::BB:
				std::cout<<'b';
				break;
			case Piece::BU:
				std::cout<<'u';
				break;
			case Piece::BR:
				std::cout<<'r';
				break;
			case Piece::BQ:
				std::cout<<'q';
				break;
			case Piece::BK:
				std::cout<<'k';
				break;
			case Piece::FULL:
				std::cout<<'*';
		}	
	}
	std::cout<<std::endl<<"turn: "<<turn;
}
void Board::move(Move m)
{	
	int source= m.getSrc();
	int destination=m.getDest();
	if(!boardArr[source].none())
	{
		boardArr[destination]=boardArr[source];
		boardArr[source].reset();
		turn = !turn;
	}
	else
	{
		std::cout<<"no piece at given square"<<std::endl;
	}
}

