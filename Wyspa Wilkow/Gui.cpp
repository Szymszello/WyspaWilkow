#include "Gui.h"



Gui::Gui(TablicaZwierzat &tablica, RenderWindow &win, bool &s, Event &e, int &rozm, Drzewka &drz, int &m_fps) : wybor(1)
{
	fps = &m_fps;
	drzewka = &drz;
	rozmiar = &rozm;
	evnt = &e;
	start = &s;
	tab = &tablica;
	window = &win;
	grafika_wilka.loadFromFile("Texture/wilk.png");
	grafika_wilczycy.loadFromFile("Texture/wilczyca.png");
	grafika_krolika.loadFromFile("Texture/krolik.png");
	grafika_drzewko.loadFromFile("Texture/drzewko.png");
	grafika_usun.loadFromFile("Texture/usun.png");
	ListaZwierzat = &tab->Lista();
}


Gui::~Gui()
{
}

void Gui::Rysuj()
{

	//T³o

	Texture grafika;
	RectangleShape tlo(Vector2f((float)window->getSize().x, (float)window->getSize().y));

	grafika.loadFromFile("Texture/tlo.png");
	tlo.setTexture(&grafika);
	window->draw(tlo);


	//Plansza

	float bok = (float)500 / (float)*rozmiar;
	Vector2f komWymiar(bok, bok);
	kwadrat.setSize(komWymiar);
	kwadrat.setFillColor(Color(133, 93, 50, 100));
	kwadrat.setOutlineThickness(1.0f);
	kwadrat.setOutlineColor(Color::Black);
	float x = 0.0, y = 0.0;
	for (int i = 0; i < *rozmiar; i++) {
		for (int j = 0; j < *rozmiar; j++) {
			x = 150 + i*komWymiar.x;			//po³o¿enie x
			y = 100 + j*komWymiar.y;			//po³o¿enie y 
			kwadrat.setPosition(Vector2f(x, y)); //ustawienie po³o¿enia kwadratu

			window->draw(kwadrat);
		}
	}

	//t³o pod menu 
	sf::RectangleShape menu(Vector2f(250, 500));
	menu.setPosition(750, 100);
	menu.setFillColor(Color(20, 255, 255, 25));
	window->draw(menu);

	//przycisk start/stop 
	sf::RectangleShape startbutton(Vector2f(150.0f, 50.0f));
	startbutton.setPosition(Vector2f(800, 125));

	if (*start)startbutton.setFillColor(Color::Blue);
	else startbutton.setFillColor(Color::Red);

	window->draw(startbutton);
	//tekst start/stop
	if (*start)RysujTekst("STOP", startbutton.getPosition().x + 40, startbutton.getPosition().y + 5, 30);
	else RysujTekst("START", startbutton.getPosition().x + 30, startbutton.getPosition().y + 5, 30);

	

	//pozycja myszy
	RysujTekst(to_string(mousepos.x), 10, 10, 15);
	RysujTekst(to_string(mousepos.y), 10, 20, 15);

	//Jakiœ tekst 

	RysujTekst("Symulacja!", 800, 50, 30);

	sf::RectangleShape button(Vector2f(250, 100));
	button.setPosition(750, 100);
	button.setFillColor(Color(20, 255, 255, 55));
	window->draw(button);


	RysujTekst("Rozmiar planszy: " + to_string(*rozmiar), 800, 210, 15);

	button.setSize(Vector2f(50, 30));
	button.setOutlineThickness(0.7f);
	button.setFillColor(Color(0, 155, 255, 155));

	button.setPosition(820, 240);
	window->draw(button);

	button.setPosition(880, 240);
	window->draw(button);

	RysujTekst("-", 840, 235, 30);
	RysujTekst("+", 900, 235, 30);


	RysujTekst("Ilosc zwierzat: " + to_string(tab->IloscZwierzat().x + tab->IloscZwierzat().y + tab->IloscZwierzat().z), 800, 280, 15);
	RysujTekst(to_string(tab->IloscZwierzat().x), 790, 315, 20);
	RysujTekst(to_string(tab->IloscZwierzat().y), 852, 315, 20);
	RysujTekst(to_string(tab->IloscZwierzat().z), 925, 315, 20);
	RysujTekst("Króliki	Wilki	Wilczyce", 775, 340, 15);


	button.setSize(Vector2f(50, 30));
	button.setOutlineThickness(0.7f);

	button.setPosition(820, 400);
	window->draw(button);

	button.setPosition(880, 400);
	window->draw(button);

	RysujTekst("Predkosc: "+to_string(*fps)+" FPS", 800, 370, 15);

	RysujTekst("-", 840, 395, 30);
	RysujTekst("+", 900, 395, 30);


	button.setSize(Vector2f(110, 30));
	button.setOutlineThickness(0.7f);
	button.setFillColor(Color(255, 0, 40, 100));
	button.setPosition(820, 480);
	window->draw(button);

	RysujTekst("Czyszczenie", 825, 485, 15);

	button.setSize(Vector2f(110, 30));
	button.setOutlineThickness(0.7f);
	button.setFillColor(Color(255, 0, 40, 100));
	button.setPosition(750,650);
	window->draw(button);

	RysujTekst("Zamknij", 760, 655 , 15);

	sf::RectangleShape w_shape(Vector2f(40, 40));
	sf::RectangleShape iw_shape(Vector2f(39, 39));
	w_shape.setFillColor(Color(20, 255, 255, 0));
	w_shape.setOutlineThickness(1.0f);
	w_shape.setOutlineColor(Color::White);
	for (int i = 0; i < 5; i++)
	{
		w_shape.setPosition(775.0f + i * 40, 525.0f);
		iw_shape.setPosition(w_shape.getPosition().x + 1, w_shape.getPosition().y + 1);
		if (wybor == i) w_shape.setOutlineColor(Color::Red);
		else w_shape.setOutlineColor(Color::White);

		switch (i)
		{
		case 0: //rysuje murek
			iw_shape.setTexture(&grafika_drzewko);
			break;
		case 1: //krolika
			iw_shape.setTexture(&grafika_krolika);
			break;
		case 2: //wilka
			iw_shape.setTexture(&grafika_wilka);
			break;
		case 3: //wilczyce
			iw_shape.setTexture(&grafika_wilczycy);
			break;
		case 4: //usuwanie
			iw_shape.setTexture(&grafika_usun);			
			break;
		default:
			break;
		}
		window->draw(iw_shape);
		window->draw(w_shape);
	}

}

