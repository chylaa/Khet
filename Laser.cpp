#include "Laser.h"

void Laser::DodajDoTablicy(char PreWay, bool CzyZbita) 
{
	//z uzyciem jeszcze 'way' i 'Pos'

	if (PreWay == 'x') return; //jesli to pierwszy krok lasera to pomijamy

	sf::Sprite s;

	s.setOrigin(4, 0);
	s.setPosition((Pos.x * square_size) + square_size / 2, (Pos.y * square_size) + square_size / 2);
	if (PreWay == 'n') s.setRotation(0);
	if (PreWay == 's') s.setRotation(180);
	if (PreWay == 'e') s.setRotation(90);
	if (PreWay == 'w') s.setRotation(270);

	TabLas.push_back(s);

	if (CzyZbita) return;

	s.setOrigin(4, 0);
	s.setPosition((Pos.x * square_size) + square_size / 2, (Pos.y * square_size) + square_size / 2);
	if (way == 'n') s.setRotation(180);
	if (way == 's') s.setRotation(0);
	if (way == 'e') s.setRotation(270);
	if (way == 'w') s.setRotation(90);

	TabLas.push_back(s);
}

void Laser::ObliczTrajektorie(Plansza P, Gracz& Gb, Gracz& Gc, Gracz& aktywny)
{
	char PreWay = 'x';
	bool CzyZbita = 0;
	if (Gc.Aktywny)
	{
		Pos.x = 0;
		Pos.y = 0;

	}
	else
	{
		Pos.x = 9;
		Pos.y = 7;
	}
	way = aktywny.Tab_Fig[ZnajdzFigure(Pos.x, Pos.y, aktywny.Tab_Fig)]->Kierunek;
	std::cout << "\n\n";
	while (1)
	{
		std::cout << "[Pusto] Gc_size: " << Gc.Tab_Fig.size() << " Gb_size: " << Gb.Tab_Fig.size() << std::endl;
		if (Pos.x > 9 || Pos.y > 7 || Pos.x < 0 || Pos.y < 0) break;

		if (P.plansza[Pos.x][Pos.y].fig != nullptr)
		{
			CzyZbita = P.plansza[Pos.x][Pos.y].fig->ObslugaLasera(way); //potrzebne tu zeby DodajDoTablicy mialo aktualne 'way' przy odbiciach 
		}
		DodajDoTablicy(PreWay, CzyZbita);
		if (P.plansza[Pos.x][Pos.y].fig == nullptr)
		{
			if (way == 'n') Pos.y--;
			if (way == 's') Pos.y++;
			if (way == 'w') Pos.x--;
			if (way == 'e') Pos.x++;
			PreWay = way;
			continue;
		}
		std::cout << "fig: " << P.plansza[Pos.x][Pos.y].fig->Nazwa << " ";
		//tu odbicia i zbicia
		if (CzyZbita) //zbita
		{

			std::cout << " Zbita " << " pos.x " << Pos.x << " pos.y " << Pos.y << " fig Gb pos tab: " << ZnajdzFigure(Pos.x, Pos.y, Gb.Tab_Fig);
			std::cout << "  Gc: " << ZnajdzFigure(Pos.x, Pos.y, Gc.Tab_Fig);
			if (ZnajdzFigure(Pos.x, Pos.y, aktywny.Tab_Fig) != -1)
			{
				aktywny.Tab_Fig.erase(aktywny.Tab_Fig.begin() + ZnajdzFigure(Pos.x, Pos.y, aktywny.Tab_Fig));
			}
			else
			{
				if (aktywny.Kolor == 'b')
				{
					std::cout << "[Gc]";
					Gc.Tab_Fig.erase(Gc.Tab_Fig.begin() + ZnajdzFigure(Pos.x, Pos.y, Gc.Tab_Fig));
				}
				else
				{
					std::cout << "[Gb]";
					Gb.Tab_Fig.erase(Gb.Tab_Fig.begin() + ZnajdzFigure(Pos.x, Pos.y, Gb.Tab_Fig));
				}
			}
			//P.plansza[Pos.x][Pos.y].fig = nullptr;
			break;
		}
		else
		{
			if (typeid(*P.plansza[Pos.x][Pos.y].fig) == typeid(Anubis))
			{
				TabLas.erase(TabLas.end() - 1);  //zeby sie ladnie laser na Anubisie wyswietlal
				break;
			}
		}

		std::cout << "way: " << way << " pos.x " << Pos.x << " pos.y " << Pos.y << std::endl;
		PreWay = way;
		if (way == 'n') Pos.y--;
		if (way == 's') Pos.y++;
		if (way == 'w') Pos.x--;
		if (way == 'e') Pos.x++;

	}
}