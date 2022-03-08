#include "Interfejs.h"

sf::RenderWindow window(sf::VideoMode(1200, 960), "Khet_v0.9.5");

void Interfejs::Rysuj(Gracz Gb, Gracz Gc, sf::Sprite board)
{
	window.draw(board);
	for (float i = 0; i < Gc.Tab_Fig.size(); i++) window.draw(Gc.Tab_Fig[i]->sprajt);
	for (float i = 0; i < Gb.Tab_Fig.size(); i++) window.draw(Gb.Tab_Fig[i]->sprajt);
	window.display();
}

int Interfejs::Rozgrywka(Gracz& Gb, Gracz& Gc)
{
	window.setFramerateLimit(60);
	sf::Vector2u windowSize;
	windowSize.x = 1200;
	windowSize.y = 960;
	//===Wyswietl plansze====
	sf::Texture board_texture;
	board_texture.loadFromFile("Obrazy/board.png");
	sf::Sprite board;
	board.setTexture(board_texture);
	
	gra.Zeruj();

	gra.szachownica.WypelnijNull();
	gra.szachownica.PrzypiszPolaZabronione();

	gra.szachownica.WypelnijPlansze(Gc.Tab_Fig, Gb.Tab_Fig);

	while (true)
	{
		if (gra.KoniecTury)
		{
			std::cout << "\n";
			for (int i = 0; i < gra.aktywny.Tab_Fig.size(); i++) std::cout << "\nFigura " << gra.aktywny.Tab_Fig[i]->Nazwa << " x:" << gra.aktywny.Tab_Fig[i]->x_wsp << " y:" << gra.aktywny.Tab_Fig[i]->y_wsp << " kierunek: " << gra.aktywny.Tab_Fig[i]->Kierunek;
			//^wypis figur w konsoli
			laser.ObliczTrajektorie(gra.szachownica, Gb, Gc, gra.aktywny);
			Rysuj(Gb, Gc, board); //konieczne tu przed "RysujLaser" aby uniknac efektu "drzenia" figury 
			RysujLaser();
			gra.szachownica.WypelnijPlansze(Gc.Tab_Fig, Gb.Tab_Fig);
			gra.aktywny = gra.ZamienGracza(Gb, Gc, gra.aktywny); 
			//czy koniec?
			if (InfoKoniec(gra.SprawdzFaraona())) 
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(2500));
				menu.MenuWybor = 5;
				return 1;
			}

			if (Gc.Aktywny) Info("Ruch czerwonych");
			if (Gb.Aktywny) Info("Ruch bialych");
			gra.KoniecTury = 0;

		}

		window.pollEvent(gra.event);
		sf::Vector2i pos = sf::Mouse::getPosition(window);

		if (gra.event.type == sf::Event::Closed) //zamkniecie okna
		{
			window.close();
			menu.MenuWybor = 3;
			return 0;
		}

		if (gra.event.type == sf::Event::Resized) window.setSize(windowSize);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			break;
		}

		if (!(board.getGlobalBounds().contains(pos.x, pos.y)) && gra.isMove) //uniemozliwia przesuniecie obiektu poza obszar okna
		{
			sf::Vector2f pom;
			pom.x = gra.PreX;
			pom.y = gra.PreY;
			gra.aktywny.Tab_Fig[gra.Ruszana]->sprajt.setPosition(pom);
			gra.isMove = false;
			continue;
		}
		//=========Obracanie============
		if (gra.event.mouseButton.button == sf::Mouse::Right && gra.event.type == sf::Event::MouseButtonPressed && !gra.isMove)
		{
			gra.KoniecTury = gra.Obracanie(gra.aktywny, 90, pos);
			std::this_thread::sleep_for(std::chrono::milliseconds(200));//sleep
			while (window.pollEvent(gra.event)); //wyczyszczenie kolejki zdarzen
		}
		if (gra.event.mouseButton.button == sf::Mouse::Middle && gra.event.type == sf::Event::MouseButtonPressed && !gra.isMove)
		{
			gra.KoniecTury = gra.Obracanie(gra.aktywny, 270, pos);
			std::this_thread::sleep_for(std::chrono::milliseconds(200));//sleep
			while (window.pollEvent(gra.event)); //wyczyszczenie kolejki zdarzen
		}
		//=======Przeciaganie i upuszczanie=============
		gra.PrzeciaganieUpuszczanie(gra.aktywny, Gc, Gb, pos);

		if (gra.isMove)
		{
			gra.aktywny.Tab_Fig[gra.Ruszana]->sprajt.setPosition(pos.x - gra.dx, pos.y - gra.dy);
		}
		//======rysowanie===========

		if (gra.KoniecTury)
		{
			gra.szachownica.WypelnijPlansze(Gc.Tab_Fig, Gb.Tab_Fig);
			gra.szachownica.WypiszPlansze();
		}
		Rysuj(Gb, Gc, board);

	}
	return 0;
	board_texture.~Texture();
}

