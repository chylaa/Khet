/**@file */
#pragma once
#include "Figura.h"


/**Klasa reprezentujaca graczy.
*/
class Gracz
{
public:
	char Kolor;/**<znak okreslajacy kolor gracza*/
	std::vector <Figura*> Tab_Fig; /*<kontener przechowujacy wskazniki na figury gracza*/
	bool Aktywny; /*<true, jesli gracz jest aktywny*/

	Gracz& operator = (const Gracz& g)
	{
		this->Kolor = g.Kolor;
		this->Aktywny = g.Aktywny;
		this->Tab_Fig = g.Tab_Fig;

		return *this;
	}


	/**Metoda usuwa figury gracza.
	*/
	void UsunFig()
	{
		if (this->Tab_Fig.empty()) return;

		this->Tab_Fig.erase(this->Tab_Fig.begin() + this->Tab_Fig.size() - 1);
		this->Tab_Fig.~vector();
	}
	

};