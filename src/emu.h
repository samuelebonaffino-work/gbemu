#ifndef EMU_H
#define EMU_H

#include "common.h"

typedef struct
{
    bool paused;
    bool running;
    u64_t ticks;
} emu_ctx_t;

int emu_run(int argc, char** argv);

#endif // EMU_H
