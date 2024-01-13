#pragma once
#include "raylib.h"

class Cell
{
public:
	Cell(int screenWidth, int screenHeight);
	
	void Update(float deltaTime);
	void Draw();

	int screenWidth;
	int screenHeight;

	bool active = true;

private:
	Vector2 RandomPointOnCircleEdge(float xCenter, float yCenter, float radius);

	Vector2 cellPosition;
	Color cellColor;

	Vector2 randomDirection;
	int randomSpeedScaler;
};

