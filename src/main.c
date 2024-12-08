#include "asteroids.h"
#include "player.h"
#include "trace.h"
#include "window.h"
#include <raylib.h>
#include <raymath.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define NEARBLACK CLITERAL(Color){15, 15, 15, 255}

Player player;

void Init(void) {

  InitWindow(WINDOW_SIZE.x, WINDOW_SIZE.y, "Asteroids");

  SetTargetFPS(60);

  player = PlayerSpawn();
}

void Update(void) { 
  PlayerUpdate(&player, GetFrameTime());
  AsteroidsUpdate();
}

void Draw(void) {
  BeginDrawing();

  ClearBackground(NEARBLACK);
  if (TraceIsEnabled()) {
    DrawCircleV(WINDOW_CENTER, 5, RED);
  }

  PlayerDraw(player);
  AsteroidsDraw();
  TraceDraw();

  EndDrawing();
}

int main(void) {
  Init();

  while (!WindowShouldClose()) {
    Update();
    Draw();
  }

  CloseWindow();

  return 0;
}
