#ifndef UTILS_H
#define UTILS_H
#define SIZE 4
#define START_POS "rnknr/ppppp/5/5/5/ubqub/ppppp/5/5/5/5/5/5/5/5/5/5/5/PPPPP/BUQBU/5/5/5/PPPPP/RNKNR"
//Pieces: 
//None for empty
//first characters: W for White B for black
enum Piece {NONE,WP,WN,WB,WR,WU,WQ,WK,BP
,BN,BB,BR,BU,BQ,BK,FULL};

//Coordinates
enum class File {A,B,C,D,E};
enum class Rank {FIRST,SECOND,THIRD,FOURTH,FIFTH};
enum class Level {A,B,C,D,E};
enum Direction {U=-81,UL=-82,UR=-80,ULF=-91,ULB=-73,
	URF=-89,URB=-71,UF=-90,UB=-72,D=81,DL=80,
	DR=82,DLF=71,DLB=89,DRF=73,DRB=91,
	DF=72,DB=90,L=-1,R=1,LF=-10,RF=-8,LB=8,
	RB=10,B=9,F=-9};
enum NMove {LUU=-163,RUU=-161,FUU=-171,BUU=-153,
	UFF=-99,URR=-79,ULL=-83,UBB=-63,DFF=63,DRR=83,
	DLL=79,DBB=99,LDD=161,RDD=163,FDD=153,BDD=171,
	LFF=-19,LBB=17,BLL=7,BRR=11,RFF=-17,RBB=19,
	FLL=-11,FRR=-7};
enum Color {BLACK,WHITE};
//Conversion between coordinates and indexes
int squareToIndex(Level, File, Rank);
Piece bitsetToPiece(std::bitset<SIZE>);
#endif
