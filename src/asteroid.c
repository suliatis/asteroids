#include "asteroid.h"

#include <raylib.h>
#include <raymath.h>

#include "window.h"

#define ASTEROID_ROTATION_SPEED_MIN 5
#define ASTEROID_ROTATION_SPEED_MAX 240

#define ASTEROID_MIN_SPEED 100
#define ASTEROID_MAX_SPEED 300
#define ASTEROID_ANGLE_OFFSET 30

Asteroid AsteroidSpawn() {
  AsteroidSpawnDirection spawnDirection =
      (AsteroidSpawnDirection)(GetRandomValue(1, 4));
  Vector2 position = {-128, -128};
  if (spawnDirection == ASTEROID_SPAWN_UP) {
    position.x = GetRandomValue(0, 800);
  }
  if (spawnDirection == ASTEROID_SPAWN_DOWN) {
    position.x = GetRandomValue(0, 800);
    position.y = 480 + 128;
  }
  if (spawnDirection == ASTEROID_SPAWN_LEFT) {
    position.y = GetRandomValue(0, 480);
  }
  if (spawnDirection == ASTEROID_SPAWN_RIGHT) {
    position.x = 800 + 128;
    position.y = GetRandomValue(0, 480);
  }

  Vector2 direction = Vector2Normalize(Vector2Subtract(WINDOW_CENTER, position));
  Vector2 velocity = Vector2Scale(
      direction, GetRandomValue(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED));
  Vector2 offsetVelocity = Vector2Rotate(
      velocity,
      GetRandomValue(-ASTEROID_ANGLE_OFFSET, ASTEROID_ANGLE_OFFSET) * DEG2RAD);

  return (Asteroid){
      .state = ASTEROID_SPAWNED,
      .size = (AsteroidSize)GetRandomValue(1, 3),
      .start = position,
      .position = position,
      .rotation = GetRandomValue(0, 360),
      .velocity = offsetVelocity,
      .rotationSpeed = GetRandomValue(ASTEROID_ROTATION_SPEED_MIN,
                                      ASTEROID_ROTATION_SPEED_MAX),
  };
}

void AsteroidUpdate(Asteroid *asteroid, float deltaTime) {
  if (asteroid->state == ASTEROID_CEASED) {
    return;
  }

  asteroid->position = Vector2Add(asteroid->position,
                                  Vector2Scale(asteroid->velocity, deltaTime));
  asteroid->rotation += asteroid->rotationSpeed * deltaTime;

  if (asteroid->state == ASTEROID_ACTIVE) {
    if (asteroid->position.x < -128 || asteroid->position.x > WINDOW_SIZE.x + 128 ||
        asteroid->position.y < -128 || asteroid->position.y > WINDOW_SIZE.y + 128) {
      asteroid->state = ASTEROID_CEASED;
    }
  } else {
    if (asteroid->position.x > 0 && asteroid->position.x < WINDOW_SIZE.x &&
        asteroid->position.y > 0 && asteroid->position.y < WINDOW_SIZE.y) {
      asteroid->state = ASTEROID_ACTIVE;
    }
  }
}

void AsteroidDraw(Asteroid asteroid) {
  if (asteroid.state == ASTEROID_CEASED) {
    return;
  }
  DrawPolyLines(asteroid.position, 3, 16 * (int)asteroid.size,
                asteroid.rotation, WHITE);
}

void AsteroidDrawTracing(Asteroid asteroid) {
  if (asteroid.state == ASTEROID_CEASED) {
    return;
  }

  Vector2 finalTarget =
      Vector2Add(asteroid.position, Vector2Scale(asteroid.velocity, 10.0f));
  DrawLineV(asteroid.start, finalTarget, GREEN);

  Vector2 target = Vector2Add(asteroid.position, asteroid.velocity);
  DrawLineV(asteroid.position, target, RED);
}
