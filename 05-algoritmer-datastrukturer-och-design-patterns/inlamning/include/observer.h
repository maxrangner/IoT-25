#ifndef OBSERVER_H
#define OBSERVER_H
#include "Context.h"
#include "Event.h"

typedef void(*Observer)(Context* ctx, Event event);
void notify(Context* ctx, Event event);

#endif