#ifndef MOVE_H
#define MOVE_H
class Move
{
	private:
		int src;
		int dest;
	public:
		int eval;
		void setSrc(int);
		void setDest(int);
		int getSrc();
		int getDest();
};
#endif
