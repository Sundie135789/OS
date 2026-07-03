#include "headers/framebuffer.h"
#include "headers/multiboot.h"
#include "headers/font.h"
#include <stdint.h>
uint32_t* framebuffer = 0;
uint32_t fb_width = 0, fb_height = 0,fb_pitch = 0;
void get_framebuffer_access(uint32_t magic, void* mb_addr){
  (void) magic;
  struct multiboot_tag* tag = (struct multiboot_tag*)((uint8_t*)mb_addr+8);
  while(tag->type != 0){
    if(tag->type == 8){
      struct multiboot_tag_framebuffer *fb = (void*) tag;
      framebuffer = (uint32_t*)(uint64_t)fb->addr;
      fb_width = fb->width;
      fb_height = fb->height;
      fb_pitch = fb->pitch;
      break;
    }
    tag = (struct multiboot_tag*)((uint8_t*)tag + ((tag->size + 7) & ~7));
  }
}

void put_pixel(uint32_t x, uint32_t y, uint32_t color){
  framebuffer[y * (fb_pitch / 4) + x] = color;
}
void clear_screen(uint32_t color){
  for(uint32_t y = 0; y < fb_height;y++){
    for(uint32_t x = 0;x < fb_width;x++){
      framebuffer[y * (fb_pitch/4) + x] = color;
    }
  }
}
void draw_filled_rectangle(int x, int y, int w, int h, uint32_t color){
  for(int j = 0;j < h;j++){
    for(int i = 0;i < w;i++){
      put_pixel(x + i, y + j, color);
    }
  }
}
// Text
void put_char(int x,int y,char c,uint32_t color){
  for(int row = 0;row<8;row++){
    uint8_t line = font[(uint8_t)c][row];
    for(int col =0;col<8;col++){
      if(line & (1 << (7 - col))){
        put_pixel(x + col, y + row, color);
      }
    }
  }
}
void print_string(int x,int y, char* str, uint32_t color){
  int original_x = x;
  for(int i=0; str[i] != '\0'; i++){
    if(str[i] == '\n' || x + FONT_WIDTH > fb_width){
      y += LINE_SPACING + 8;
      x = original_x;
      continue;
    }
    put_char(x, y, str[i], color);
    x += CHAR_SPACING + 8;
  }
}
void draw_line(int x0, int y0, int x1, int y1, uint32_t color){
  //TODO
}
