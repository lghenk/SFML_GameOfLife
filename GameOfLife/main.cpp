#include <iostream>
#include <SFML/Graphics.hpp>
#include "Cell.h"  
#include "Application.h"

#define ROW 50
#define COLUMN 50

using namespace std;

sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");

Cell grid[ROW][COLUMN];

bool leftPressed = false;
bool spacePressed = false;
bool returnPressed = false;
bool run = false;

void update();
void lateUpdate();

int CountAliveSurroundings(Cell cell) {
	sf::Vector2f pos = cell.arrayPos;
	int alive = 0;

	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (i == 0 && j == 0)
				continue;

			if (pos.x + i < 0 || pos.x + i > ROW || pos.y + j < 0 || pos.y + j > COLUMN)
				continue;

			Cell item = grid[(int)pos.x + i][(int)pos.y + j];

			if (item.IsAlive()) {
				alive++;
			}
		}
	}

	return alive;
}

void handleInput() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && leftPressed == false) {
		sf::Vector2i position = sf::Mouse::getPosition(window);
		cout << "X: " << to_string(position.x / 10) << " Y:" << to_string(position.y / 10) << endl;

		if (position.x / 10 >= 0 && position.x / 10 <= ROW && position.y / 10 >= 0 && position.y / 10 <= COLUMN) {
			grid[position.x / 10][position.y / 10].Toggle();
		}

		leftPressed = true;
	} else if (leftPressed == true && !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		leftPressed = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !spacePressed) {
		run = !run;
		spacePressed = true;
		cout << "Space Pressed" << endl;
	} else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && spacePressed) {
		spacePressed = false;
		cout << "Space Released" << endl;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !returnPressed) {
		update();
		lateUpdate();
		returnPressed = true;
		cout << "Enter Pressed" << endl;
	} else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && returnPressed) {
		returnPressed = false;
		cout << "Enter Released" << endl;
	}
}

void update() {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {
			int aliveFriends = CountAliveSurroundings(grid[i][j]);

			if (grid[i][j].IsAlive()) {
				if (aliveFriends == 2 || aliveFriends == 3) {
					grid[i][j].tempAlive = true;
				} else {
					grid[i][j].tempAlive = false;
				}
			} else {
				if (aliveFriends == 3) {
					grid[i][j].tempAlive = true;
				} else {
					grid[i][j].tempAlive = false;
				}
			}
		}
	}
}

void lateUpdate() {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {
			grid[i][j].setAlive(grid[i][j].tempAlive);
		}
	}
}

int main() {

	Application app;
	app.Run();

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {
			grid[i][j].arrayPos = sf::Vector2f(i, j);

			grid[i][j].rectangle.setSize(sf::Vector2f(10, 10));
			grid[i][j].rectangle.setPosition(sf::Vector2f(i * 10, j * 10));

			cout << to_string(i) << " " << to_string(j) << endl;
		}
	}



	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		handleInput();
		if (run) {
			handleInput();
			update();
			lateUpdate();
		}


		window.clear();
		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COLUMN; j++) {
				window.draw(grid[i][j].rectangle);
			}
		}
		window.display();
	}

	return 0;
}