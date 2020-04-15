#ifndef user_input_h
#define user_input_h

#include "tools/actions.h"
#include "tools/kbhit.h"

//TODO: misschien niet last?
int lastKeyPressed();
Action getAction(int key);

#endif
