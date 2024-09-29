#ifndef ASTEROID_H_
#define ASTEROID_H_

#include "raylib.h"

typedef enum AsteroidSize {
  ASTEROID_SMALL = 1,
  ASTEROID_MEDIUM = 2,
  ASTEROID_LARGE = 3
} AsteroidSize;

AsteroidSize GetRandomAsteroidSize(void);

typedef struct Asteroid {
  bool active;
  AsteroidSize size;
  Vector2 position;
  float rotation;
  float rotationSpeed;
  Vector2 velocity;
} Asteroid;

Asteroid CreateAsteroid(AsteroidSize size, Vector2 position, Vector2 velocity);
void UpdateAsteroid(Asteroid *asteroid, float deltaTime, Vector2 screenSize);
void DrawAsteroid(Asteroid asteroid);

Vector2 GetRandomAsteroidVelocity(Vector2 position, Vector2 target);

#endif
