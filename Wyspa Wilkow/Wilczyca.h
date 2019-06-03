#pragma once
#include "Zwierze.h"
class Wilczyca :
	public Zwierze
{
public:
	Wilczyca();
	~Wilczyca();
	 
	Zwierze* Klonuj();
	bool IsWilk() { return false; };
	bool IsWilczyca() { return true; };
	bool IsKrolik() { return false; };
};

