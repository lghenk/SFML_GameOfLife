#pragma once
#include <SFML/Graphics.hpp>

class Cell {
public:
	Cell();
	~Cell();

	void Toggle();
	bool IsAlive();
	void setAlive(bool isItAlive);

	sf::RectangleShape rectangle;
	sf::Vector2f arrayPos;

	bool tempAlive;
	
private:
	bool alive;
};

