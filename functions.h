#pragma once
const extern sf::Color black, grey, green, yellow;
const std::vector<std::string> alfabet = { "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "A", "S", "D", "F", "G", "H", "J", "K", "L", "Z", "X", "C", "V", "B", "N", "M", ""};
std::vector<tile> create_all()
{
	std::vector<tile> all;
	tile a("", grey, false);
	for (int i = 0; i < 30; ++i)
	{
		a.setPosition(105 + (i % 5) * 60, 20 + (i / 5) * 60);
		all.emplace_back(a);
	}
	a.setCollide(true);
	for (int i = 0; i < 10; ++i)
	{
		a.setContent(alfabet[i]);
		a.setPosition(50 * i, 440);
		all.emplace_back(a);
	}
	for (int i = 10; i < 19; ++i)
	{
		a.setContent(alfabet[i]);
		a.setPosition(50 * (i - 10) + 25, 493);
		all.emplace_back(a);
	}
	for (int i = 19; i < alfabet.size(); ++i)
	{
		a.setContent(alfabet[i]);
		a.setPosition(50 * (i - 19) + 50, 546);
		all.emplace_back(a);
	}
	return all;
}
void ustaw_pierdolniki(sf::Sprite& restart, sf::Sprite &backspace, tile& reset, tile& lose, sf::Texture& res, sf::Texture& back, sf::RectangleShape& obramowka)
{
	obramowka.setFillColor(sf::Color::Transparent);
	obramowka.setOutlineThickness(1);
	obramowka.setOutlineColor(sf::Color(255, 255, 255, 170));
	res.loadFromFile("res\\restart.png");
	back.loadFromFile("res\\delete.png");
	restart.setTexture(res);
	backspace.setTexture(back);
	restart.setTextureRect(sf::IntRect(0, 0, 32, 32));
	backspace.setTextureRect(sf::IntRect(0, 0, 32, 32));
	restart.setPosition(sf::Vector2f(19, 19));
	backspace.setPosition(sf::Vector2f(409, 555));
	lose.setPosition(200, 380);
	lose.setSize(100, 50);
	reset.setPosition(10, 10);
}
void wczytaj_slownik(std::vector<std::string>& list, std::map<std::string, bool>& dictionary)
{
	std::ifstream plik("res\\slowa.txt");
	std::string linia;
	while (plik >> linia)
	{
		list.push_back(linia);
		dictionary[linia] = true;
	}
	plik.close();
}
bool czy_zle(const std::string h)
{
	std::vector<bool> uzyte(26, false);
	bool ans = false;
	for (int i = 0; i < h.size(); ++i)
	{
		if (uzyte[h[i] - 97])
		{
			ans = true;
			break;
		}
		uzyte[h[i] - 97] = true;
	}
	return ans;
}
void to_lower(std::string& s)
{
	for (int i = 0; i < s.size(); ++i)
		s[i] = s[i] + 32;
}
void porownaj(const int row, const std::string i, const std::string h, std::vector<tile> &all)
{
	for (int z = 0; z < 5; ++z)
	{
		for (int x = 0; x < 5; ++x)
		{
			if (i[z] != h[x])
				continue;
			if (z == x)
			{
				all[row * 5 + z].setColor(green);
				for (int j = 30; j < all.size(); ++j)
					if (i[z] - 32 == all[j].getText().toAnsiString()[0])
						all[j].setColor(green);
				continue;
			}
			all[row * 5 + z].setColor(yellow);
			for (int j = 30; j < all.size(); ++j)
				if (i[z] - 32 == all[j].getText().toAnsiString()[0] && all[j].getBody().getFillColor() != green)
					all[j].setColor(yellow);
		}
		for (int j = 30; j < all.size(); ++j)
			if (i[z] - 32 == all[j].getText().toAnsiString()[0] && all[j].getBody().getFillColor() == grey)
				all[j].setColor(black);
	}

}