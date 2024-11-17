#include "trace.h"

bool enabled = false;

bool TraceToggle() {
  enabled = !enabled;
  return enabled;
}

bool TraceIsEnabled() {
  return enabled;
}

bool TraceIsDisabled() {
  return !enabled;
}
