/**@file */
#pragma once
#include <iostream>
#include <thread> //for sleep function
#include <chrono>
#include "Gracz.h"
#include "Laser.h"

/**Funkcja ustawia punkt odniesienia dla Sprajta w jego centrum.
@param image ustawiany Sprajt
*/
void SetOrginToCenter(sf::Sprite& image);

/**Klasa zawierajaca atrybuty i metody zarzadzajace logika rozgrywki.
*/
class Gra
{
public:
	sf::Event event; /**<typ specjalny SFML - kolejka zdarzen*/
	Plansza szachownica; /**<obiekt reprezentujacy plansze do gry*/
	Gracz Gb; /**<gracz bialy*/
	Gracz Gc; /**<gracz czerwony*/
	Gracz aktywny; /**<gracz aktywny*/
	bool KoniecTury=0; /**<atrybut informujacy czy tura zostala zakonczona i nalezy zmienic aktywnego gracza*/ 
	bool isMove=0; /**<atrybut informujacy czy aktualnie jest poruszana jakas figura*/
	float dx; /**<zmienna pomocnicza, roznica miedzy miejscem "zlapania" figury a jej centrum*/ 
	float dy; /**<zmienna pomocnicza, roznica miedzy miejscem "zlapania" figury a jej centrum*/ 
	float PreX; /**<poprzednia pozycja figury w oknie w osi OX*/
	float PreY; /**<poprzednia pozycja figury w oknie w osi OY */
	int Ruszana; /**<indeks poruszanego Sprajta w kontenerze ze sprajtami figur*/
	
	/**Metoda obsluguje przeciaganie i upuszczanie figur na planszy.
	@param aktywny obiekt reprezentujacy aktywnego gracza
	@param Gc obiekt reprezentujacy gracza czerwonego
	@param Gb obiekt reprezentujacy gracza bialego
	@param pos para wspolrzednych okreslajaca pozycje kursora w oknie
	*/
	void PrzeciaganieUpuszczanie(Gracz aktywny, Gracz Gc, Gracz Gb, sf::Vector2i pos);

	/**Metoda obslugujaca zamiane miejscami Skarabeusza z inna figura.
	@param Gc obiekt reprezentujacy gracza czerwonego
	@param Gb obiekt reprezentujacy gracza bialego
	@param NewWsp para liczb okreslajaca nowe wspolrzedne Skarabeusza 
	@param OldWsp para liczb okreslajaca stare wspolrzedne Skarabeusza
	*/
	void ZamienSkarabeusza(Gracz Gc, Gracz Gb,sf::Vector2f NewWsp, sf::Vector2f OldWsp);

	/**Metoda obsluguje obracanie figur.
	@param aktywny obiekt reprezentujacy aktywnego gracza
	@param Gc obiekt reprezentujacy gracza czerwonego
	@param Gb obiekt reprezentujacy gracza bialego
	@param pos para wspolrzednych okreslajaca pozycje kursora w oknie
	@return Metoda zwraca true jesli obrot zostal wykonany 
	*/
	bool Obracanie(Gracz active, int rotation, sf::Vector2i pos); //zwraca 1 jako koniec tury

	/**Metoda okreslna nowego aktywnego gracza po zakonczenu tury.
	@param Gb obiekt reprezentujacy gracza bialego
	@param Gc obiekt reprezentujacy gracza czerwonego
	@param active obiekt reprezentujacy aktywnego gracza
	@return Metoda zwraca gracza czerwonego lub bialego, w zaleznosci ktory z nich jest nowym aktywnym
	*/
	Gracz ZamienGracza(Gracz& Gb, Gracz& Gc, Gracz active);

	/**Metoda sprawdza czy Faraon ktoregos z graczy zostal trafiony
	@return Metoda zwraca 'c' jesli zbity czerwony lub 'b' jesli zbity bialy
	*/
	char SprawdzFaraona(); 

	/**Metoda zeruje kluczowe atrybuty gry
	*/
	void Zeruj()
	{
		KoniecTury = 0;
		isMove = false;
		dx = 0;
		dy = 0;
		Ruszana = 0;
		PreX = 0;
		PreY = 0;
	}

};






