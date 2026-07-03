#include <stdint.h>
#include "headers/framebuffer.h"
// do input, make terminal, do draw_line from url: https://chatgpt.com/c/6a47e8c0-e044-83ee-82a6-262f531feb96
void kernel_main(uint32_t magic, void* mb_addr){ 
  get_framebuffer_access(magic, mb_addr);
  clear_screen(0xFF000000);
  print_string(200, 200, "Hello world!", 0xFFFFFFFF);
  while(1);
}
