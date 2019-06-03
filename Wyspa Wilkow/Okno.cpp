#include <SFML/Graphics.hpp>
#include "TablicaZwierzat.h"
#include "Gui.h"
#include "Drzewka.h"

#define _WIN32_WINNT 0x500
#include <iostream>
#include <windows.h>
using namespace sf;


int main()
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	Event evnt;
	int rozmiar = 11;
	bool start = false;
	int fps = 2;

	Drzewka drzewka(rozmiar);
	RenderWindow window(VideoMode(1024, 720), "Wyspa Wilków!", Style::Titlebar);
	TablicaZwierzat tablica(rozmiar, drzewka, fps, start);
	Gui gui(tablica, window, start, evnt, rozmiar, drzewka, fps); //Graphic user inteface

	window.setVerticalSyncEnabled(true);

	while (window.isOpen())
	{
		
		while (window.pollEvent(evnt))
		{
			if (evnt.type == Event::Closed)  
				window.close();
		}

		gui.Rysuj();
		gui.Myszka();
		gui.RysujZwierzeta();

		if (start) start = tablica.Dzia³anie();
		
		window.display();
		window.clear();

	}

	return 0;
}