#include "trace.h"
#include "raygui.h"
#include "window.h"

bool enabled = false;

void _DrawTraceToggleButton() {
  Vector2 size = {120, 20};
  Vector2 padding = {10, 10};
  Vector2 position = {WINDOW_SIZE.x - size.x - padding.x,
                      WINDOW_SIZE.y - size.y - padding.y};
  char* text = "Tracing: Toggle ON";
  if (enabled) {
    text = "Tracing: Toggle OFF";
  }

  if (GuiButton((Rectangle){position.x, position.y, size.x, size.y}, text)) {
    TraceToggle();
  }
}

void TraceDraw() {
  _DrawTraceToggleButton();
}

bool TraceToggle() {
  enabled = !enabled;
  return enabled;
}

bool TraceIsEnabled() { return enabled; }

bool TraceIsDisabled() { return !enabled; }
