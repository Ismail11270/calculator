#pragma once
#include <SFML\Graphics.hpp>

class button
{
private:
	sf::RectangleShape butt;
	sf::Text label;
public:
	button(sf::Vector2f(size), sf::Vector2f(pos), sf::Color color, std::string buttonLabel, int sizeOfText, sf::Font *font);
	button();
	void create(sf::Vector2f(size), sf::Vector2f(pos), sf::Color color, std::string buttonLabel, int sizeOfText, sf::Font *font);
	sf::Vector2f getCoords();
	sf::Vector2f getSize();
	void drawTo(sf::RenderWindow *window);
	bool isPressed(sf::Vector2f(points));
};
