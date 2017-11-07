#include "Cell.h"
#include <SFML/Graphics.hpp>

Cell::Cell() {
	rectangle.setPosition(sf::Vector2f(0, 0));
	rectangle.setSize(sf::Vector2f(10, 10));
	rectangle.setFillColor(sf::Color::Black);
}


Cell::~Cell() {

}

void Cell::setAlive(bool isItAlive) {
	alive = isItAlive;

	if (alive) {
		rectangle.setFillColor(sf::Color::White);
	} else {
		rectangle.setFillColor(sf::Color::Black);
	}
}

void Cell::Toggle() {
	alive = !alive;

	if (alive) {
		rectangle.setFillColor(sf::Color::White);
	} else {
		rectangle.setFillColor(sf::Color::Black);
	}
}

bool Cell::IsAlive() {
	return alive;
}
