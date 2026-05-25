#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <raylib.h>

#define HEIGHT 900
#define WIDTH 600

uint8_t heap[4096];
size_t heap_top = 0;

size_t used_memory() { return heap_top; }
size_t free_memory() { return sizeof(heap) - heap_top; }
void *my_malloc(std::size_t size) {

  if (heap_top + size > sizeof(heap)) {
    return NULL;
  }

  void *ptr = &heap[heap_top];
  heap_top += size;

  return ptr;
}

void custom_reset() {
  heap_top = 0;
  std::memset(heap, 0, sizeof(heap));
}

int raylibvisualizer() {

  InitWindow(WIDTH, HEIGHT, "Heap");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    // Scale to window width
    int allocated_w = (int)((heap_top / 4096.0f) * (WIDTH - 60));
    int free_w = (WIDTH - 60) - allocated_w;

    DrawRectangle(30, 30, allocated_w, 40, GREEN);
    DrawRectangle(30 + allocated_w, 30, free_w, 40, GRAY);
    EndDrawing();
  }
  CloseWindow();

  return 0;
}

int main(int argc, char *argv[]) {
  int size;
  std::cout << "Give a Number for Size Allocation Under 4KB" << std::endl;
  std::cin >> size;

  void *ptr = my_malloc(size);
  if (ptr == NULL) {
    std::cout << "Allocation failed" << std::endl;
    return 1;
  }

  raylibvisualizer();
  return 0;
}
