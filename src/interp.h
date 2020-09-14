#ifndef INCLUDED_INTERP_H
#define INCLUDED_INTERP_H

#include "source.h"

typedef struct Interp Interp;

Interp* CreateInterp(void);
void DestroyInterp(Interp* interp);

int ExecuteScript(Interp* interp, Source* scriptSource);

#endif  // INCLUDED_INTERP_H
