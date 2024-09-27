#include <raylib.h>
#include <raymath.h>

#include "asteroid.h"

#define NEARBLACK                                                              \
  CLITERAL(Color) { 15, 15, 15, 255 }

#define SCREEN_SIZE CLITERAL(Vector2) {800, 450}
#define SCREEN_CENTER Vector2Scale(SCREEN_SIZE, 0.5f)

#define MAX_ASTEROIDS 64
AsteroidSize _asteroidSizes[] = {ASTEROID_SMALL, ASTEROID_MEDIUM,
                                 ASTEROID_LARGE};
Asteroid _asteroids[MAX_ASTEROIDS] = {0};

void Init(void) {

  InitWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, "Asteroids");

  SetTargetFPS(60);
}

void Update(void) {
  for (int i = 0; i < MAX_ASTEROIDS; i++) {
    UpdateAsteroid(_asteroids + i, GetFrameTime());
  }
}

void Draw(void) {
  BeginDrawing();

  ClearBackground(NEARBLACK);

  for (int i = 0; i < MAX_ASTEROIDS; i++) {
    DrawAsteroid(&_asteroids[i]);
  }

  EndDrawing();
}

void AddAsteroid(void) {
  bool created = false;
  for (int i = 0; i < MAX_ASTEROIDS; i++) {
    if (_asteroids[i].active) {
      continue;
    }

    Vector2 position = GetMousePosition();
    Vector2 velocity = GetRandomAsteroidVelocity(position, SCREEN_CENTER);
    AsteroidSize size = GetRandomAsteroidSize();

    _asteroids[i] = CreateAsteroid(size, position, velocity);
    created = true;
    break;
  }

  if (!created) {
    TraceLog(LOG_ERROR, "Can't create more asteroids!");
  }
}

int main(void) {
  Init();

  while (!WindowShouldClose()) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      AddAsteroid();
    }
    Update();
    Draw();
  }

  CloseWindow();

  return 0;
}
