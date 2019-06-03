#include "Wilczyca.h"



Wilczyca::Wilczyca()
{
}


Wilczyca::~Wilczyca()
{
}



Zwierze * Wilczyca::Klonuj()
{
	Wilczyca *nowawilczyca = new Wilczyca;
	nowawilczyca->pos_x = this->pos_x;
	nowawilczyca->pos_y = this->pos_y;
	nowawilczyca->tluszcz = this->tluszcz;
	return nowawilczyca;
}
