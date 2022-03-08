/**@file */
#pragma once
#include "Figura.h"
#include "Gra.h"
//#define RozmiarOkna_y  960

/**Klasa odpowiedzialna za obsluge wiazki wystrzeliwanej przez Sfinksa.
*/
class Laser
{
public:
	sf::Vector2i Pos; /**<para zmiennych liczbowych reprezentujaca wspolzedne x oraz y fragmentu lasera na planszy*/
	char way; /**<jeden ze znakow n, s, w lub e okreslajacy nastepny krok lasera*/
	std::vector <sf::Sprite> TabLas; /**<kontener przechowujacy wszystkie sprajty fragmentow lasera do wyswietlenia*/

	/**Metoda dodaje to kontenera TabLas kolejne fragmenty lasera.
	@param PreWay poprzedni kierunek "poruszanania sie" wiazki
	@param CzyZbita jesli laser zbija figure wartosc true
	*/
	void DodajDoTablicy(char PreWay, bool CzyZbita);

	/**Metoda na podstawie rozmieszczenia figur okresla na jakich polach ma zostac wyswietlony laser.
	@param P obiekt reprezentujacy plansze do gry
	@param Gb obiekt reprezentujacy gracza bialego
	@param Gc obiekt reprezentujacy gracza czerwonego
	@param aktywny obiekt reprezentujacy aktywnego gracza
	*/
	void ObliczTrajektorie(Plansza P, Gracz& Gb, Gracz& Gc, Gracz& aktywny);

};

