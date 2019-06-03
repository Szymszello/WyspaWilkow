#include "Drzewka.h"


 

Drzewka::Drzewka(int & rozm)
{
	rozmiar = &rozm;
}

Drzewka::~Drzewka()
{
}

void Drzewka::Dodaj(int x, int y)
{
	list<Zwierze*>::iterator it; 
	list<Vector2i>::iterator i;
	for (i = drzewka.begin(); i != drzewka.end(); i++)
	{
		if ((*i).x == x && (*i).y == y) //sprawdza czy jest ju¿ krzaczek na tej pozycji  
		{
			return; //jeœli tak to nie dodaje 
		}
				
	} 

	drzewka.push_back(Vector2i(x, y)); 

}

void Drzewka::Usun(int x, int y)
{
	list<Vector2i>::iterator i;
	for (i = drzewka.begin(); i != drzewka.end();)
	{
		if ((*i).x == x && (*i).y == y) //sprawdza czy jest drzewko na tej pozycji 
		{
			i = drzewka.erase(i);
		}
		else i++;
	}

	 
}

void Drzewka::Update()
{
	list<Vector2i>::iterator i;
	for (i = drzewka.begin(); i != drzewka.end();)
	{
		if ((*i).x >= *rozmiar || (*i).x < 0 || (*i).y >= *rozmiar || (*i).y < 0)
		{
			i = drzewka.erase(i);
		}
		else ++i;
	}
}

void Drzewka::Czyszczenie()
{	
	drzewka.erase(drzewka.begin(),drzewka.end());
}

list<Vector2i> Drzewka::Lista()
{
	return drzewka;
}
