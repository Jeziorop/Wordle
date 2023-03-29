#pragma once
#include "SFML/Graphics.hpp"
class tile
{
	sf::RectangleShape body;
	sf::RectangleShape zaciemnienie;
	sf::Time t_zaciemnienie;
	bool collide;
	sf::Text content;
public:
	static sf::Font font;
	tile(const std::string& s, sf::Color c, bool b);
	void setColor(sf::Color c);
	void setContent(const std::string& s);
	void setPosition(const float& x, const float& y);
	void setCollide(const bool& b);
	void setSize(const int &x, const int &y); 
	void setFont(const sf::Font& f);
	void show(sf::RenderWindow &app);
	void setZaciemnienie(const sf::Time &s);
	sf::RectangleShape getBody();
	sf::String getText();
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	sf::Time getZaciemnienie();
	bool getCollide();

	bool czy_kolizja(const float& x, const float& y);
};

