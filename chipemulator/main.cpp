#include <cstdint>
#include <fstream>
#include <iostream>
#include <raylib.h>

#define SCALE 10
#define WIDTH (64 * SCALE)
#define HEIGHT (32 * SCALE)

// CHIP-8 State
uint8_t memory[4096];
uint8_t V[16];
uint16_t I;
uint16_t pc;
uint16_t stack[16];
uint16_t sp;
uint8_t delay_timer;
uint8_t sound_timer;
uint8_t display[64 * 32];
bool keypad[16];

const unsigned int Start_Address = 0x200;

void initialize() {

const unsigned int FONTSET_SIZE = 80;

uint8_t fontset[FONTSET_SIZE] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, 
	0x20, 0x60, 0x20, 0x20, 0x70, 
	0xF0, 0x10, 0xF0, 0x80, 0xF0, 
	0xF0, 0x10, 0xF0, 0x10, 0xF0, 
	0x90, 0x90, 0xF0, 0x10, 0x10, 
	0xF0, 0x80, 0xF0, 0x10, 0xF0, 
	0xF0, 0x80, 0xF0, 0x90, 0xF0, 
	0xF0, 0x10, 0x20, 0x40, 0x40, 
	0xF0, 0x90, 0xF0, 0x90, 0xF0, 
	0xF0, 0x90, 0xF0, 0x10, 0xF0, 
	0xF0, 0x90, 0xF0, 0x90, 0x90, 
	0xE0, 0x90, 0xE0, 0x90, 0xE0, 
	0xF0, 0x80, 0x80, 0x80, 0xF0, 
	0xE0, 0x90, 0x90, 0x90, 0xE0, 
	0xF0, 0x80, 0xF0, 0x80, 0xF0, 
	0xF0, 0x80, 0xF0, 0x80, 0x80  
};
}

void load_rom(const char *filename) {

  std::ifstream file(filename, std::ios::binary | std::ios::ate);

  if (file.is_open()) {
    std::streampos size = file.tellg();
    char *buffer = new char[size];

    file.seekg(0, std::ios::beg);
    file.read(buffer, size);
    file.close();

    for (long i = 0; i < size; i++) {
      memory[Start_Address + i] = buffer[i];
    }

    delete[] (buffer);
  }
  // TODO: Open ROM file
  // TODO: Read file contents into memory starting at address 0x200
}

void fetch_decode_execute() {
  // TODO: Fetch opcode (2 bytes at pc)
  // TODO: Decode opcode into nibbles
  // TODO: Execute opcode
}

int raylibvisualizer() {
  InitWindow(WIDTH, HEIGHT, "CHIP-8 Emulator");
  SetTargetFPS(60);

  initialize();

  // TODO: Remove hardcoded behavior later, load ROM path from args
  // load_rom("rom.ch8");

  while (!WindowShouldClose()) {
    // TODO: Handle input for keypad (map keys to CHIP-8 0-F keys)

    // TODO: Emulate a cycle (call fetch_decode_execute)
    // Note: You may need to call it multiple times per frame for proper clock
    // speed

    // TODO: Update timers (decrement delay_timer and sound_timer at 60Hz)

    BeginDrawing();
    ClearBackground(BLACK);

    // TODO: Render the 64x32 display array using DrawRectangle for each ON
    // pixel

    EndDrawing();
  }

  CloseWindow();
  return 0;
}

int main(int argc, char *argv[]) {
  // TODO: Parse command-line arguments to pass ROM file path to load_rom
  raylibvisualizer();
  return 0;
}
