#include "Zwierze.h" 





Zwierze::Zwierze() :pos_x(rand() % 20), pos_y(rand() % 20), tluszcz(1.0) 
{

}

Zwierze::~Zwierze()
{
}

void Zwierze::Pozycja(int x, int y)
{
	pos_x = x;
	pos_y = y;
}

void Zwierze::Ruch(int granica, list<Vector2i> &drz)
{

	//if (this->IsKrolik())return;
	int x = pos_x, y = pos_y;

	int inc = (rand() % 3);
	inc -= 1;
	x += inc; //nowa pozycja x
	inc = (rand() % 3);
	inc -= 1;
	y += inc; //nowa pozycja y

	if (x >= granica || x < 0 || y >= granica || y < 0) //jeœli mia³o by wyjœæ poza plansze 
	{
		this->Ruch(granica, drz);
		return;
	}
	else
		for (list<Vector2i>::iterator i = drz.begin(); i != drz.end(); i++) //jeœli mia³o by wejœæ w krzaczek 
		{
			if (x == (*i).x&& y == (*i).y)
			{
				this->Ruch(granica, drz);
				return;
			}
		}

	pos_x = x;
	pos_y = y;
}

void Zwierze::Pogon(Zwierze * zw)
{
	pos_x = zw->pos_x;
	pos_y = zw->pos_y;

}

void Zwierze::Zjadanie()
{
	tluszcz += 1.0f;
}

void Zwierze::Glod()
{
	tluszcz -= 0.1f;
}



sf::Vector2i Zwierze::Pozycja()
{
	return sf::Vector2i(pos_x, pos_y);
}

bool Zwierze::operator==(Zwierze * zw)
{
	if (Pozycja() == zw->Pozycja() && IsKrolik() == zw->IsKrolik() && IsWilczyca() == zw->IsWilczyca() && IsWilk() == zw->IsWilk() && tluszcz == zw->tluszcz) return true;
	else return false;
}







