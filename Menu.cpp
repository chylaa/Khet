#include "Menu.h"
#include <stdexcept>


void Menu::SetTekstur(Gracz& Gc, Gracz& Gb)
{
	for (int i = 0; i < Gc.Tab_Fig.size(); i++)
	{
		Gc.Tab_Fig[i]->tekstura.loadFromFile("Obrazy/" + Gc.Tab_Fig[i]->Nazwa + ".png");
		Gc.Tab_Fig[i]->sprajt.setTexture(Gc.Tab_Fig[i]->tekstura);
		SetOrginToCenter(Gc.Tab_Fig[i]->sprajt);
		Gc.Tab_Fig[i]->sprajt.setPosition((Gc.Tab_Fig[i]->x_wsp * square_size) + (square_size / 2), (Gc.Tab_Fig[i]->y_wsp * square_size) + (square_size / 2));
	}
	for (int i = 0; i < Gb.Tab_Fig.size(); i++)
	{
		Gb.Tab_Fig[i]->tekstura.loadFromFile("Obrazy/" + Gb.Tab_Fig[i]->Nazwa + ".png");
		Gb.Tab_Fig[i]->sprajt.setTexture(Gb.Tab_Fig[i]->tekstura);
		SetOrginToCenter(Gb.Tab_Fig[i]->sprajt);
		Gb.Tab_Fig[i]->sprajt.setPosition((Gb.Tab_Fig[i]->x_wsp * square_size) + (square_size / 2), (Gb.Tab_Fig[i]->y_wsp * square_size) + (square_size / 2));
	}

}

int Menu::ObslugaWyboru(Gra& gra) 
{

	if(MenuWybor==3 || MenuWybor==4) //nowa gra
	{
		return 1; 
	}
	if(MenuWybor == 2) //zapisz
	{
		ZapiszGre(gra);
		return 1;
	}
	if (MenuWybor == 1)
	{
		gra.Zeruj();
		NoweFig(gra);
		gra.aktywny = gra.Gb;
		gra.szachownica.WypelnijPlansze(gra.Gc.Tab_Fig, gra.Gb.Tab_Fig);
		return 1;
	}
	if (MenuWybor == 0) //wczytaj i ustaw figury
	{
		//gra.Zeruj();
		try
		{
			WczytajFig(gra);
		}
		catch (std::invalid_argument& e)
		{
			std::cout << "\nError: " << e.what();
			return 0;
		}
		if (gra.Gb.Aktywny) gra.aktywny = gra.Gb; //!!!!!!!!!!
		if (gra.Gc.Aktywny) gra.aktywny = gra.Gc;
		gra.szachownica.WypelnijPlansze(gra.Gc.Tab_Fig, gra.Gb.Tab_Fig);
		return 1;
	}
	
	return 0;
}

