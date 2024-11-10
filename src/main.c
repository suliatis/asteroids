#include <raylib.h>
#include <raymath.h>

#include "window.h"
#include "asteroid.h"

#define NEARBLACK                                                              \
  CLITERAL(Color) { 15, 15, 15, 255 }

#define MAX_ASTEROIDS 64
Asteroid _asteroids[MAX_ASTEROIDS] = {0};
int _recentAsteroidIndex = -1;
bool _isInDebugMode = true;

void Init(void) {

  InitWindow(WINDOW_SIZE.x, WINDOW_SIZE.y, "Asteroids");

  SetTargetFPS(60);
}

void AddAsteroid(void) {
  bool created = false;
  for (int i = 0; i < MAX_ASTEROIDS; i++) {
    if (_asteroids[i].state != ASTEROID_CEASED) {
      continue;
    }

    _asteroids[i] = AsteroidSpawn(GetMousePosition(), WINDOW_CENTER);
    _recentAsteroidIndex = i;
    created = true;
    break;
  }

  if (!created) {
    TraceLog(LOG_ERROR, "Can't create more asteroids!");
  }
}

void Update(void) {
  for (int i = 0; i < MAX_ASTEROIDS; i++) {
    AsteroidUpdate(_asteroids + i, GetFrameTime());
  }
}

void Draw(void) {
  BeginDrawing();

  ClearBackground(NEARBLACK);
  if (_isInDebugMode) {
    DrawCircleV(WINDOW_CENTER, 5, RED);
  }

  for (int i = 0; i < MAX_ASTEROIDS; i++) {
    if (_isInDebugMode) {
      AsteroidDrawTracing(_asteroids[i]);
    }
    AsteroidDraw(_asteroids[i]);
  }

  EndDrawing();
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
