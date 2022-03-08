/**@file */
#pragma once

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include<algorithm>
#include<typeinfo>
#include <vector>

#define square_size 120 //wielkosc pola planszy
#define MaxIloscFig 13 //maksymalna ilosc figur dla jednego gracza



class Plansza;

/**
Klasa "bazowa" dla wszystkich figur, zawierajaca metody wirtualne odpowiedzialne za ich ruch oraz odbicia lasera.
*/
class Figura
{
	
public:

	std::string Nazwa; /**<nazwa figury (takze fragment sciezki do odpowiedniego pliku z tekstura)*/
	sf::Texture tekstura; /**<tekstura figury*/
	sf::Sprite sprajt; /**<sprajt figury*/
	char Kolor; /**< kolor figury ( 'c' - czerwona 'b' - biala)*/ 
	int x_wsp; /**<pozycja figury na planszy w osi OX [0-9]*/
	int y_wsp; /**<pozycja figury na planszy w osi OY [0-7]*/
	char Kierunek; /**<kierunek w jakim zwrocona jest figura*/

	/**Metoda odpowiada za sprawdzenie czy figura moze wykonac ruch na przekazane wspolzedne.
	@param x numer kolumny docelowej pozycji figury.
	@param y numer wiersza docelowej pozycji figury.
	@param P obiekt reprezentujacy plansze do gry
	@return Metoda zwraca "1" jesli ruch jest mozliwy.
	*/
	virtual bool CzyMozliwyRuch(int x, int y, Plansza P) = 0;

	/**Metoda odpowiada za okreslenie czy figura zostala zbita przez wiazke lasera lub ja odbila (jesli tak w jakim kierunku).
	@param way znak (n/s/w/e) opisujacy kierunek w ktorym porusza sie laser 
	@return Metoda zwraca "1" jesli figura zostala zbita.
	*/
	virtual bool ObslugaLasera(char& way) =0;
	
	/**Metoda odpowiada za okreslenie czy figura moze wykonac obrot.
	@param rotation kierunek obrotu wyrazony w stopniach
	@see ObliczTrajektorie()
	@return Metoda zwraca "1" jesli obrot jest mozliwy.
	*/
	bool CzyMozliwyObrot(int rotation);

	/**Metoda przypisujaca figurze wspolzedne na planszy na podstawie jej wspolzednych w oknie gry.
	@param x pozycja figury w oknie gry w osi OX
	@param y pozycja figury w oknie gry w osi OY
	*/
	void PrzypiszWsp(int x, int y);

	/**Metoda odpowiada za ustaienie figury w podanym kierunku.
	@param rotation kierunek obrotu wyrazony w stopniach
	*/
	void UstawKierunek(int rotation);

	/**Metoda stworzona do wywolania w konstruktorach kazdej z figur w celu uproszczenia zapisu.
	*/
	void konstruktor(std::string nazwa, char kolor, int x, int y, char kierunek) 
	{
		Nazwa = nazwa;
		Kolor = kolor;
		x_wsp=x;
		y_wsp = y;
		Kierunek = kierunek;
		if (kierunek == 's') this->sprajt.setRotation(180);
		if (kierunek == 'w') this->sprajt.setRotation(270);
		if (kierunek == 'e') this->sprajt.setRotation(90);
	}

};

/**Funkcja wyszukuje w tablicy figur ta znajdujaca sie na podanych wspolzednych.
@param x numer kolumny, w ktorej znajduje sie figura.
@param y numer wiersza, w ktorym znajduje sie figura.
@param tab_fig wektor zawierajacy figury.
@return Funkcja zwraca indeks figury w wektorze (-1 gdy jej nie znajdzie).
*/
int ZnajdzFigure(int x, int y, std::vector <Figura*> tab_fig);

/**
Struktura reprezentujaca pojedyncze pole planszy
*/
struct Pole
{
public:
	Figura* fig; /**<wskaznik do ewentualnej figury stojacej na polu (nullptr jesli pole jest puste)*/
	char RodzajPola; /**<rodzaj pola: c-zabronione dla bialego; b-zabronione dla czerwonego; n-normalne*/
};

/**
Klasa obsugujaca reprezentacje planszy gry.
*/
class Plansza
{
public:
	Pole plansza[10][8]; /**< tablica reprezentujaca plansze*/

