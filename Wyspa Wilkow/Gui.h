#pragma once
#include "SFML\Graphics.hpp"
#include "TablicaZwierzat.h"
#include "Drzewka.h"
using namespace std;
using namespace sf;
class Gui
{
public:
	Gui(TablicaZwierzat &tablica, sf::RenderWindow &win, bool &s, sf::Event &e, int &rozm, Drzewka &drz, int &m_fps);
	~Gui();


	void Rysuj();
	void RysujZwierzeta();
	void RysujDrzewka();
	void Myszka();
	Texture grafika_krolika;
	Texture grafika_wilka;
	Texture grafika_wilczycy;
	Texture grafika_drzewko;
	Texture grafika_usun;
	RectangleShape kwadrat;

	void RysujOknoPowitalne();
private:
	int wybor; 
	/*
	0 - Dodaj P³ot
	1 - Dodaj Królika
	2 - Dodaj Wilka
	3 - Dodaj Wilczyce
	4 - Usuñ zwierze */

	list<Zwierze*> *ListaZwierzat;
	Drzewka *drzewka;
	int *rozmiar;
	void RysujTekst(const sf::String & string, float x, float y, int rozmiar);
	Event *evnt;
	bool *start;
	TablicaZwierzat *tab;
	RenderWindow *window;
	Vector2i mousepos;
	int *fps;
};

