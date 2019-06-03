#pragma once
#include "Zwierze.h"
class Wilk :
	public Zwierze
{
public:
	Wilk();
	~Wilk();
	 
	Zwierze* Klonuj();
	bool IsWilk() { return true; };
	bool IsWilczyca() { return false; };
	bool IsKrolik() { return false; };
};

