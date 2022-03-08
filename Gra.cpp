#include "Gra.h"


void SetOrginToCenter(sf::Sprite& image)
{
	image.setOrigin(image.getLocalBounds().width / 2, image.getLocalBounds().width / 2);
}


void Gra::PrzeciaganieUpuszczanie(Gracz aktywny, Gracz Gc, Gracz Gb, sf::Vector2i pos)
{
	//Podnoszenie figury
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		for (int i = 0; i < aktywny.Tab_Fig.size(); i++)
		{
			if (aktywny.Tab_Fig[i]->sprajt.getGlobalBounds().contains(pos.x, pos.y))
			{
				isMove = true;
				Ruszana = i;

				PreX = aktywny.Tab_Fig[i]->sprajt.getPosition().x; //do obslugi powrotu fig na miejsce po nieprawidlowym ruchu
				PreY = aktywny.Tab_Fig[i]->sprajt.getPosition().y;

				dx = pos.x - aktywny.Tab_Fig[i]->sprajt.getPosition().x; //zeby mozna bylo chwytac figury w dowolnym miejscu grafiki
				dy = pos.y - aktywny.Tab_Fig[i]->sprajt.getPosition().y;
			}
		}
	}
	//Upuszczanie figury
	if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left && isMove)
	{
		isMove = false;

		//==========Centrowanie figur w polu====== 
		sf::Vector2f NowaPos, NoweWsp; // np. P(0;120 , 0;120) -> S(60,60) czyli:
		NowaPos.x = int((aktywny.Tab_Fig[Ruszana]->sprajt.getPosition().x / square_size)) * square_size + (square_size / 2); // pozycja.x/120 daje <int> 0,1,2,3 itp
		NowaPos.y = int((aktywny.Tab_Fig[Ruszana]->sprajt.getPosition().y / square_size)) * square_size + (square_size / 2); // wiec *120 + 120/2
		
		NoweWsp.x = int(NowaPos.x / square_size); //wspolzedne <0;9>
		NoweWsp.y = int(NowaPos.y / square_size); //<0;7>
		
		if (aktywny.Tab_Fig[Ruszana]->CzyMozliwyRuch(NoweWsp.x, NoweWsp.y,szachownica)) 
		{
			//Obsluga skarabeusza
			if (typeid(*aktywny.Tab_Fig[Ruszana]) == typeid(Skarabeusz))
			{
				Skarabeusz*pom=dynamic_cast<Skarabeusz*>(aktywny.Tab_Fig[Ruszana]);
				if (pom->zamiana)
				{
					sf::Vector2f OldWsp;
					OldWsp.x = aktywny.Tab_Fig[Ruszana]->x_wsp;
					OldWsp.y = aktywny.Tab_Fig[Ruszana]->y_wsp;
					ZamienSkarabeusza(Gc, Gb,NoweWsp, OldWsp);
					pom->zamiana = 0;
				}
				pom = nullptr;
			}
			aktywny.Tab_Fig[Ruszana]->sprajt.setPosition(NowaPos);
			aktywny.Tab_Fig[Ruszana]->PrzypiszWsp(pos.x, pos.y);
			KoniecTury = 1; //upuszczanie na to samo pole nie konczy tury bo figura zajmuje pole "sobie samej"
			std::cout << "\n";
		}
		else
		{
			sf::Vector2f pom;
			pom.x = PreX;
			pom.y = PreY;
			aktywny.Tab_Fig[Ruszana]->sprajt.setPosition(pom);
		}
	}
}
bool Gra::Obracanie(Gracz active, int rotation, sf::Vector2i pos)
{

	for (int i = 0; i < active.Tab_Fig.size(); i++)
	{
		if (active.Tab_Fig[i]->sprajt.getGlobalBounds().contains(pos.x, pos.y))
		{
			if (typeid(*active.Tab_Fig[i]) == typeid(Sfinks))
			{
				if (!active.Tab_Fig[i]->CzyMozliwyObrot(rotation)) return 0;

			}
			active.Tab_Fig[i]->sprajt.rotate(rotation);
			active.Tab_Fig[i]->UstawKierunek(rotation);
			std::cout << "\nObracanie kierunek: " << active.Tab_Fig[i]->Kierunek;

			return 1;
		}
	}
	return 0;
}
Gracz Gra::ZamienGracza(Gracz& Gb, Gracz& Gc, Gracz active)
{

	if (Gb.Aktywny)
	{
		Gb = active;
		Gb.Aktywny = 0;
		Gc.Aktywny = 1;
		return Gc;
	}
	Gc = active;
	Gb.Aktywny = 1;
	Gc.Aktywny = 0;
	return Gb;
}
void Gra::ZamienSkarabeusza(Gracz Gc, Gracz Gb, sf::Vector2f NewWsp, sf::Vector2f OldWsp) 
{
	sf::Vector2f NowaPos;
	NowaPos.x = (OldWsp.x * square_size) + (square_size / 2); //nowa pozycja (px) drugiej figury
	NowaPos.y = (OldWsp.y * square_size) + (square_size / 2);
	int i;
	if (szachownica.plansza[(int)NewWsp.x][(int)NewWsp.y].fig->Kolor == 'c')
	{
		i = ZnajdzFigure(NewWsp.x, NewWsp.y, Gc.Tab_Fig);
		Gc.Tab_Fig[i]->x_wsp=OldWsp.x;
		Gc.Tab_Fig[i]->y_wsp = OldWsp.y;
		Gc.Tab_Fig[i]->sprajt.setPosition(NowaPos);
	}
	else
	{
		i = ZnajdzFigure(NewWsp.x, NewWsp.y, Gb.Tab_Fig);
		Gb.Tab_Fig[i]->x_wsp = OldWsp.x;
		Gb.Tab_Fig[i]->y_wsp = OldWsp.y;
		Gb.Tab_Fig[i]->sprajt.setPosition(NowaPos);
	}
}

char Gra::SprawdzFaraona()
{
	bool jest=0;

	for (int i = 0; i < Gb.Tab_Fig.size(); i++)
	{
		if (typeid(*Gb.Tab_Fig[i]) == typeid(Faraon))
		{
			jest = 1;
			break;
		}
	}
	if(!jest) return 'b';
	jest = 0;

	for (int i = 0; i < Gc.Tab_Fig.size(); i++)
	{
		if (typeid(*Gc.Tab_Fig[i]) == typeid(Faraon))
		{
			jest = 1;
			break;
		}
	}
	if(!jest) return 'c';

	return 'n';
}

