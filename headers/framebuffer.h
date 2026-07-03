#pragma once

#include <stdint.h>
void get_framebuffer_access(uint32_t magic, void* mb_addr);
extern uint32_t* framebuffer;
extern uint32_t width;
extern uint32_t height;
extern uint32_t pitch;

// Graphics functions
void put_pixel(uint32_t x, uint32_t y, uint32_t color);
void clear_screen(uint32_t color);
void draw_filled_rectangle(int x,int y, int width, int height, uint32_t color);
void put_char(int x,int y,char c, uint32_t color);
void print_string(int x,int y,char* str, uint32_t color);
void draw_line(int x0, int y0, int x1, int y1, uint32_t color);
