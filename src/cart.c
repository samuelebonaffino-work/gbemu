#include "cart.h"

typedef struct cart_ctx
{
  char filename[1024];
  u32_t rom_size;
  u8_t* rom_data;
  rom_header_t* header;
} cart_ctx_t;

static cart_ctx_t ctx;

static const char* ROM_TYPES[] =
{
  "ROM ONLY",
  "MBC1",
  "MBC1+RAM",
  "MBC1+RAM+BATTERY",
  "0x04 - UNDEFINED",
  "MBC2",
  "MBC2+BATTERY",
  "0x07 - UNDEFINED",
  "ROM+RAM 1",
  "ROM+RAM+BATTERY 1",
  "0x0A - UNDEFINED",
  "MMM01",
  "MMM01+RAM",
  "MMM01+RAM+BATTERY",
  "0x0E - UNDEFINED",
  "MBC3+TIMER+BATTERY",
  "MBC3+TIMER+RAM+BATTERY 2",
  "MBC3",
  "MBC3+RAM 2",
  "MBC3+RAM+BATTERY 2",
  "0x14 - UNDEFINED",
  "0x15 - UNDEFINED",
  "0x16 - UNDEFINED",
  "0x17 - UNDEFINED",
  "0x18 - UNDEFINED",
  "MBC5",
  "MBC5+RAM",
  "MBC5+RAM+BATTERY",
  "MBC5+RUMBLE",
  "MBC5+RUMBLE+RAM",
  "MBC5+RUMBLE+RAM+BATTERY",
  "0x1F - UNDEFINED",
  "MBC6",
  "0x21 - UNDEFINED",
  "MBC7+SENSOR+RUMBLE+RAM+BATTERY",
};

static const char* LIC_CODE[0xA5] = 
{
  [0x00] = "None",
  [0x01] = "Nintendo R&D1",
  [0x08] = "Capcom",
  [0x13] = "Electronic Arts",
  [0x18] = "Hudson Soft",
  [0x19] = "b-ai",
  [0x20] = "kss",
  [0x22] = "pow",
  [0x24] = "PCM Complete",
  [0x25] = "san-x",
  [0x28] = "Kemco Japan",
  [0x29] = "seta",
  [0x30] = "Viacom",
  [0x31] = "Nintendo",
  [0x32] = "Bandai",
  [0x33] = "Ocean/Acclaim",
  [0x34] = "Konami",
  [0x35] = "Hector",
  [0x37] = "Taito",
  [0x38] = "Hudson",
  [0x39] = "Banpresto",
  [0x41] = "Ubi Soft",
  [0x42] = "Atlus",
  [0x44] = "Malibu",
  [0x46] = "angel",
  [0x47] = "Bullet-Proof",
  [0x49] = "irem",
  [0x50] = "Absolute",
  [0x51] = "Acclaim",
  [0x52] = "Activision",
  [0x53] = "American sammy",
  [0x54] = "Konami",
  [0x55] = "Hi tech entertainment",
  [0x56] = "LJN",
  [0x57] = "Matchbox",
  [0x58] = "Mattel",
  [0x59] = "Milton Bradley",
  [0x60] = "Titus",
  [0x61] = "Virgin",
  [0x64] = "LucasArts",
  [0x67] = "Ocean",
  [0x69] = "Electronic Arts",
  [0x70] = "Infogrames",
  [0x71] = "Interplay",
  [0x72] = "Broderbund",
  [0x73] = "sculptured",
  [0x75] = "sci",
  [0x78] = "THQ",
  [0x79] = "Accolade",
  [0x80] = "misawa",
  [0x83] = "lozc",
  [0x86] = "Tokuma Shoten Intermedia",
  [0x87] = "Tsukuda Original",
  [0x91] = "Chunsoft",
  [0x92] = "Video system",
  [0x93] = "Ocean/Acclaim",
  [0x95] = "Varie",
  [0x96] = "Yonezawa/s'pal",
  [0x97] = "Kaneko",
  [0x99] = "Pack in soft",
  [0xA4] = "Konami (Yu-Gi-Oh!)"
};

const char* cart_type_name()
{
  return (ctx.header->type <= 0x22) ? ROM_TYPES[ctx.header->type] : "UKNOWN";
}

const char* cart_lic_name()
{
  return (ctx.header->type <= 0xA4) ? LIC_CODE[ctx.header->lic_code] : "UKNOWN";
}

const bool cart_test_checksum()
{
  u16_t x = 0;
  for(u16_t i = 0x0134; i <= 0x014C; i++)
  {
    x -= ctx.rom_data[i] - 1;
  }

  return (x & 0xFF) ? true : false;
}

bool cart_load(char* cart_name)
{
  snprintf(ctx.filename, sizeof(ctx.filename), "%s", cart_name);

  FILE* fp = fopen(cart_name, "r");
  if(!fp)
  {
    print_err("cart.c", "cart_load", "failed to open the specified file: %s.\n", cart_name);
    return false;
  }
  print_msg("cart.c", "cart.load", "Opened: %s\n", ctx.filename);

  fseek(fp, 0, SEEK_END);
  ctx.rom_size = ftell(fp);
  ctx.rom_data = malloc(ctx.rom_size);
  rewind(fp);
  fread(ctx.rom_data, ctx.rom_size, 1, fp);
  fclose(fp);

  ctx.header = (rom_header_t*) (ctx.rom_data + 0x100);
  ctx.header->title[15] = 0;

  print_msg("cart.c", "cart_load", "Loaded cartridge:\n");
  print_msg("cart.c", "cart_load", "  - Title    : %s\n", ctx.header->title);
  print_msg("cart.c", "cart_load", "  - Type     : %2.2X (%s)\n", ctx.header->type, cart_type_name());
  print_msg("cart.c", "cart_load", "  - ROM size : %d\n", ctx.header->rom_size);
  print_msg("cart.c", "cart_load", "  - RAM size : %2.2X\n", ctx.header->ram_size);
  print_msg("cart.c", "cart_load", "  - LIC code : %2.2X\n", ctx.header->lic_code, cart_lic_name());
  print_msg("cart.c", "cart_load", "  - ROM vers : %2.2X\n", ctx.header->version);
  print_msg("cart.c", "cart_load", "  - Checksum : %2.2X (%s)\n", ctx.header->checksum, cart_test_checksum() ? "PASSED" : "FAILED");

  return true;
}

u8_t cart_read(u16_t address)
{

}

void cart_write(u16_t address, u8_t value)
{
  
}