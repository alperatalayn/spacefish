#include <iostream>
#include <string>
#include "board.h"
#include "utils.h"
#include "generator.h"
#include "engine.h"

int main()
{
	Board Board1;
	Board1.initialize();
	Generator g;
	Engine e;
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
				Move m;
				m.setDest(dest);
				m.setSrc(src);
				Board1.move(m);
				break;
			case 'f':
				std::cout<<Board1.createFEN()<<std::endl;
				break;
			case 'r':
				g.printMoves(g.pLegal(Board1));
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
				std::cout<<g.isCheck(Board1);
				break;
			case 'l':
				g.printMoves(g.legal(Board1));
				break;
			
			case 'e':
				int safetyFirst=1000;
				while(safetyFirst>1)
				{
					Move best = e.search(Board1,3,-5000,5000,&g);
					Board1.move(best);
					std::cout<<"src: "<<best.getSrc()
					<<" dest: "<<best.getDest()
					<<" eval: "<<best.eval<<std::endl;
					safetyFirst-=1;
				}
				break;
		}
	}
	std::cout<<"program terminated by User. Have a nice day!"<<std::endl;
	return 0;
}
