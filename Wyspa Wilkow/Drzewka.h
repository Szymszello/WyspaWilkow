#pragma once
#include <list>
#include "SFML\Graphics.hpp"
#include "Zwierze.h"


using namespace std;
using namespace sf;

class Drzewka
{
public:
	Drzewka(int &rozm);
	~Drzewka();

	void Dodaj(int x, int y);
	void Usun(int x, int y);
	void Update();
	void Czyszczenie();
	list<Vector2i> Lista();
private:
	int *rozmiar;
	list<Vector2i> drzewka;
};

