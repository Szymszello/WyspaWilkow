#pragma once
#include <SFML\Graphics.hpp>
#include "Drzewka.h"
#include <list>

using namespace sf;
using namespace std;

class Zwierze
{
public:
	Zwierze();
	~Zwierze();
 
	int pos_x, pos_y;
	float tluszcz; 
	bool ruch = true;

	void Pozycja(int x, int y); //ustaw pozycje 
	virtual bool IsWilk() = 0;
	virtual bool IsWilczyca() = 0;
	virtual bool IsKrolik() = 0;
	void Ruch(int granica, list<Vector2i> &drz);
	void Pogon(Zwierze * zw);
	void Zjadanie();
	void Glod();
	sf::Vector2i Pozycja();
	virtual Zwierze* Klonuj() = 0;
	bool operator==(Zwierze * zw);

private:
	
	int rozmiar; 

};

