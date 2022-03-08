/**@file */
#pragma once
#include "Menu.h"

/**Klasa reprezentujaca interfejs i to co widza gracze.
*/
class Interfejs 
{
public:
	Menu menu; /**<menu gry*/
	Gra gra; /**<klasa zawierajaca atrybuty i metody zarzadzajace logika rozgrywki.*/
	//sf::Sprite board; /**<Sprajt z grafika planszy*/
	Laser laser; /**<klasa odpowiedzialna za obsluge wiazki wystrzeliwanej przez Sfinksa.*/

	/**Metoda, w ktorej znajduje sie glowna petla gry, wczytywane sa dzialania graczy i wyswietlane grafiki.
	@param Gb obiekt reprezentujacy gracza bialego
	@param Gc obiekt reprezentujacy gracza czerwonego
	@return Metoda zwraca '1' jesli zbito Faraona i rozgryka zostala zakonczona. 
	*/
	int Rozgrywka(Gracz& Gb, Gracz& Gc);

	/**Metoda rysujaca w oknie figury oraz plansze.
	@param Gb obiekt reprezentujacy gracza bialego
	@param Gc obiekt reprezentujacy gracza czerwonego
	@param board 
	*/
	void Rysuj(Gracz Gb, Gracz Gc, sf::Sprite board);

	/**Metoda rysujaca w oknie wiazke lasera.
	*/
	void RysujLaser();

	/**Metoda wypisuje w oknie podany ciag znakow.
	@param s ciag znakow
	*/
	void Info(std::string s);

	/**Metoda wywoluje metode Info() z odpowiednim ciagiem znakow w przypadku zakonczenia gry.
	@param c znak okreslajacy kolor przegranego gracza
	@see Info()
	@see SprawdzFaraona()
	@return Metoda zwraca true jesli odczytano znak 'c' lub 'b' (oznaczajacy zbicie Faraona). 
	*/
	bool InfoKoniec(char c);

};