#include "asteroid.h"

#include <raylib.h>
#include <raymath.h>

#define ASTEROID_ROTATION_SPEED_MIN 5
#define ASTEROID_ROTATION_SPEED_MAX 240

Asteroid CreateAsteroid(AsteroidSize size, Vector2 position, Vector2 velocity) {
  return (Asteroid){
      .active = true,
      .size = size,
      .position = position,
      .rotation = GetRandomValue(0, 360),
      .velocity = velocity,
      .rotationSpeed = GetRandomValue(ASTEROID_ROTATION_SPEED_MIN,
                                      ASTEROID_ROTATION_SPEED_MAX),
  };
}

void UpdateAsteroid(Asteroid *asteroid, float deltaTime) {
  if (!asteroid->active) {
    return;
  }

  asteroid->position = Vector2Add(asteroid->position,
                                  Vector2Scale(asteroid->velocity, deltaTime));
  asteroid->rotation += asteroid->rotationSpeed * deltaTime;
  return *asteroid;
}
