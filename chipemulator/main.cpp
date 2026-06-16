#include <cstdint>
#include <fstream>
#include <iostream>
#include <cstdlib>
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

  pc = Start_Address;
  I = 0;
  sp = 0;
  delay_timer = 0;
  sound_timer = 0;

  for (int i = 0; i < 4096; i++) {
    memory[i] = 0;
  }

  for (int i = 0; i < 16; i++) {
    V[i] = 0;
    stack[i] = 0;
    keypad[i] = false;
  }

  for (int i = 0; i < 64 * 32; i++) {
    display[i] = 0;
  }

  for (unsigned int i = 0; i < FONTSET_SIZE; i++) {
    memory[0x050 + i] = fontset[i];
  }
}

void load_rom(const char *filename) {

  std::ifstream file(filename, std::ios::binary | std::ios::ate);

  if (file.is_open()) {
    std::streampos size = file.tellg();
    
    if (size > (4096 - Start_Address)) {
      std::cerr << "Error: ROM file is too large to fit in memory." << std::endl;
      return;
    }

    char *buffer = new char[size];

    file.seekg(0, std::ios::beg);
    file.read(buffer, size);
    file.close();

    for (long i = 0; i < size; i++) {
      memory[Start_Address + i] = buffer[i];
    }

    delete[] (buffer);
  } else {
    std::cerr << "Error: Failed to open ROM file: " << filename << std::endl;
  }
}

void fetch_decode_execute() {
  uint16_t opcode = (memory[pc] << 8) | memory[pc + 1];
  pc += 2;

 
  uint8_t X = (opcode & 0x0F00) >> 8;
  uint8_t Y = (opcode & 0x00F0) >> 4;
  uint8_t N = opcode & 0x000F;
  uint8_t NN = opcode & 0x00FF;
  uint16_t NNN = opcode & 0x0FFF;

  switch (opcode & 0xF000) {
    case 0x0000:
      switch (opcode) {
        case 0x00E0: // CLS
          for (int i = 0; i < 64 * 32; i++) {
            display[i] = 0;
          }
          break;
        case 0x00EE: // RET
          sp--;
          pc = stack[sp];
          break;
        default:
          std::cerr << "Unknown opcode: " << std::hex << opcode << std::endl;
          break;
      }
      break;
    case 0x1000: // JP addr
      pc = NNN;
      break;
    case 0x2000: // CALL addr
      stack[sp] = pc;
      sp++;
      pc = NNN;
      break;
    case 0x3000: // SE Vx, byte
      if (V[X] == NN) pc += 2;
      break;
    case 0x4000: // SNE Vx, byte
      if (V[X] != NN) pc += 2;
      break;
    case 0x5000: // SE Vx, Vy
      if (V[X] == V[Y]) pc += 2;
      break;
    case 0x6000: // LD Vx, byte
      V[X] = NN;
      break;
    case 0x7000: // ADD Vx, byte
      V[X] += NN;
      break;
    case 0x8000:
      switch (N) {
        case 0x0: V[X] = V[Y]; break;
        case 0x1: V[X] |= V[Y]; break;
        case 0x2: V[X] &= V[Y]; break;
        case 0x3: V[X] ^= V[Y]; break;
        case 0x4: {
          uint16_t sum = V[X] + V[Y];
          V[X] = sum & 0xFF;
          V[0xF] = (sum > 0xFF) ? 1 : 0;
          break;
        }
        case 0x5: {
          uint8_t vX = V[X];
          uint8_t vY = V[Y];
          V[X] = vX - vY;
          V[0xF] = (vX >= vY) ? 1 : 0;
          break;
        }
        case 0x6: { // SHR Vx {, Vy}
          uint8_t vX = V[X];
          V[X] = vX >> 1;
          V[0xF] = vX & 0x1;
          break;
        }
        case 0x7: { // SUBN Vx, Vy
          uint8_t vX = V[X];
          uint8_t vY = V[Y];
          V[X] = vY - vX;
          V[0xF] = (vY >= vX) ? 1 : 0;
          break;
        }
        case 0xE: { // SHL Vx {, Vy}
          uint8_t vX = V[X];
          V[X] = vX << 1;
          V[0xF] = (vX & 0x80) >> 7;
          break;
        }
        default:
          std::cerr << "Unknown opcode: " << std::hex << opcode << std::endl;
          break;
      }
      break;
    case 0x9000: // SNE Vx, Vy
      if (V[X] != V[Y]) pc += 2;
      break;
    case 0xA000: // LD I, addr
      I = NNN;
      break;
    case 0xB000: // JP V0, addr
      pc = NNN + V[0];
      break;
    case 0xC000: // RND Vx, byte
      V[X] = (rand() % 256) & NN;
      break;
    case 0xD000: { // DRW Vx, Vy, nibble
      uint8_t xPos = V[X] % 64;
      uint8_t yPos = V[Y] % 32;
      V[0xF] = 0;
      for (int row = 0; row < N; row++) {
        uint8_t spriteByte = memory[I + row];
        for (int col = 0; col < 8; col++) {
          uint8_t spritePixel = spriteByte & (0x80 >> col);
          if (spritePixel) {
            int displayIdx = ((yPos + row) % 32) * 64 + ((xPos + col) % 64);
            if (display[displayIdx] == 1) {
              V[0xF] = 1;
            }
            display[displayIdx] ^= 1;
          }
        }
      }
      break;
    }
    case 0xE000:
      switch (NN) {
        case 0x9E: // SKP Vx
          if (keypad[V[X]]) pc += 2;
          break;
        case 0xA1: // SKNP Vx
          if (!keypad[V[X]]) pc += 2;
          break;
        default:
          std::cerr << "Unknown opcode: " << std::hex << opcode << std::endl;
          break;
      }
      break;
    case 0xF000:
      switch (NN) {
        case 0x07: // LD Vx, DT
          V[X] = delay_timer;
          break;
        case 0x0A: { // LD Vx, K
          bool keyPress = false;
          for (int i = 0; i < 16; i++) {
            if (keypad[i]) {
              V[X] = i;
              keyPress = true;
              break;
            }
          }
          if (!keyPress) {
            pc -= 2; // Block execution
          }
          break;
        }
        case 0x15: // LD DT, Vx
          delay_timer = V[X];
          break;
        case 0x18: // LD ST, Vx
          sound_timer = V[X];
          break;
        case 0x1E: // ADD I, Vx
          I += V[X];
          break;
        case 0x29: // LD F, Vx
          I = V[X] * 5 + 0x050; // Fonts start at 0x050
          break;
        case 0x33: // LD B, Vx
          memory[I] = V[X] / 100;
          memory[I + 1] = (V[X] / 10) % 10;
          memory[I + 2] = V[X] % 10;
          break;
        case 0x55: // LD [I], Vx
          for (int i = 0; i <= X; i++) {
            memory[I + i] = V[i];
          }
          break;
        case 0x65: // LD Vx, [I]
          for (int i = 0; i <= X; i++) {
            V[i] = memory[I + i];
          }
          break;
        default:
          std::cerr << "Unknown opcode: " << std::hex << opcode << std::endl;
          break;
      }
      break;
    default:
      std::cerr << "Unknown opcode: " << std::hex << opcode << std::endl;
      break;
  }
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
