#pragma once
#include "Cell.h" 

#define ROW 100
#define COLUMN 100

class Application {
public:	
	Application();
	~Application();
	
private:
	void Update();
	void Render();	
	Cell grid[ROW][COLUMN];
	
};
