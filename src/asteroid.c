#include "asteroid.h"

#include <raylib.h>
#include <raymath.h>

#define ASTEROID_ROTATION_SPEED_MIN 5
#define ASTEROID_ROTATION_SPEED_MAX 240

#define ASTEROID_MIN_SPEED 100
#define ASTEROID_MAX_SPEED 300
#define ASTEROID_ANGLE_OFFSET 30

Asteroid AsteroidSpawn(Vector2 position, Vector2 target) {
  Vector2 direction = Vector2Normalize(Vector2Subtract(target, position));
  Vector2 velocity = Vector2Scale(
      direction, GetRandomValue(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED));
  Vector2 offsetVelocity = Vector2Rotate(
      velocity,
      GetRandomValue(-ASTEROID_ANGLE_OFFSET, ASTEROID_ANGLE_OFFSET) * DEG2RAD);

  return (Asteroid){
      .active = true,
      .size = (AsteroidSize)GetRandomValue(1, 3),
      .start = position,
      .position = position,
      .rotation = GetRandomValue(0, 360),
      .velocity = offsetVelocity,
      .rotationSpeed = GetRandomValue(ASTEROID_ROTATION_SPEED_MIN,
                                      ASTEROID_ROTATION_SPEED_MAX),
  };
}

void AsteroidUpdate(Asteroid *asteroid, float deltaTime, Vector2 screenSize) {
  if (!asteroid->active) {
    return;
  }

  asteroid->position = Vector2Add(asteroid->position,
                                  Vector2Scale(asteroid->velocity, deltaTime));
  asteroid->rotation += asteroid->rotationSpeed * deltaTime;

  int size = (int)asteroid->size * 16;
  if (asteroid->position.x + size < 0)
    asteroid->active = false;
  else if (asteroid->position.x - size > screenSize.x)
    asteroid->active = false;
  else if (asteroid->position.y + size < 0)
    asteroid->active = false;
  else if (asteroid->position.y - size > screenSize.y)
    asteroid->active = false;
}

void AsteroidDraw(Asteroid asteroid) {
  if (!asteroid.active) {
    return;
  }
  DrawPolyLines(asteroid.position, 3, 16 * (int)asteroid.size,
                asteroid.rotation, WHITE);
}

void AsteroidDrawTracing(Asteroid asteroid) {
  if (!asteroid.active) {
    return;
  }

  Vector2 finalTarget =
      Vector2Add(asteroid.position, Vector2Scale(asteroid.velocity, 10.0f));
  DrawLineV(asteroid.start, finalTarget, GREEN);

  Vector2 target = Vector2Add(asteroid.position, asteroid.velocity);
  DrawLineV(asteroid.position, target, RED);
}
