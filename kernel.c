#include <stdint.h>
#include "headers/framebuffer.h"
void kernel_main(uint32_t magic, void* mb_addr){
  get_framebuffer_access(magic, mb_addr);
  clear_screen(0xFF0000FF);

  while(1);
}
