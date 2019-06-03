#include "TablicaZwierzat.h"


TablicaZwierzat::TablicaZwierzat(int & r, Drzewka &drz, int &m_fps, bool &s)
{
	start = &s;
	fps = &m_fps;
	rozmiar = &r;
	drzewka = &drz;
}

TablicaZwierzat::~TablicaZwierzat()
{
	ListaZwierzat.clear();
}



list<Zwierze*> &TablicaZwierzat::Lista()
{
	return ListaZwierzat;
}

void TablicaZwierzat::Dodaj(Zwierze& zwierze)
{
	ListaZwierzat.push_front(&zwierze);
}

void TablicaZwierzat::Dodaj(Zwierze & zwierze, int pos_x, int pos_y)
{
	zwierze.Pozycja(pos_x, pos_y);
	ListaZwierzat.push_front(&zwierze);
}

void TablicaZwierzat::DodajWilka(int pos_x, int pos_y)
{
	Wilk *w = new Wilk;
	w->pos_x = pos_x;
	w->pos_y = pos_y;
	Dodaj(*w);
}

void TablicaZwierzat::DodajWilczyce(int pos_x, int pos_y)
{
	Wilczyca *w = new Wilczyca;
	w->pos_x = pos_x;
	w->pos_y = pos_y;
	Dodaj(*w);
}

void TablicaZwierzat::DodajKrolika(int pos_x, int pos_y)
{
	Krolik *k = new Krolik;
	k->pos_x = pos_x;
	k->pos_y = pos_y;
	Dodaj(*k);
}

void TablicaZwierzat::Rozmnoz(Zwierze* zwierze)
{
	//if (zwierze->IsKrolik())return;
	Zwierze *zw;
	zw = zwierze->Klonuj();
	sf::Vector2i pos = zw->Pozycja();
	this->Dodaj(*zw, pos.x, pos.y);
}

void TablicaZwierzat::Usun(Zwierze & zwierze)
{

	list <Zwierze*>::iterator iter;
	for (iter = ListaZwierzat.begin(); iter != ListaZwierzat.end(); )
	{
		if ((*iter) == &zwierze)
		{
			iter = ListaZwierzat.erase(iter);
			return;
		}
		else ++iter;
	}
}

void TablicaZwierzat::Usun(int pos_x, int pos_y)
{
	Zwierze &zw = Szukaj(pos_x, pos_y);
	if (&zw)
	{
		Usun(zw); //jesli istnieje to usun 
	}
}

Vector3i TablicaZwierzat::IloscZwierzat() //x.kroliki, y.wilki, z.wilczyce
{
	int kroliki = 0,
		wilki = 0,
		wilczyce = 0;

	for (list<Zwierze*>::iterator i = ListaZwierzat.begin(); i != ListaZwierzat.end(); i++)
	{
		if ((*i)->IsKrolik()) kroliki++;
		if ((*i)->IsWilk()) wilki++;
		if ((*i)->IsWilczyca()) wilczyce++;
	}

	return Vector3i(kroliki, wilki, wilczyce);
}

bool TablicaZwierzat::Czas()
{
	float czas_oczekiwania = 1.0f / *fps;
	elapsed = clock.getElapsedTime();
	if (elapsed.asSeconds() > czas_oczekiwania) {
		clock.restart();
		return false;
	}
	return true;
}




Zwierze& TablicaZwierzat::Szukaj(int pos_x, int pos_y)
{

	list <Zwierze*>::iterator iter;
	for (iter = ListaZwierzat.begin(); iter != ListaZwierzat.end(); iter++)
	{
		if ((*iter)->pos_x == pos_x && (*iter)->pos_y == pos_y)
		{
			Zwierze *z = (*iter);
			return *z;
		}
	}
}

std::list<Zwierze*> TablicaZwierzat::Szukaj(Zwierze * zwierze) //zwraca zwierzêta o tej samej pozycji , w pierwszej kolejnoœci s¹ wilczyce
{
	std::list<Zwierze*> l_szukaj;
	int i = 0;
	list <Zwierze*>::iterator iter;
	for (iter = ListaZwierzat.begin(); iter != ListaZwierzat.end(); iter++)
	{

		if ((*iter)->pos_x == zwierze->pos_x && (*iter)->pos_y == zwierze->pos_y)
		{
			if (*iter != zwierze)
			{
				if((*iter)->IsWilczyca()) l_szukaj.push_front(*iter);
				else l_szukaj.push_back(*iter);
				i++;
			}
		}
	}

	return l_szukaj;

}



list<Zwierze*> TablicaZwierzat::Sasiad(Zwierze * zw) //zwraca liste s¹siadów 
{
	list <Zwierze*> v_sasiad;
	int tablica[3] = { 0, -1, 1 };

	list <Zwierze*>::iterator iter;
	for (iter = ListaZwierzat.begin(); iter != ListaZwierzat.end(); iter++)
	{
		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 3; y++) {
				int zmx = zw->pos_x + tablica[x];
				int zmy = zw->pos_y + tablica[y];
				if ((*iter)->pos_x == zmx && (*iter)->pos_y == zmy)
				{
					if (*iter != zw)
					{
						if ((*iter)->IsKrolik())v_sasiad.push_front(*iter); //Króliki  dodaje na pocz¹tek listy
						else v_sasiad.push_back(*iter); //a reszte na koniec bo nie ma znaczenia  
					}
				}
			}
		}
	}
	return v_sasiad; //powinno zwracac liste s¹siadów 
}

