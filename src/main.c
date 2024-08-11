#include <raylib.h>

#include "asteroid.h"

#define NEARBLACK                                                              \
  CLITERAL(Color) { 15, 15, 15, 255 }

#define MAX_ASTEROIDS 64
Asteroid _asteroids[MAX_ASTEROIDS] = {0};

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

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      Asteroid asteroid =
          CreateAsteroid(ASTEROID_SMALL, GetMousePosition(), (Vector2){200, 0});
      for (int i = 0; i < MAX_ASTEROIDS; i++) {
        if (_asteroids[i].active) {
          continue;
        }
        _asteroids[i] = asteroid;
        break;
      }
    }
    Update();
    Draw();
  }

  CloseWindow();

  return 0;
}
