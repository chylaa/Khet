#include <iostream>
#include "Figura.h"


void Figura::PrzypiszWsp(int x, int y) //Przypisuje wspolrzedne na planszy (lewy gorny kwadrat [0,0])
{
	this->x_wsp = int(x / square_size);
	this->y_wsp = int(y / square_size);
}

void Figura::UstawKierunek(int rotation)
{
	char PreKier = this->Kierunek;
	std::	cout << "\nUstawKierunek this: " << this->Kierunek;
	if (PreKier == 'n' && rotation == 90) this->Kierunek = 'e';
	if (PreKier == 'n' && rotation == 270) this->Kierunek = 'w';
	if (PreKier == 'e' && rotation == 90) this->Kierunek = 's';
	if (PreKier == 'e' && rotation == 270) this->Kierunek = 'n';
	if (PreKier == 's' && rotation == 90) this->Kierunek = 'w';
	if (PreKier == 's' && rotation == 270) this->Kierunek = 'e';
	if (PreKier == 'w' && rotation == 90) this->Kierunek = 'n';
	if (PreKier == 'w' && rotation == 270) this->Kierunek = 's';
}

bool Figura::CzyMozliwyObrot(int rotation)
{
	if (this->Kolor == 'b')
	{
		if (this->Kierunek == 'n' && rotation == 270) return 1;
		if (this->Kierunek == 'w' && rotation == 90) return 1;
	}
	else
	{
		if (this->Kierunek == 's' && rotation == 270) return 1;
		if (this->Kierunek == 'e' && rotation == 90) return 1;
	}
	return 0;
}

int ZnajdzFigure(int x, int y, std::vector <Figura*> tab_fig)
{

	for (int i = 0; i < tab_fig.size(); i++)
	{
		if (tab_fig[i]->x_wsp == x && tab_fig[i]->y_wsp == y) return i;
	}
	return -1;
}

bool Piramida::CzyMozliwyRuch(int x, int y, Plansza P)
{
	if (P.plansza[x][y].fig != nullptr) return 0;
	if (P.plansza[x][y].RodzajPola != 'n' && P.plansza[x][y].RodzajPola != this->Kolor) return 0;

	if (this->x_wsp + 1 == x && this->y_wsp == y) return 1;
	if (this->x_wsp - 1 == x && this->y_wsp == y) return 1;
	if (this->y_wsp + 1 == y && this->x_wsp == x) return 1;
	if (this->y_wsp - 1 == y && this->x_wsp == x) return 1;

	if (this->x_wsp + 1 == x && this->y_wsp + 1 == y) return 1;
	if (this->x_wsp - 1 == x && this->y_wsp - 1 == y) return 1;
	if (this->x_wsp + 1 == x && this->y_wsp - 1 == y) return 1;
	if (this->x_wsp - 1 == x && this->y_wsp + 1 == y) return 1;

	return 0;
}

bool Piramida::ObslugaLasera(char& way)
{
	char pom = way; //do wykrycia czy nastapilo odbicie
	if (this->Kierunek == 's' && way == 'n') way = 'w';
	if (this->Kierunek == 's' && way == 'e') way = 's';
	if (this->Kierunek == 'n' && way == 's') way = 'e';
	if (this->Kierunek == 'n' && way == 'w') way = 'n';
	if (this->Kierunek == 'e' && way == 'n') way = 'e';
	if (this->Kierunek == 'e' && way == 'w') way = 's';
	if (this->Kierunek == 'w' && way == 's') way = 'w';
	if (this->Kierunek == 'w' && way == 'e') way = 'n';

	if (pom == way) return 1;
	return 0;
}

bool Anubis::CzyMozliwyRuch(int x, int y, Plansza P)
{
	if (P.plansza[x][y].fig != nullptr) return 0;
	if (P.plansza[x][y].RodzajPola != 'n' && P.plansza[x][y].RodzajPola != this->Kolor) return 0;
	if (this->x_wsp + 1 == x && this->y_wsp == y) return 1;
	if (this->x_wsp - 1 == x && this->y_wsp == y) return 1;
	if (this->y_wsp + 1 == y && this->x_wsp == x) return 1;
	if (this->y_wsp - 1 == y && this->x_wsp == x) return 1;

	if (this->x_wsp + 1 == x && this->y_wsp + 1 == y) return 1;
	if (this->x_wsp - 1 == x && this->y_wsp - 1 == y) return 1;
	if (this->x_wsp + 1 == x && this->y_wsp - 1 == y) return 1;
	if (this->x_wsp - 1 == x && this->y_wsp + 1 == y) return 1;

	return 0;
}

bool Anubis::ObslugaLasera(char& way)
{
	if (this->Kierunek == 'n' && way == 's') return 0;
	if (this->Kierunek == 's' && way == 'n') return 0;
	if (this->Kierunek == 'w' && way == 'e') return 0;
	if (this->Kierunek == 'e' && way == 'w') return 0;
	return 1;
}