void Gui::RysujZwierzeta()
{

	float x_p = 150.0f;
	float y_p = 100.0f; //wspó³rzêdne pocz¹tku planszy		
	float bok_z = kwadrat.getSize().x;

	RectangleShape kwadrat(Vector2f(bok_z, bok_z)); //rozmiary zwierz¹tka
	for (list <Zwierze*>::iterator iter = ListaZwierzat->begin(); iter != ListaZwierzat->end(); iter++)
	{
		if ((*iter)->IsKrolik())
		{
			kwadrat.setTexture(&grafika_krolika);
			kwadrat.setPosition(Vector2f(x_p + (*iter)->pos_x * bok_z, y_p + (*iter)->pos_y * bok_z));
			window->draw(kwadrat);
		}
		if ((*iter)->IsWilk())
		{
			kwadrat.setTexture(&grafika_wilka);
			kwadrat.setPosition(Vector2f(x_p + (*iter)->pos_x * bok_z, y_p + (*iter)->pos_y * bok_z));
			window->draw(kwadrat);
		}
		if ((*iter)->IsWilczyca())
		{
			kwadrat.setTexture(&grafika_wilczycy);
			kwadrat.setPosition(Vector2f(x_p + (*iter)->pos_x * bok_z, y_p + (*iter)->pos_y * bok_z));
			window->draw(kwadrat);
		}

	}
	this->RysujDrzewka();
}

