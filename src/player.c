#include "player.h"
#include "trace.h"
#include "window.h"
#include <raylib.h>
#include <raymath.h>

#define PLAYER_ROTATION_SPEED 240
#define PLAYER_INIT_ROTATION 30

Player PlayerSpawn(void) {
  return (Player){
      .position = WINDOW_CENTER,
      .speed = 0,
      .rotation = 0,
  };
}

void PlayerUpdate(Player *player, float delta) {
  if (IsKeyDown(KEY_LEFT)) {
    player->rotation -= PLAYER_ROTATION_SPEED * delta;
  } else if (IsKeyDown(KEY_RIGHT)) {
    player->rotation += PLAYER_ROTATION_SPEED * delta;
  }
  player->rotation = fmod(player->rotation, 360);

  if (IsKeyDown(KEY_UP)) {
    float nextSpeed = player->speed + 10 * delta;
    if (nextSpeed < 10) {
      player->speed = nextSpeed;
    } else {
      player->speed = 10;
    }
  } else if (IsKeyDown(KEY_DOWN)) {
    float nextSpeed = player->speed - 10 * delta;
    if (nextSpeed > 0) {
      player->speed = nextSpeed;
    } else {
      player->speed = 0;
    }
  }
  player->position =
      Vector2Add(player->position, Vector2Rotate((Vector2){player->speed, 0},
                                                 player->rotation * DEG2RAD));
}

void PlayerDrawTrace(Player player) {
  Vector2 direction = Vector2Scale(
      Vector2Rotate((Vector2){player.speed, 0}, player.rotation * DEG2RAD), 10);
  direction = Vector2Add(player.position, direction);
  DrawLineV(player.position, direction, BLUE);
}

void PlayerDraw(Player player) {
  if (TraceIsEnabled()) {
    PlayerDrawTrace(player);
  }
  DrawPolyLines(player.position, 3, 32, player.rotation, WHITE);
}
