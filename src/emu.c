#include "emu.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "cart.h"
#include "cpu.h"

#include <stdio.h>

// Emulator components:
// - Cartridge>
// - CPU>
// - Bus>
// - PPU>
// - Timer>

static emu_ctx_t ctx;

void delay(u32_t ms)
{
  SDL_Delay(ms);
}

emu_ctx_t* emu_get_ctx()
{
  return &ctx;
}

int emu_run(int argc, char** argv)
{
  if(argc < 2)
  {
    print_err("emu.c", "emu_run", "need to specify a ROM file to be loaded.\n");
    return -1;
  }

  if(!cart_load(argv[1]))
  {
    print_err("emu.c", "emu_run", "failed to load ROM file: %s.\n", argv[1]);
    return -2;
  }

  print_msg("emu.c", "emu_run", "Cartridge loaded...\n");

  SDL_Init(SDL_INIT_VIDEO);
  print_msg("emu.c", "emu_run", "SDL init\n");
  TTF_Init();
  print_msg("emu.c", "emu_run", "TTF init\n");

  cpu_init();

  ctx.running = true;
  ctx.paused = false;
  ctx.ticks = 0;

  while(ctx.running)
  {
    if(ctx.paused)
    {
      delay(10);
      continue;
    }

    if(!cpu_step())
    {
      print_err("emu.c", "emu_run", "CPU stopped\n");
      return -3;
    }

    ctx.ticks++;
  }

  return 0;
}