#ifndef PLAYER_H_
#define PLAYER_H_

#include "raylib.h"

typedef struct Player {
  Vector2 position;
  float rotation;
  float speed;
  Vector2 acceleration;
  Vector2 velocity;
} Player;

Player PlayerSpawn(void);
void PlayerUpdate(Player *player, float delta);
void PlayerDraw(Player player);

#endif
