/**@file */
#pragma once
#include "Gra.h"
#include<fstream>

/**Klasa reprezentujaca menu gry i zawierajaca metody obslugujace wybor graczy.
*/
class Menu
{
public:
	int MenuWybor=-1;/**<atrybut definiuje ktora z opcji zostala wybrana  0 -wczytaj gre 1-nowa gra 2-zapisz gre 3-zamknij 4-wroc do gry */

	/**Metoda rysujaca w oknie widok menu oraz wczytujaca dzialania graczy.
	@return Metoda zwraca identyczna wartosc jaka zostaje przypisana atrybutowi MenuWybor.
	*/
	int MenuDisplay();

	/**Metoda wywolujaca odpowiednia funkcje menu w zaleznosci od wyboru gracza.
	@param gra klasa zawierajaca atrybuty i metody zarzadzajace logika rozgrywki
	@return Metoda zwraca '1' jesli zostala wybrana ktoras z dostepnych opcji, w przeciwnym razie '0'.
	*/
	int ObslugaWyboru(Gra& gra);

	/**Metoda tworzaca pelen zestaw nowych figur dla graczy wraz z ich poczatkowymi parmetrami.
	@param gra klasa zawierajaca atrybuty i metody zarzadzajace logika rozgrywki
	*/
	void NoweFig(Gra& gra);
	/**Metoda tworzaca zestaw figur z parametrami wczytanymi z pliku save.txt oraz ustawiajaca aktywnego gracza.
	@param gra klasa zawierajaca atrybuty i metody zarzadzajace logika rozgrywki
	*/
	void WczytajFig(Gra& gra);

	/**Metoda zapisujaca do pliku save.txt parametry figur oraz informacje o aktywnym graczu
	@param gra klasa zawierajaca atrybuty i metody zarzadzajace logika rozgrywki
	*/
	void ZapiszGre(Gra& gra);

	/**Metoda ustawiajaca tekstury z pliku ./Obrazy/ figurom graczy.
	@param Gb obiekt reprezentujacy gracza bialego
	@param Gc obiekt reprezentujacy gracza czerwonego
	*/
	void SetTekstur(Gracz& Gc, Gracz& Gb);
};