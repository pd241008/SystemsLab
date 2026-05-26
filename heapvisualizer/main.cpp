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

struct BlockHeader {
  size_t size;
  bool is_free;
  BlockHeader *next;
};
BlockHeader *global_head = nullptr;

void *my_malloc(std::size_t size) {
  size_t total_size = sizeof(BlockHeader) + size;

  BlockHeader *current = global_head;
  while (current != nullptr) {

    if (current->is_free == true && current->size >= size) {

      current->is_free = false;

      return (void *)(current + 1);
    }
    current = current->next;
  }

  if (heap_top + total_size > sizeof(heap)) {
    return NULL; // Out of memory
  }

  BlockHeader *header = (BlockHeader *)&heap[heap_top];
  header->size = size;
  header->is_free = false;
  header->next = nullptr;

  if (global_head == nullptr) {
    global_head = header;
  } else {

    BlockHeader *tail = global_head;
    while (tail->next != nullptr) {
      tail = tail->next;
    }
    tail->next = header;
  }

  heap_top += total_size;

  return (void *)(header + 1);
}

void custom_reset() {
  heap_top = std::size_t(NULL);
  std::memset(heap, 0, sizeof(heap));
}

void traversal(BlockHeader *head) {

  BlockHeader *current = head;

  while (current != nullptr) {

    std::cout << "Block size: " << current->size
              << " | Is free: " << (current->is_free ? "Yes" : "No")
              << std::endl;

    current = current->next;
  }
}
int raylibvisualizer() {
  InitWindow(WIDTH, HEIGHT, "Heap Visualizer");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

  
    BlockHeader *current = global_head;
    int current_x = 30;

    while (current != nullptr) {


      int block_width =
          (int)(((sizeof(BlockHeader) + current->size) / 4096.0f) *
                (WIDTH - 60));


      if (current->is_free == false) {
        DrawRectangle(current_x, 30, block_width, 40, GREEN);
      } else {
        DrawRectangle(current_x, 30, block_width, 40, GRAY);
      }

     
      current_x += block_width;

   
      current = current->next;
    }

    int remaining_width = (WIDTH - 30) - current_x;

    if (remaining_width > 0) {
   
      DrawRectangle(current_x, 30, remaining_width, 40, DARKGRAY);
    }

    EndDrawing();
  }
  CloseWindow();
  return 0;
}
int main(int argc, char *argv[]) {
  int size;
  std::cout << "Give a Number for Size Allocation Under 4KB: " << std::endl;
  std::cin >> size;

  void *ptr = my_malloc(size);
  if (ptr == NULL) {
    std::cout << "Allocation failed" << std::endl;
    return 1;
  }
  traversal(global_head);
  std::cout << "Successfully allocated " << size << " bytes." << std::endl;
  std::cout << "Total heap consumed: " << used_memory() << " bytes."
            << std::endl;

  raylibvisualizer();
  return 0;
}
