#include <raylib.h>

#include "asteroid.h"

#define NEARBLACK                                                              \
  CLITERAL(Color) { 15, 15, 15, 255 }

#define MAX_ASTEROIDS 64
AsteroidSize _asteroidSizes[] = {ASTEROID_SMALL, ASTEROID_MEDIUM,
                                 ASTEROID_LARGE};
Asteroid _asteroids[MAX_ASTEROIDS] = {0};

void Init(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Asteroids");

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
    _asteroids[i] = CreateAsteroid(_asteroidSizes[GetRandomValue(0, 2)],
                                   GetMousePosition(), (Vector2){200, 0});
    created = true;
    break;
  }

  if (!created) {
    TraceLog(LOG_ERROR, "Can't create more asteroids");
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
