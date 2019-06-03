#pragma once
#include "Zwierze.h"
#include "Krolik.h"
#include "Wilczyca.h"
#include "Wilk.h"
#include "Drzewka.h"
#include "SFML\Graphics.hpp"

using namespace std;
using namespace sf;

class TablicaZwierzat
{
public:
	TablicaZwierzat(int &r, Drzewka &drz, int &m_fps, bool &s);
	~TablicaZwierzat();
private:
	Drzewka *drzewka;
	list <Zwierze*> ListaZwierzat;
	int *rozmiar;
	bool *start;
public: 
	list <Zwierze*> &Lista();
	void Dodaj(Zwierze& zwierze);
	void Dodaj(Zwierze& zwierze, int pos_x, int pos_y);
	void DodajWilka(int pos_x, int pos_y);
	void DodajWilczyce(int pos_x, int pos_y);
	void DodajKrolika(int pos_x, int pos_y);

	void Rozmnoz(Zwierze* zwierze);
	void Usun(Zwierze& zwierze);
	void Usun(int pos_x, int pos_y); //to b�dzie kasowa� posta� na polu jak kliknie myszk� czy co�;
	Vector3i IloscZwierzat();
	Zwierze& Szukaj(int pos_x, int pos_y);
	list<Zwierze*> Szukaj(Zwierze* zwierze);
	list<Zwierze*> Sasiad(Zwierze* zw);
	bool Dzia�anie(); 
	void Update();
	void Czyszczenie();
	sf::Clock clock;
	sf::Time elapsed;
	bool Czas();
	int *fps;
};

