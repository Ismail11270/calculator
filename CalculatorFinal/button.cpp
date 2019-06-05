#include "button.h"



button::button(sf::Vector2f(size), sf::Vector2f(pos), sf::Color color, std::string buttonLabel, int sizeOfText, sf::Font *font)
{
	create(size, pos, color, buttonLabel, sizeOfText, font);
}
void button::create(sf::Vector2f(size), sf::Vector2f(pos), sf::Color color, std::string buttonLabel, int sizeOfText, sf::Font *font)
{
	this->butt.setSize(size);
	this->butt.setFillColor(color);
	this->butt.setPosition(pos);
	this->label.setFont(*font);
	this->label.setFillColor(sf::Color::Red);
	this->label.setCharacterSize(sizeOfText);
	this->label.setString(buttonLabel);
	this->label.setPosition({ (pos.x + (size.x / 2) - sizeof(buttonLabel) - 20), (pos.y + (size.y / 2) - sizeOfText / 2) });
}
void button::drawTo(sf::RenderWindow *window) {
	window->draw(this->butt);
	window->draw(label);
}

sf::Vector2f button::getCoords() {
	return this->butt.getPosition();
}

sf::Vector2f button::getSize() {
	return this->butt.getSize();
}

bool button::isPressed(sf::Vector2f(points)) {
	return this->butt.getGlobalBounds().contains(points);
}

button::button()
{

}
