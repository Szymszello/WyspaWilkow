#pragma once
#include "Zwierze.h"
#include "SFML\Graphics.hpp"
class Krolik :
	public Zwierze
{
public:
	Krolik();
	~Krolik();
	 
	Zwierze* Klonuj();
	bool IsWilk() { return false; };
	bool IsWilczyca() { return false; };
	bool IsKrolik() { return true; };
	
};