bool Skarabeusz::CzyMozliwyRuch(int x, int y, Plansza P)
{
	int czy = 0;
	if (P.plansza[x][y].RodzajPola != 'n' && P.plansza[x][y].RodzajPola != this->Kolor) return 0;
	if (this->x_wsp + 1 == x && this->y_wsp == y) czy++;
	if (this->x_wsp - 1 == x && this->y_wsp == y) czy++;
	if (this->y_wsp + 1 == y && this->x_wsp == x) czy++;
	if (this->y_wsp - 1 == y && this->x_wsp == x) czy++;

	if (this->x_wsp + 1 == x && this->y_wsp + 1 == y) czy++;
	if (this->x_wsp - 1 == x && this->y_wsp - 1 == y) czy++;
	if (this->x_wsp + 1 == x && this->y_wsp - 1 == y) czy++;
	if (this->x_wsp - 1 == x && this->y_wsp + 1 == y) czy++;

	if (P.plansza[x][y].fig != nullptr)
	{
		if (czy && (typeid(*P.plansza[x][y].fig) == typeid(Piramida) || typeid(*P.plansza[x][y].fig) == typeid(Anubis)))
		{
			this->zamiana = 1;
			return 1;
		}
	}
	if (czy && (P.plansza[x][y].fig == nullptr)) return 1;
	return 0;
}

bool Skarabeusz::ObslugaLasera(char& way)
{
	if (this->Kierunek == 's' || this->Kierunek == 'n')
	{
		if (way == 'n')
		{
			way = 'w';
			return 0;
		}
		if (way == 'e')
		{
			way = 's';
			return 0;
		}
		if (way == 's') way = 'e';
		if (way == 'w') way = 'n';
	}
	else
	{
		if (way == 'n')
		{
			way = 'e';
			return 0;
		}
		if (way == 'w')
		{
			way = 's';
			return 0;
		}
		if (way == 's') way = 'w';
		if (way == 'e') way = 'n';
	}
	return 0;
}

bool Sfinks::CzyMozliwyRuch(int x, int y, Plansza P)
{
	if (this->x_wsp == x && this->y_wsp == y) return 0;
	return 0;
}

bool Sfinks::ObslugaLasera(char& way)
{
	return 0;
}

bool Faraon::CzyMozliwyRuch(int x, int y, Plansza P)
{
	if (P.plansza[x][y].fig != nullptr) return 0;
	if (P.plansza[x][y].RodzajPola != 'n' && P.plansza[x][y].RodzajPola != this->Kolor) return 0;
	if (this->x_wsp + 1 == x && this->y_wsp == y) return 1;
	if (this->x_wsp - 1 == x && this->y_wsp == y) return 1;
	if (this->y_wsp + 1 == y && this->x_wsp == x) return 1;
	if (this->y_wsp - 1 == y && this->x_wsp == x) return 1;

	if (this->x_wsp + 1 == x && this->y_wsp + 1 == y) return 1;
	if (this->x_wsp - 1 == x && this->y_wsp - 1 == y) return 1;
	if (this->x_wsp + 1 == x && this->y_wsp - 1 == y) return 1;
	if (this->x_wsp - 1 == x && this->y_wsp + 1 == y) return 1;

	return 0;
}

bool Faraon::ObslugaLasera(char& way)
{
	return 1;
}





void Plansza::WypelnijNull()
{
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				plansza[i][j].fig = nullptr;
				plansza[i][j].RodzajPola = 'n';
			}
		}
	}
}
void Plansza::WypelnijPlansze(std::vector <Figura*> &TGc, std::vector <Figura*> &TGb)
{

	std::vector <Figura*> TabFig;
	TabFig.insert(TabFig.end(), TGc.begin(), TGc.end());
	TabFig.insert(TabFig.end(), TGb.begin(), TGb.end());

	//std::cout << "\nsize: " << TabFig.size();

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (ZnajdzFigure(i, j, TabFig) == -1)
			{
				plansza[i][j].fig = nullptr;
			}
			else {
				plansza[i][j].fig = TabFig[ZnajdzFigure(i, j, TabFig)];
			}
		}
	}
}
void Plansza::WypiszPlansze()
{
	for (int i = 0; i < 8; i++)
	{
		std::cout << "\n";
		for (int j = 0; j < 10; j++)
		{
			if (plansza[j][i].fig == nullptr)
			{
				std::cout << "[  ]";
			}
			else
			{
				std::cout << " " << plansza[j][i].fig->Nazwa.substr(0, 2) << " ";
			}

		}
	}
}
void Plansza::PrzypiszPolaZabronione()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i == 0) plansza[i][j].RodzajPola = 'c';
			if (i == 9) plansza[i][j].RodzajPola = 'b';
			if (i == 1 && (j == 0 || j == 7)) plansza[i][j].RodzajPola = 'b';
			if (i == 8 && (j == 0 || j == 7)) plansza[i][j].RodzajPola = 'c';
		}
	}
}