void Gui::RysujDrzewka()
{
	list<Vector2i> ListaDrzewek = drzewka->Lista();
	float x_p = 150.0f;
	float y_p = 100.0f; //wspó³rzêdne pocz¹tku planszy
	RectangleShape drzewko(Vector2f(kwadrat.getSize().x, kwadrat.getSize().y));
	for (list <Vector2i>::iterator iter = ListaDrzewek.begin(); iter != ListaDrzewek.end(); iter++)
	{
		drzewko.setTexture(&grafika_drzewko);
		drzewko.setPosition(Vector2f(x_p + (*iter).x * kwadrat.getSize().x, y_p + (*iter).y * kwadrat.getSize().y));
		window->draw(drzewko);
	}


}

void Gui::Myszka()
{
	while (window->pollEvent(*evnt))
	{
		switch (evnt->type)
		{
		case Event::MouseButtonPressed:
			if (evnt->mouseButton.button == sf::Mouse::Left)
			{
				int x = evnt->mouseButton.x;
				int y = evnt->mouseButton.y;
				if (x > 800 && x < 950 && y > 125 && y < 175) *start = !(*start); //start stop 
				int p_x = 775;
				int k_x = 815;
				for (int i = 0; i < 5; i++)
				{					
					if (x > p_x + i * 40 && x < k_x + i * 40 && y > 525 && y < 565) wybor = i;
				}
			
				if (x > 150 && x < 650 && y > 100 && y < 600) //dodaj zwierzynê 
				{

					float a = ((float)x - 150) / 500 * *rozmiar; //pozycja myszy dzielona przez szerokoœæ planszy w pikselach razy iloœæ pól  
					a = floor(a);

					float b = ((float)y - 100) / 500 * *rozmiar;
					b = floor(b);

					bool jest = false;
					switch (wybor)
					{
					case 0: //dodaj p³ot						
						for (list<Zwierze*>::iterator it = ListaZwierzat->begin(); it != ListaZwierzat->end(); it++)
						{
							if (a == (*it)->pos_x && b == (*it)->pos_y)
							{
								jest = true; //jesli na tej pozycji jest zwierz¹tko to przerwij dodawanie krzaczka 
								break; //wychodzi z pêtli bo ju¿ znalaz³o 
							}
						}
						if (jest) break;
						else drzewka->Dodaj((int)a, (int)b);
						break;
					case 1: //dodaj Królik
						tab->DodajKrolika((int)a, (int)b);
						break;
					case 2: //dodaj Wilk
						tab->DodajWilka((int)a, (int)b);
						break;
					case 3: //dodaj Wilczyca
						tab->DodajWilczyce((int)a, (int)b);
						break;
					case 4: //usun obiekt
						tab->Usun((int)a, (int)b);
						drzewka->Usun((int)a, (int)b);
						break;
					default:
						break;
					}
				}

				if (x > 820 && x < 930 && y > 240 && y < 270) //zwieksz zmniejsz rozmiar 
				{
					if (x > 820 && x < 875)
						*rozmiar -= 1;
					else *rozmiar += 1;
					tab->Update();
					drzewka->Update();
				}
				if (x > 820 && x < 930 && y > 400 && y < 430) //zwieksz zmniejsz predkosc 
				{
					if (x > 820 && x < 875)
					{
						if (*fps < 2) break;
						else *fps -= 1;
					}
					else
					{
						if (*fps > 30) break;
						else *fps += 1;					
					}
				}
				if (x > 820 && x < 920 && y > 480 && y < 510)
				{
					tab->Czyszczenie();
					drzewka->Czyszczenie();
				}
				if (x > 750 && x < 860 && y > 650 && y < 680)
				{
					window->close();
				}
			
			}
			break;
		case Event::MouseMoved:
			mousepos = Vector2i(evnt->mouseMove.x, evnt->mouseMove.y);
			break;
		default:
			break;
		}
	}

}

void Gui::RysujOknoPowitalne()
{

}



void Gui::RysujTekst(const sf::String & string, float x, float y, int rozmiar)
{
	Font font;
	Text tekst;
	font.loadFromFile("ALGER.ttf");

	tekst.setPosition(x, y);
	tekst.setString(string);
	tekst.setFont(font);
	tekst.setCharacterSize(rozmiar);
	window->draw(tekst);
}