void Menu::NoweFig(Gra& gra) 
{

	Piramida* p1 = new Piramida("Piramida_b", 'b', 9, 4, 's');
	Piramida* p2 = new Piramida("Piramida_b", 'b', 9, 3, 'w');
	Piramida* p3 = new Piramida("Piramida_b", 'b', 7, 6, 'n');
	Piramida* p4 = new Piramida("Piramida_b", 'b', 2, 7, 'w');
	Piramida* p5 = new Piramida("Piramida_b", 'b', 2, 4, 'w');
	Piramida* p6 = new Piramida("Piramida_b", 'b', 2, 3, 's');
	Piramida* p7 = new Piramida("Piramida_b", 'b', 3, 2, 'w');
	Sfinks* s1 = new Sfinks("Sfinks_b", 'b', 9, 7, 'n');
	Skarabeusz* sk1 = new Skarabeusz("Skarabeusz_b", 'b', 4, 4, 'e');
	Skarabeusz* sk2 = new Skarabeusz("Skarabeusz_b", 'b', 5, 4, 'n');
	Anubis* a1 = new Anubis("Anubis_b", 'b', 5, 7, 'n');
	Anubis* a2 = new Anubis("Anubis_b", 'b', 3, 7, 'n');
	Faraon* f = new Faraon("Faraon_b", 'b', 4, 7, 'n');

	Piramida* P1 = new Piramida("piramida", 'c', 0, 3, 'n');
	Piramida* P2 = new Piramida("piramida", 'c', 0, 4, 'e');
	Piramida* P3 = new Piramida("piramida", 'c', 2, 1, 's');
	Piramida* P4 = new Piramida("piramida", 'c', 7, 0, 'e');
	Piramida* P5 = new Piramida("piramida", 'c', 7, 3, 'e');
	Piramida* P6 = new Piramida("piramida", 'c', 7, 4, 'n');
	Piramida* P7 = new Piramida("piramida", 'c', 6, 5, 'e');
	Sfinks* S1 = new Sfinks("Sfinks", 'c', 0, 0, 's');
	Skarabeusz* Sk1 = new Skarabeusz("Skarabeusz", 'c', 4, 3, 's');
	Skarabeusz* Sk2 = new Skarabeusz("Skarabeusz", 'c', 5, 3, 'w');
	Anubis* A1 = new Anubis("Anubis", 'c', 4, 0, 's');
	Anubis* A2 = new Anubis("Anubis", 'c', 6, 0, 's');
	Faraon* F = new Faraon("Faraon", 'c', 5, 0, 's');

	//gra.Gb.UsunFig();
	//gra.Gc.UsunFig();
	gra.Gb.Tab_Fig.resize(MaxIloscFig, nullptr);
	gra.Gc.Tab_Fig.resize(MaxIloscFig, nullptr);

	gra.Gb.Tab_Fig = { p1,p2,p3,p4,p5,p6,p7,s1,sk1,sk2,a1,a2,f };
	gra.Gc.Tab_Fig = { P1,P2,P3,P4,P5,P6,P7,S1,Sk1,Sk2,A1,A2,F };
	gra.Gb.Aktywny = 1;
	gra.Gc.Aktywny = 0;
	gra.Gc.Kolor = 'c';
	gra.Gb.Kolor = 'b';

	SetTekstur(gra.Gc, gra.Gb);


}

void Menu::ZapiszGre(Gra& gra)
{
	std::ofstream PlikZapis;
	PlikZapis.open("save.txt",std::ios::trunc);


	for (int i = 0; i < gra.Gb.Tab_Fig.size(); i++)
	{
		PlikZapis << "\n" << gra.Gb.Tab_Fig[i]->Nazwa << " ";
		PlikZapis << gra.Gb.Tab_Fig[i]->Kierunek << " ";
		PlikZapis << gra.Gb.Tab_Fig[i]->x_wsp << " ";
		PlikZapis << gra.Gb.Tab_Fig[i]->y_wsp << " ";
	}
	PlikZapis << "\nGb"; //wyznacza koniec
	for (int i = 0; i < gra.Gc.Tab_Fig.size(); i++)
	{
		PlikZapis << "\n" << gra.Gc.Tab_Fig[i]->Nazwa << " ";
		PlikZapis << gra.Gc.Tab_Fig[i]->Kierunek << " ";
		PlikZapis << gra.Gc.Tab_Fig[i]->x_wsp << " ";
		PlikZapis << gra.Gc.Tab_Fig[i]->y_wsp << " ";
	}
	PlikZapis << "\nGc"<< std::endl; // wyznacza koniec
	PlikZapis << gra.Gb.Aktywny << std::endl;
	PlikZapis << gra.Gc.Aktywny << std::endl;

	PlikZapis.close();
}

