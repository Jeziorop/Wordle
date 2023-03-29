#include <SFML/Graphics.hpp>
#include <fstream>
#include "tile.h"
#include "functions.h"
#include "gameState.h"
#include <iostream>
#include <map>
#include <chrono>
#include <cstdlib>
#include <iostream>
const sf::Color black(0, 0, 0), grey(35, 35, 35), yellow(255, 159, 43), green(55, 194, 27);
const sf::Time mrug = sf::milliseconds(70);
int main()
{
	const std::vector<char> alfabet = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	const std::vector<int> alfabet2 = {40, 53, 51, 42, 32, 43, 44, 45, 37, 46, 47, 48, 55, 54, 38, 39, 30, 33, 41, 34, 36, 52, 31, 50, 35, 49};
	sf::RenderWindow app(sf::VideoMode(500, 620), "WORDLE", sf::Style::Close);
	srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	app.setFramerateLimit(60);
	sf::Font font;
	font.loadFromFile("res\\Hack-Regular.ttf");
	tile reset("", grey, true);
	tile defeat("", sf::Color(170, 60, 40), false);
	defeat.setFont(font);
	sf::RectangleShape obramowanie_kafelka(sf::Vector2f(50, 50));
	sf::Sprite restart, backspace;
	sf::Texture res, back;
	sf::Image icon;
	if(icon.loadFromFile("res\\icon.png"))
		app.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	std::map<std::string, bool> istniejace;
	std::vector<std::string> slownik;
	ustaw_pierdolniki(restart,backspace, reset, defeat, res, back, obramowanie_kafelka);
	wczytaj_slownik(slownik, istniejace);
reset:
	reset.setColor(grey);
	std::string haslo, input;
	do {
		haslo = slownik[rand() % slownik.size()];
	} while (czy_zle(haslo));
	defeat.setContent(haslo);
	std::vector<tile> all = create_all();
	for (auto& a : all)
		a.setFont(font);
	int kafelek = 0;
	obramowanie_kafelka.setPosition(all[kafelek].getPosition());
	obramowanie_kafelka.setOutlineColor(sf::Color(255, 255, 255, 170));
	gameState g = gameState::ACTIVE;
	bool blokada = false;
	sf::Clock clock;
	sf::Time delta;
	while (app.isOpen())
	{
		sf::Event t;
		while (app.pollEvent(t)) {
			if (t.type == sf::Event::Closed) {
				app.close();
			}
			else if (t.type == sf::Event::MouseButtonPressed)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::XButton1))
				{
					if (kafelek % 5 != 0)
					{
						kafelek--;
						obramowanie_kafelka.setPosition(all[kafelek].getPosition());
					}
					continue;
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::XButton2))
				{
					if (kafelek % 5 != 4)
					{
						kafelek++;
						obramowanie_kafelka.setPosition(all[kafelek].getPosition());

					}
					continue;
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
				{
					blokada = !blokada;
					if (blokada)
						obramowanie_kafelka.setOutlineColor(yellow);
					else
						obramowanie_kafelka.setOutlineColor(sf::Color(255, 255, 255, 170));
					continue;
				}
				int x = sf::Mouse::getPosition(app).x;
				int y = sf::Mouse::getPosition(app).y;
				if (g == gameState::ACTIVE)
				{
					for (int i = 30; i < all.size() - 1; ++i)
					{
						if (all[i].getCollide() && all[i].czy_kolizja(x, y) && kafelek < 30)
						{
							all[kafelek].setContent(all[i].getText());
							all[i].setZaciemnienie(mrug);
							int wiersz = kafelek / 5;
							input = all[wiersz * 5].getText().toAnsiString() + all[wiersz * 5 + 1].getText().toAnsiString() + all[wiersz * 5 + 2].getText().toAnsiString() + all[wiersz * 5 + 3].getText().toAnsiString() + all[wiersz * 5 + 4].getText().toAnsiString();
							to_lower(input);
							if (istniejace[input])
							{
								porownaj(wiersz, input, haslo, all);
								kafelek = wiersz * 5 + 5;
								obramowanie_kafelka.setPosition(all[kafelek].getPosition());
								if (input == haslo)
								{
									for (auto& a : all)
										a.setCollide(false);
									reset.setColor(green);
									g = gameState::WIN;
								}
							}
							else if (!blokada && kafelek % 5 != 4)
							{
								kafelek++;
								obramowanie_kafelka.setPosition(all[kafelek].getPosition());
							}
							break;
						}
					}

					//KASOWANIE 
					if (all[56].czy_kolizja(x, y))
					{
						all[56].setZaciemnienie(mrug);
						if (all[kafelek].getText().toAnsiString() != "")
						{
							all[kafelek].setContent("");
						}
						else if (!blokada && kafelek % 5 != 0)
						{
							kafelek--;
							all[kafelek].setContent("");
							obramowanie_kafelka.setPosition(all[kafelek].getPosition());
						}
					}
				}

				//RESET
				if (reset.czy_kolizja(x, y)) {
					reset.setZaciemnienie(mrug);
					goto reset;
				}

				//WYGRANA
				if (input == haslo)
				{
					for (auto &a : all)
						a.setCollide(false);
					reset.setColor(sf::Color(55, 194, 27));
					g = gameState::WIN;
				}
			}
			else if (t.type == sf::Event::KeyPressed)
			{
				std::cout << t.key.code << "\n";
				std::string in = "";
				if (g == gameState::ACTIVE && kafelek < 30)
				{
					if (t.key.code < 26 && t.key.code >= 0)
					{
						in = alfabet[t.key.code];
						all[alfabet2[t.key.code]].setZaciemnienie(mrug);
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace))
					{
						all[56].setZaciemnienie(mrug);
						if (all[kafelek].getText().toAnsiString() != "")
						{
							all[kafelek].setContent("");
						}
						else if (!blokada && kafelek % 5 != 0)
						{
							kafelek--;
							all[kafelek].setContent("");
							obramowanie_kafelka.setPosition(all[kafelek].getPosition());
						}
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && kafelek % 5 != 0)
					{
						kafelek--;
						obramowanie_kafelka.setPosition(all[kafelek].getPosition());
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && kafelek % 5 != 4)
					{
						kafelek++;
						obramowanie_kafelka.setPosition(all[kafelek].getPosition());
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					{
						blokada = !blokada;
						if (blokada)
							obramowanie_kafelka.setOutlineColor(yellow);
						else
							obramowanie_kafelka.setOutlineColor(sf::Color(255, 255, 255, 170));
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
						g = gameState::LOSE;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::End)) {
					reset.setZaciemnienie(mrug);
					goto reset;
				}
				if (in == "")
					continue;
				all[kafelek].setContent(in);
				int wiersz = kafelek / 5;
				input = all[wiersz * 5].getText().toAnsiString() + all[wiersz * 5 + 1].getText().toAnsiString() + all[wiersz * 5 + 2].getText().toAnsiString() + all[wiersz * 5 + 3].getText().toAnsiString() + all[wiersz * 5 + 4].getText().toAnsiString();
				to_lower(input);
				if (istniejace[input])
				{
					porownaj(kafelek / 5, input, haslo, all);
					kafelek = wiersz * 5 + 5;
					obramowanie_kafelka.setPosition(all[kafelek].getPosition());
					if (input == haslo)
					{
						for (auto& a : all)
							a.setCollide(false);
						reset.setColor(green);
						g = gameState::WIN;
					}
				}
				else if (!blokada && kafelek % 5 != 4)
				{
					kafelek++;
					obramowanie_kafelka.setPosition(all[kafelek].getPosition());
				}
			}
			else if (t.type == sf::Event::MouseWheelMoved)
			{
				int wiersz = kafelek / 5;
				if ((kafelek + t.mouseWheel.delta) > 0 && (kafelek + t.mouseWheel.delta) / 5 == wiersz)
					kafelek += t.mouseWheel.delta;
				else if (t.mouseWheel.delta > 0)
					kafelek = wiersz * 5 + 4;
				else
					kafelek = wiersz * 5;
				obramowanie_kafelka.setPosition(all[kafelek].getPosition());
			}
		}
		app.clear(sf::Color(15, 15, 15));
		delta = clock.getElapsedTime();
		clock.restart();
		for (auto& a : all)
		{
			if (a.getZaciemnienie().asMilliseconds() > delta.asMilliseconds())
				a.setZaciemnienie(sf::milliseconds(a.getZaciemnienie().asMilliseconds() - delta.asMilliseconds()));
			else
				a.setZaciemnienie(sf::milliseconds(0));
			a.show(app);
		}
		if (reset.getZaciemnienie().asMilliseconds() > delta.asMilliseconds())
			reset.setZaciemnienie(sf::milliseconds(reset.getZaciemnienie().asMilliseconds() - delta.asMilliseconds()));
		else
			reset.setZaciemnienie(sf::milliseconds(0));
		reset.show(app);
		app.draw(restart);
		app.draw(backspace);
		if (g == gameState::LOSE || (kafelek == 30 && g != gameState::WIN))
		{
			defeat.show(app);
			reset.setColor(green);
			g = gameState::LOSE;
		}
		else if (g == gameState::ACTIVE)
			app.draw(obramowanie_kafelka);
		app.display();
	}
}