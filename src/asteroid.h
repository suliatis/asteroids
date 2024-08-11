#ifndef ASTEROID_H_
#define ASTEROID_H_

#include "raylib.h"

typedef enum AsteroidSize {
  SMALL = 1,
  MEDIUM = 2,
  LARGE = 3
} AsteroidSize;

typedef struct Asteroid {
  bool active;
  AsteroidSize size;
  Vector2 position;
  float rotation;
  float rotationSpeed;
  Vector2 velocity;
} Asteroid;

Asteroid CreateAsteroid(AsteroidSize size, Vector2 position, Vector2 velocity);
void UpdateAsteroid(Asteroid* asteroid, float deltaTime);
#endif