void Menu::WczytajFig(Gra& gra)
{
	std::string bufor;
	char kier;
	int x, y;
	int i = 0;
	std::ifstream PlikWczyt("save.txt");

	NoweFig(gra); 
	if (!PlikWczyt.good()) throw std::invalid_argument("Plik z zapisem nie istnieje");

	while (1)
	{
		PlikWczyt >> bufor;
		if (bufor == "Gb") break;
		PlikWczyt >> kier;
		PlikWczyt >> x;
		PlikWczyt >> y;
		if (x < 0 || y < 0 || x>9 || y>7 || (kier != 'n' && kier != 'e' && kier != 'w' && kier != 's') || i > 13 || PlikWczyt.eof()) //(x,y,kier nie w zakresie - i>MaxIloscLinii - ktoras zmienna pusta)
		{
			throw std::invalid_argument("Zawartosc pliku z zapisem jest uszkodzona!");
		}
		std::cout << "[Gb] Zaladowano: " << bufor << std::endl;
		if (bufor == "Piramida_b") gra.Gb.Tab_Fig[i]=new Piramida(bufor, 'b', x, y, kier); //gra.Gb.Tab_Fig.push_back(new Piramida(bufor, 'b', x, y, kier));
		if (bufor == "Sfinks_b") gra.Gb.Tab_Fig[i] = new Sfinks(bufor, 'b', x, y, kier);//gra.Gb.Tab_Fig.push_back(new Sfinks(bufor, 'b', x, y, kier));
		if (bufor == "Skarabeusz_b") gra.Gb.Tab_Fig[i] = new Skarabeusz(bufor, 'b', x, y, kier);//gra.Gb.Tab_Fig.push_back(new Skarabeusz(bufor, 'b', x, y, kier));
		if (bufor == "Anubis_b") gra.Gb.Tab_Fig[i] = new Anubis(bufor, 'b', x, y, kier);//gra.Gb.Tab_Fig.push_back(new Anubis(bufor, 'b', x, y, kier));
		if (bufor == "Faraon_b") gra.Gb.Tab_Fig[i] = new Faraon(bufor, 'b', x, y, kier);//gra.Gb.Tab_Fig.push_back(new Faraon(bufor, 'b', x, y, kier));
		i++;
	}

	for (int j = MaxIloscFig-1; j >= i; j--) delete gra.Gb.Tab_Fig[j];
	gra.Gb.Tab_Fig.resize(i,nullptr); //

	i=0;

	while (1)
	{
		PlikWczyt >> bufor;
		if (bufor == "Gc") break;
		PlikWczyt >> kier;
		PlikWczyt >> x;
		PlikWczyt >> y;
		if (x < 0 || y < 0 || x>9 || y>7 || (kier != 'n' && kier != 'e' && kier != 'w' && kier != 's') || i > 13 || PlikWczyt.eof()) //(x,y,kier nie w zakresie - i>MaxIloscLinii - ktoras zmienna pusta)
		{
			throw std::invalid_argument("Zawartosc pliku z zapisem jest uszkodzona!");
		}
		std::cout << "[Gc] Zaladowano: " << bufor << std::endl;
		if (bufor == "piramida") gra.Gc.Tab_Fig[i] = new Piramida(bufor, 'c', x, y, kier);//gra.Gc.Tab_Fig.push_back(new Piramida(bufor, 'c', x, y, kier));
		if (bufor == "Sfinks")  gra.Gc.Tab_Fig[i] = new Sfinks(bufor, 'c', x, y, kier);//gra.Gc.Tab_Fig.push_back(new Sfinks(bufor, 'c', x, y, kier));
		if (bufor == "Skarabeusz")  gra.Gc.Tab_Fig[i] = new Skarabeusz(bufor, 'c', x, y, kier);//gra.Gc.Tab_Fig.push_back(new Skarabeusz(bufor, 'c', x, y, kier));
		if (bufor == "Anubis") gra.Gc.Tab_Fig[i] = new Anubis(bufor, 'c', x, y, kier); //gra.Gc.Tab_Fig.push_back(new Anubis(bufor, 'c', x, y, kier));
		if (bufor == "Faraon")  gra.Gc.Tab_Fig[i] = new Faraon(bufor, 'c', x, y, kier);// gra.Gc.Tab_Fig.push_back(new Faraon(bufor, 'c', x, y, kier));
		i++;
	}

	for (int j = MaxIloscFig - 1; j >= i; j--) delete gra.Gc.Tab_Fig[j];
	gra.Gc.Tab_Fig.resize(i,nullptr); //

	PlikWczyt >> gra.Gb.Aktywny;
	PlikWczyt >> gra.Gc.Aktywny;
	

	SetTekstur(gra.Gc, gra.Gb);
	
	PlikWczyt.close();

}