bool TablicaZwierzat::Dzia³anie()
{

	if (!Czas())
	{

		list<Zwierze*>::iterator i;
		for (i = ListaZwierzat.begin(); i != ListaZwierzat.end();)
		{
			//t³uszcz
			if ((*i)->tluszcz <= 0.0f)
			{
				i = ListaZwierzat.erase(i);
				continue;
			}

			/*!!!! Akcja gdy znajd¹ siê na tym samym polu !!!!!*/
			std::list<Zwierze*> s_vec = Szukaj((*i)); //szuka zwierz¹t o takich samych wspó³rzêdnych 
			if (s_vec.size() > 0)
			{
				if ((*i)->IsWilk())
				{
					for (list<Zwierze*>::iterator s_iter = s_vec.begin(); s_iter != s_vec.end(); s_iter++)
					{
						if ((*s_iter)->IsKrolik()) //gdy ofiar¹ jest królik
						{
							(*i)->ruch = false;
							Usun(**s_iter);
							(*i)->Zjadanie();
							break; //wychodzi z pêtli bo nie chce zeby robi³ wiecej niz dwie rzeczy podczas jednego ruchu wa¿niejsze jest jedzenie 
						}
						if ((*s_iter)->IsWilczyca()) /*Gdy wilk dopadnie wilczyce*/
						{
							(*i)->ruch = false; //jak dopadnie to stoi w miejscu
							int r = rand() % 2;
							if ((bool)r) //losowoœæ p³ci 
							{
								DodajWilczyce(rand() % *rozmiar, rand() % *rozmiar);
							}
							else DodajWilka(rand() % *rozmiar, rand() % *rozmiar);
						}

					}
				}
				if ((*i)->IsWilczyca())
				{
					for (list<Zwierze*>::iterator s_iter = s_vec.begin(); s_iter != s_vec.end(); s_iter++)
					{
						if ((*s_iter)->IsWilk()) /*Gdy wilk dopadnie wilczyce*/
						{
							//	(*i)->ruch = false; //jak jest dopadnieta przez wilka to stoi w miejscu
						}
						if ((*s_iter)->IsKrolik()) //gdy ofiar¹ jest królik
						{
							(*i)->ruch = false;
							Usun(**s_iter);
							(*i)->Zjadanie();
						}
					}
				}
				if ((*i)->IsKrolik())
				{
					for (list<Zwierze*>::iterator s_iter = s_vec.begin(); s_iter != s_vec.end(); s_iter++)
					{
						if ((*s_iter)->IsWilk() || (*s_iter)->IsWilk())
						{
							(*i)->ruch = false; //jak dopadnie to stoi w miejscu
						}
					}
				}
			}
			else
			{
				if ((*i)->ruch) //jeœli nic nie robi czyli jest sam na polu 
				{
					list<Zwierze*> sasiad_vec = Sasiad((*i)); //szuka zwierz¹t s¹siaduj¹cych tak ¿e najpierw s¹ króliki 
					for (list<Zwierze*>::iterator s_iter = sasiad_vec.begin(); s_iter != sasiad_vec.end(); s_iter++)
					{
						if ((*i)->IsWilk())
						{
							if ((*s_iter)->IsWilczyca())
							{
								(*i)->Pogon(*s_iter); //zmienia pozycje na t¹ któr¹ aktualnie ma wilczyca 
								(*i)->ruch = false;
								break;
							}
							if ((*s_iter)->IsKrolik())
							{
								(*i)->Pogon(*s_iter);
								(*i)->ruch = false;
								break;
							}
						}

						if ((*i)->IsWilczyca())
						{
							if ((*s_iter)->IsKrolik())
							{
								(*i)->Pogon(*s_iter);
								(*i)->ruch = false;
								break;
							}
						}
					}
				}
			}


			if (!((*i)->IsKrolik()))// jesli nie jest królikiem
			{
				(*i)->Glod();
			}
			else //jesli jest 
			{
				int szanse = 20; //% szans na rozmnozenie
				Zwierze *z = (*i);
				if (rand() % 101 < szanse)
				{
					DodajKrolika(rand() % *rozmiar, rand() % *rozmiar);
				}
			}
			++i;

		}

		for (list<Zwierze*>::iterator i = ListaZwierzat.begin(); i != ListaZwierzat.end(); i++)
		{
			if ((*i)->ruch == true)(*i)->Ruch(*rozmiar, drzewka->Lista()); //jezeli ruch = false to nie rusza sie 
			(*i)->ruch = true;
		}
	}

	Vector3i ilosc = IloscZwierzat();
	if (ilosc.x <1 || ilosc.x>10000 || ilosc.y < 1 || ilosc.y>10000 || ilosc.z < 1 || ilosc.x>10000)
	{
		return false;
	}
	return true;
}

void TablicaZwierzat::Update()
{
	list<Zwierze*>::iterator i;
	for (i = ListaZwierzat.begin(); i != ListaZwierzat.end();)
	{
		if ((*i)->pos_x >= *rozmiar || (*i)->pos_x < 0 || (*i)->pos_y >= *rozmiar || (*i)->pos_y < 0)
		{
			i = ListaZwierzat.erase(i);
		}
		else ++i;
	}


}

void TablicaZwierzat::Czyszczenie()
{

	ListaZwierzat.erase(ListaZwierzat.begin(), ListaZwierzat.end());
}


