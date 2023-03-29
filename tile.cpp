#include "tile.h"
tile::tile(const std::string& s, sf::Color c, bool b)
{
	body.setSize(sf::Vector2f(50.f, 50.f));
	body.setFillColor(c);
	body.setOutlineColor(sf::Color(0, 0, 0));
	body.setOutlineThickness(3.f);
	content.setCharacterSize(22);
	content.setFillColor(sf::Color::White);
	content.setString(s);
	collide = b;
	t_zaciemnienie = sf::seconds(0.f);
	zaciemnienie.setFillColor(sf::Color(0, 0, 0, 100));
	zaciemnienie.setSize(body.getSize());
}
void tile::setColor(sf::Color c)
{
	body.setFillColor(c);
}
void tile::setContent(const std::string& s)
{
	content.setString(s);
}
void tile::setPosition(const float& x, const float& y)
{
	body.setPosition(sf::Vector2f(x, y));
	zaciemnienie.setPosition(sf::Vector2f(x, y));
	content.setPosition(sf::Vector2f(x + 17, y + 11));
}
void tile::setCollide(const bool &b)
{
	collide = b;
}
void tile::setSize(const int& x, const int& y)
{
	body.setSize(sf::Vector2f(x, y));
}
void tile::show(sf::RenderWindow &app)
{
	app.draw(body);
	if (t_zaciemnienie.asMilliseconds() != 0)
		app.draw(zaciemnienie);
	app.draw(content);
}
void tile::setZaciemnienie(const sf::Time &s)
{
	t_zaciemnienie = s;
}
void tile::setFont(const sf::Font &f)
{
	content.setFont(f);
}
sf::RectangleShape tile::getBody()
{
	return body;
}
sf::String tile::getText()
{
	return content.getString();
}
bool tile::getCollide()
{
	return collide;
}
sf::Vector2f tile::getPosition()
{
	return body.getPosition();
}
sf::Vector2f tile::getSize()
{
	return body.getSize();
}
sf::Time tile::getZaciemnienie()
{
	return t_zaciemnienie;
}
bool tile::czy_kolizja(const float& x, const float& y)
{
	return collide && body.getPosition().x <= x && body.getPosition().y <= y && body.getPosition().x + body.getSize().x >= x && body.getPosition().y + body.getSize().y >= y;
}
