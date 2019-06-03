#include "Wilk.h"



Wilk::Wilk()
{
}


Wilk::~Wilk()
{
}


Zwierze * Wilk::Klonuj()
{
	Wilk *nowywilk = new Wilk;
	nowywilk->pos_x = this->pos_x;
	nowywilk->pos_y = this->pos_y;
	nowywilk->tluszcz = this->tluszcz;
	return nowywilk;
}
