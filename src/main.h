#ifndef MAIN_H
#define MAIN_H
#include <pebble.h>

// Global Stuff
#define COLORS       true
#define ANTIALIASING true

#define HAND_MARGIN  14
#define FINAL_RADIUS 68

#define ANIMATION_DURATION 400
#define ANIMATION_DELAY    500
  
const uint32_t KEY_CONFVER = 52668701; // int - configuration version ID
const uint32_t KEY_CONFDAT = 52668711; // data - configuration data

// Phone communication keys
#define KEY_COLOR_HH 1
#define KEY_COLOR_MH 2
#define KEY_COLOR_HM 3
#define KEY_COLOR_WB 4
#define KEY_COLOR_WO 5
#define KEY_COLOR_SB 6
#define KEY_DIGITIME 7

#define CURRENT_CONFVER 2 // MUST CHANGE THIS if struct below changes!
  
typedef struct {
  GColor color_hour_hand;
  GColor color_minute_hand;
  GColor color_hour_markers;
  GColor color_watchface_background;
  GColor color_watchface_outline;
  GColor color_surround_background;
  bool display_digital;
// } __attribute__((__packed__)) appConfig;  // if needed as config grows
} appConfig;

appConfig conf;

typedef struct {
  int hours;
  int minutes;
} Time;

#ifndef PBL_COLOR
void graphics_context_set_stroke_width(struct GContext *ctx, int width) {
  ;
}

// Draw line with width. From: http://forums.getpebble.com/discussion/comment/132110/#Comment_132110
// (Based on code found here http://rosettacode.org/wiki/Bitmap/Bresenham's_line_algorithm#C)
static void graphics_draw_line2(GContext *ctx, GPoint p0, GPoint p1, int8_t width) {
  // Order points so that lower x is first
  int16_t x0, x1, y0, y1;
  if (p0.x <= p1.x) {
    x0 = p0.x; x1 = p1.x; y0 = p0.y; y1 = p1.y;
  } else {
    x0 = p1.x; x1 = p0.x; y0 = p1.y; y1 = p0.y;
  }
    
  // Init loop variables
  int16_t dx = x1-x0;
  int16_t dy = abs(y1-y0);
  int16_t sy = y0<y1 ? 1 : -1; 
  int16_t err = (dx>dy ? dx : -dy)/2;
  int16_t e2;
  
  // Calculate whether line thickness will be added vertically or horizontally based on line angle
  int8_t xdiff, ydiff;
  
  if (dx > dy) {
    xdiff = 0;
    ydiff = width/2;
  } else {
    xdiff = width/2;
    ydiff = 0;
  }
    
  // Use Bresenham's integer algorithm, with slight modification for line width, to draw line at any angle
  while (true) {
    // Draw line thickness at each point by drawing another line 
    // (horizontally when > +/-45 degrees, vertically when <= +/-45 degrees)
    graphics_draw_line(ctx, GPoint(x0-xdiff, y0-ydiff), GPoint(x0+xdiff, y0+ydiff));
    
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0++; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}
#endif

#endif