bool Interfejs::InfoKoniec(char c)
{
	if (c == 'b')
	{
		Info("Wygrywa czerwony!");
		return 1;
	}
	if (c == 'c')
	{
		Info("Wygrywa bialy!");
		return 1;
	}
	return 0;
}

void Interfejs::RysujLaser()
{
	int i = 0;
	sf::Texture Las_t;
	Las_t.loadFromFile("Obrazy/LaserCol.png");
	for (int i = 0; i < this->laser.TabLas.size(); i++)
	{
		this->laser.TabLas[i].setTexture(Las_t);
		window.draw(this->laser.TabLas[i]);
		std::this_thread::sleep_for(std::chrono::milliseconds(80)); //"animacja"
		window.display(); //
	}
	//std::this_thread::sleep_for(std::chrono::milliseconds(100)); //ciagla linia
	//window.display();
	this->laser.TabLas.clear();
	Las_t.~Texture();
}

void Interfejs::Info(std::string s)
{
	sf::Text tekst;
	sf::Font font;
	font.loadFromFile("Obrazy/font.otf");
	tekst.setFont(font);
	tekst.setString(s);
	tekst.setCharacterSize(60);
	if (s[5] == 'c' || s[8] =='c') tekst.setFillColor(sf::Color::Red);
	tekst.setOutlineColor(sf::Color::Black);
	tekst.setOutlineThickness(12);
	tekst.setOrigin(tekst.getLocalBounds().width / 2, tekst.getLocalBounds().height / 2);
	tekst.setPosition(600, 480);
	window.draw(tekst);
	window.display();
	std::this_thread::sleep_for(std::chrono::milliseconds(1500));
}


int Menu::MenuDisplay() 
{
	sf::Event event;

	sf::Texture t_Gra_Button, t_ZapiszButton, t_WczytajButton, t_TitleScreen;
	t_Gra_Button.loadFromFile("Obrazy/GraButton.png");
	t_TitleScreen.loadFromFile("Obrazy/TitleScreen2.png");
	t_ZapiszButton.loadFromFile("Obrazy/ZapiszButton.png");
	t_WczytajButton.loadFromFile("Obrazy/WczytajButton.png");
	sf::Sprite Gra_Button, ZapiszButton, WczytajButton;
	sf::Sprite TitleScreen;

	Gra_Button.setTexture(t_Gra_Button);
	ZapiszButton.setTexture(t_ZapiszButton);
	WczytajButton.setTexture(t_WczytajButton);
	TitleScreen.setTexture(t_TitleScreen);

	Gra_Button.setPosition(window.getSize().x / 2, (window.getSize().y / 2) + 90);
	WczytajButton.setPosition(window.getSize().x / 2, (window.getSize().y / 2) + 202);
	ZapiszButton.setPosition(window.getSize().x / 2, (window.getSize().y / 2) + 314);
	SetOrginToCenter(Gra_Button);
	SetOrginToCenter(WczytajButton);
	SetOrginToCenter(ZapiszButton);

	while (true)
	{
		window.display();
		sf::Vector2i pos = sf::Mouse::getPosition(window);
		Gra_Button.setScale(1, 1);
		WczytajButton.setScale(1, 1);
		ZapiszButton.setScale(1, 1);

		window.pollEvent(event);

		if (event.type == sf::Event::Closed) {
			window.close();
			MenuWybor = 3;
			return 3; //zamknij menu
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			MenuWybor = 4;
			return 4;
		}
		if (Gra_Button.getGlobalBounds().contains(pos.x, pos.y))
		{
			Gra_Button.setScale(1.05, 1.05);

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				MenuWybor = 1;
				return 1;
			}
		}
		if (WczytajButton.getGlobalBounds().contains(pos.x, pos.y))
		{
			WczytajButton.setScale(1.05, 1.05);
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				MenuWybor = 0;
				return 0;
			}
		}
		if (ZapiszButton.getGlobalBounds().contains(pos.x, pos.y))
		{
			ZapiszButton.setScale(1.05, 1.05);
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				MenuWybor = 2;
				return 2;
			}
		}

		window.draw(TitleScreen);
		window.draw(Gra_Button);
		window.draw(WczytajButton);
		window.draw(ZapiszButton);

	}
	t_Gra_Button.~Texture();
	t_TitleScreen.~Texture();
	t_WczytajButton.~Texture();
	t_ZapiszButton.~Texture();
	return -1;
}