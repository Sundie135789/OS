#include "headers/framebuffer.h"
#include <stdint.h>

struct multiboot_tag{
  uint32_t type;
  uint32_t size;
};
struct multiboot_tag_framebuffer{
  uint32_t type;
  uint32_t size;
  uint64_t addr;
  uint32_t pitch;
  uint32_t width;
  uint32_t height;
  uint8_t bpp;
  uint8_t type_attr;
  uint16_t reserved;
};
uint32_t* framebuffer = 0;
uint32_t width = 0, height = 0, pitch = 0;
void get_framebuffer_access(uint32_t magic, void* mb_addr){
  (void) magic;
  struct multiboot_tag* tag = (struct multiboot_tag*)((uint8_t*)mb_addr+8);
  while(tag->type != 0){
    if(tag->type == 8){
      struct multiboot_tag_framebuffer *fb = (void*) tag;
      framebuffer = (uint32_t*)(uint64_t)fb->addr;
      width = fb->width;
      height = fb->height;
      pitch = fb->pitch;
      break;
    }
    tag = (struct multiboot_tag*)((uint8_t*)tag + ((tag->size + 7) & ~7));
  }
}

void put_pixel(uint32_t x, uint32_t y, uint32_t color){
  framebuffer[y * (pitch / 4) + x] = color;
}
void clear_screen(uint32_t color){
  for(uint32_t y = 0; y < height;y++){
    for(uint32_t x = 0;x < width;x++){
      framebuffer[y * (pitch/4) + x] = color;
    }
  }
}
void draw_line(int x0, int x1, int y0, int y1, uint32_t color){
  // TODO bresenhams
}