	/**Metoda wypelnia pola tablicy "plansza" wartosciami neutralnymi.
	*/
	void WypelnijNull();

	/**Metoda odpowiada za wypelnienie planszy wskaznikami na figury graczy.
	@param TGc kontener przechowujacy wskazniki na figury gracza czerwonego
	@param TGc kontener przechowujacy wskazniki na figury gracza bialego
	*/
	void WypelnijPlansze(std::vector <Figura*> &TGc, std::vector <Figura*> &TGb);

	/**Metoda wypisuje widok planszy w konsoli.
	*/
	void WypiszPlansze();

	/**Metoda wypelnia w tablicy "plansza" pola zabronione.
	*/
	void PrzypiszPolaZabronione();

};


/**Klasa reprezentujaca figure typu Piramida.
*/
class Piramida : public Figura
{
public:
	
	Piramida(std::string nazwa, char kolor, int x, int y, char kierunek)
	{
		konstruktor(nazwa, kolor, x, y,kierunek);
	}

	/**Metoda odpowiedzialna za sprawdzenie czy ruch Piramidy na dana pozycje jest dopuszczany.
	* @overload
	*/
	bool CzyMozliwyRuch(int x, int y, Plansza P);

	/**Metoda odpowiedzialna za okreslenie zachowania lasera przy kontakcie z Piramida.
	* @overload
	*/
	bool ObslugaLasera(char& way);

};
/**Klasa reprezentujaca figure typu Anubis.
*/
class Anubis : public Figura
{
public:

	Anubis(std::string nazwa, char kolor, int x, int y, char kierunek)
	{
		konstruktor(nazwa, kolor, x, y, kierunek);
	}
	/**Metoda odpowiedzialna za sprawdzenie czy ruch Anubisa na dana pozycje jest dopuszczany.
	* @overload
	*/
	bool CzyMozliwyRuch(int x, int y, Plansza P);

	/**Metoda odpowiedzialna za okreslenie zachowania lasera przy kontakcie z Anubisem.
	* @overload
	*/
	bool ObslugaLasera(char& way);

};

/**Klasa reprezentujaca figure typu Skarabeusz.
*/
class Skarabeusz : public Figura
{
public:
	bool zamiana=0; /**<atrybut okresla czy w danym ruchu Skarabeusz zamienia sie miejscami z inna figura*/
	Skarabeusz(std::string nazwa, char kolor, int x, int y, char kierunek)
	{
		konstruktor(nazwa, kolor, x, y, kierunek);
	}
	/**Metoda odpowiedzialna za sprawdzenie czy ruch Skarabeusza na dana pozycje jest dopuszczany.
	* @overload
	*/
	bool CzyMozliwyRuch(int x, int y, Plansza P);

	/**Metoda odpowiedzialna za okreslenie zachowania lasera przy kontakcie ze Skarabeuszem.
	* @overload
	*/
	bool ObslugaLasera(char& way);

};

/**Klasa reprezentujaca figure typu Sfinks.
*/
class Sfinks : public Figura
{
public:
	
	Sfinks(std::string nazwa, char kolor, int x, int y, char kierunek)
	{
		konstruktor(nazwa, kolor, x, y, kierunek);
	}
	/**Metoda odpowiedzialna za sprawdzenie czy ruch Sfinksa na dana pozycje jest dopuszczany.
	* @overload
	*/
	bool CzyMozliwyRuch(int x, int y, Plansza P);

	/**Metoda odpowiedzialna za okreslenie zachowania lasera przy kontakcie ze Sfinksem.
	* @overload
	*/
	bool ObslugaLasera(char& way);

	
};

/**Klasa reprezentujaca figure typu Faraon.
*/
class Faraon : public Figura
{
public:
	Faraon(std::string nazwa, char kolor, int x, int y, char kierunek)
	{
		konstruktor(nazwa, kolor, x, y, kierunek);
	}
	/**Metoda odpowiedzialna za sprawdzenie czy ruch Faraona na dana pozycje jest dopuszczany.
	* @overload
	*/
	bool CzyMozliwyRuch(int x, int y, Plansza P);

	/**Metoda odpowiedzialna za okreslenie zachowania lasera przy kontakcie z Faraonem.
	* @overload
	*/
	bool ObslugaLasera(char& way);

};



