#ifndef ASTEROID_H_
#define ASTEROID_H_

#include "raylib.h"

typedef enum AsteroidSize {
  ASTEROID_SMALL = 1,
  ASTEROID_MEDIUM = 2,
  ASTEROID_LARGE = 3
} AsteroidSize;

typedef enum AsteroidState {
  ASTEROID_CEASED = 0,
  ASTEROID_SPAWNED = 1,
  ASTEROID_ACTIVE = 2,
} AsteroidState;

typedef enum AsteroidSpawnDirection {
  ASTEROID_SPAWN_UP = 1,
  ASTEROID_SPAWN_DOWN = 2,
  ASTEROID_SPAWN_LEFT = 3,
  ASTEROID_SPAWN_RIGHT = 4
} AsteroidSpawnDirection;

typedef struct Asteroid {
  AsteroidState state;
  AsteroidSize size;
  Vector2 start;
  Vector2 position;
  float rotation;
  float rotationSpeed;
  Vector2 velocity;
} Asteroid;

Asteroid AsteroidSpawn(Vector2 position, Vector2 target);
void AsteroidUpdate(Asteroid *asteroid, float deltaTime, Vector2 screenSize);
void AsteroidDraw(Asteroid asteroid);
void AsteroidDrawTracing(Asteroid asteroid);
#endif
