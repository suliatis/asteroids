#include "asteroids.h"

#include "asteroid.h"
#include "trace.h"
#include <raygui.h>
#include <raylib.h>
#include <stdio.h>
#include <string.h>

#define MAX_ASTEROIDS 64

Asteroid asteroids[MAX_ASTEROIDS] = {0};

void AsteroidsUpdate(void) {
  // Add ~2 new asteroids in every second
  // TODO Loop fusion?
  if (GetRandomValue(1, 30) == 1) {
    bool created = false;
    for (int i = 0; i < MAX_ASTEROIDS; i++) {
      if (asteroids[i].state != ASTEROID_INACTIVE) {
        continue;
      }

      asteroids[i] = AsteroidSpawn();
      created = true;
      break;
    }

    if (!created) {
      TraceLog(LOG_ERROR, "Can't create more asteroids!");
    }
  }

  for (int i = 0; i < MAX_ASTEROIDS; i++) {
    AsteroidUpdate(asteroids + i, GetFrameTime());
  }
}

int _CountActive(void) {
  int count = 0;
  for (int i = 0; i < MAX_ASTEROIDS; i++) {
    if (asteroids[i].state == ASTEROID_INACTIVE) {
      continue;
    }
    count++;
  }
  return count;
}

void _DrawCounter_TraceUI(void) {
  const char *text = TextFormat("ASTEROIDS: %d", _CountActive());
  GuiLabel((Rectangle){10, 10, 100, 20}, text);
}

void AsteroidsDraw(void) {
  if (TraceIsEnabled()) {
    _DrawCounter_TraceUI();
  }

  for (int i = 0; i < MAX_ASTEROIDS; i++) {
    if (TraceIsEnabled()) {
      AsteroidDrawTracing(asteroids[i]);
    }
    AsteroidDraw(asteroids[i]);
  }
}
