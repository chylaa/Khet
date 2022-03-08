// Khet.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "Figura.h"
#include "Interfejs.h"

int main()
{
	int MenuWybor=1; //( 1-nowa gra 0-wczytaj gre 2-zapisz 3-zamkniecie okna 4-powrot do gry
	Interfejs* gierka = new Interfejs;
	bool pierw = 1; //pierwsza gra po odpaleniu programu lub zbiciu faraona

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));//sleep
		MenuWybor = gierka->menu.MenuDisplay();

		std::cout << "\nMenu wybor: " << MenuWybor << "\nPierw: "<<pierw<< std::endl;
		if (MenuWybor == 3) break;
		if (pierw && (MenuWybor == 4 || MenuWybor==2)) continue;
		if(MenuWybor==2) gierka->menu.ObslugaWyboru(gierka->gra);

		if (MenuWybor != 4 && MenuWybor != 2) 
		{
			if (!pierw) 
			{			
				gierka->gra.Gb.UsunFig();
				gierka->gra.Gc.UsunFig();
				delete gierka;
				Interfejs* gierka = new Interfejs;
			}
			gierka->menu.MenuWybor = MenuWybor;
			if(gierka->menu.ObslugaWyboru(gierka->gra)==0) break; 
		}
		//===========Glowna petla==============================
		pierw=gierka->Rozgrywka(gierka->gra.Gb, gierka->gra.Gc);
		if (gierka->menu.MenuWybor == 3) break;
	}	
	delete gierka;
	std::cout << "\nTHANK YOU";
	return 1;
}

