#include "Cell.h"
#include "raymath.h"

Vector3 yellow = Vector3(255, 255, 0);
Vector3 red = Vector3(255, 0, 0);

Cell::Cell(int screenWidth, int screenHeight)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    //spawn cell on edge of circle
    cellPosition = RandomPointOnCircleEdge(this->screenWidth / 2, this->screenHeight / 2, 100);

    randomSpeedScaler = GetRandomValue(20, 35); //randomize speed
    randomDirection = Vector2(GetRandomValue(-10, 10), GetRandomValue(-10, 10)); //randomize direction
}

void Cell::Update(float deltaTime)
{
    //move cell in random direction
    cellPosition.x += randomDirection.x * randomSpeedScaler * deltaTime;
    cellPosition.y += randomDirection.y * randomSpeedScaler * deltaTime;

    //cell position out of bounds checks
    bool outOfBoundsA = cellPosition.x > screenWidth || cellPosition.y > screenHeight;
    bool outOfBoundsB = cellPosition.x < 0 || cellPosition.y < 0;
   
    if (outOfBoundsA || outOfBoundsB) //deactivate cell when not visible anymore
        active = false;
}

void Cell::Draw()
{
    // Lerp between yellow and red based on the distance to the center of the screenx
    float distanceToCenter = Vector2Distance(cellPosition, Vector2(screenWidth / 2, screenHeight / 2));
    Vector3 color = Vector3Lerp(yellow, red, Remap(distanceToCenter, 0, screenWidth / 1.4f, 0, 1));
    
    DrawPixelV(cellPosition, Color(color.x, color.y, color.z, 255)); //draw cell at current position
}

//Returns a random point the edge of an imaginary circle
Vector2 Cell::RandomPointOnCircleEdge(float xCenter, float yCenter, float radius) {
    float angle = static_cast<float>(GetRandomValue(0, 360)) * DEG2RAD; // Convert degrees to radians

    float x = radius * cosf(angle) + xCenter;
    float y = radius * sinf(angle) + yCenter;

    return Vector2(x, y);
}