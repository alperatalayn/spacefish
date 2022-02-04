#include <iostream>
#include <string>
#include "board.h"
#include "utils.h"
#include "generator.h"

int main()
{
	Board Board1;
	Board1.initialize();
	Generator g;
	char command;
	int src;
	int dest;
	int index;
	int level,file,rank;
	while(command!='q')
	{
		std::cin>>command;
		switch(command)
		{
			case 'p':
				Board1.printBoard();
				break;
			case 'm':
				std::cout<<"enter move source and destination as integers"<<std::endl;
				std::cin>>src>>dest;
				Board1.move(src,dest);
				break;
			case 'f':
				std::cout<<Board1.createFEN()<<std::endl;
				break;
			case 'r':
				g.printMoves(g.pLegal(Board1.getBoard(),Color::WHITE));
				break;
			case 'g':
				std::cout<<"enter index as integer"<<std::endl;
				std::cin>>index;
				std::cout<<Board1.getPieceByIndex(index);
				break;
			case 'i':
				std::cout<<"enter coordinates as integers"<<std::endl;
				std::cin>>level>>rank>>file;
				std::cout<<squareToIndex(
				(Level)level,
				(File)file,
				(Rank)rank);
				break;
			case 'c':
				std::cout<<g.isCheck(Board1.getBoard(),true);
				break;
			case 'l':
				g.printMoves(g.legal(Board1.getBoard(),Color::BLACK));
				break;
		}
	}
	std::cout<<"program terminated by User. Have a nice day!"<<std::endl;
	return 0;
}
