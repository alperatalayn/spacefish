#include "move.h"

void Move::setSrc(int source)
{
	src=source;
}
void Move::setDest(int destination)
{
	dest=destination;
}
int Move::getDest()
{
	return dest;
}
int Move::getSrc()
{
	return src;
}
