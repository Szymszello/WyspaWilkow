#include "Krolik.h"

using namespace sf;

Krolik::Krolik()
{
	
}


Krolik::~Krolik()
{
}


Zwierze * Krolik::Klonuj()
{
	Krolik *nowykrolik= new Krolik;
	nowykrolik->pos_x = this->pos_x;
	nowykrolik->pos_y = this->pos_y;
	nowykrolik->tluszcz = this->tluszcz;
	return nowykrolik;
}
