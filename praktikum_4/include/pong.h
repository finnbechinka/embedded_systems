#ifndef PONG_H
#include "semphr.h"

#define REG(P) (*(volatile uint32_t *)(P))

#define GPIO_BASE 0x10012000
#define GPIO_FALL_IE 0x20
#define GPIO_RISE_IE 0x18
#define GPIO_RISE_IP 0x1c
#define PLIC_BASE 0x0C000000
#define PLIC_ENABLE 0x2000
#define PLIC_THRESH 0x200000
#define PLIC_CLAIM 0x200004

#define BTN_GREEN 18UL
#define BTN_BLUE 19UL
#define BTN_YELLOW 20UL
#define BTN_RED 21UL

#define PADDING 10
#define SEGMENT_LENGTH 5

typedef struct
{
  int x;
  int y;
} Point_t;

typedef struct
{
  int radius;
  Point_t pos;
  Point_t dir;
} Ball_t;

typedef struct
{
  int width;
  int height;
  int score;
  Point_t pos;
  Point_t old;
  int score_updated;
} Player_t;

extern void irq_handler(void);
extern void init_btn(int btn);
extern void init(void);
extern void task_update_ball(void *pvParameters);
extern void task_update_players(void *pvParameters);
extern void task_update_score(void *pvParameters);
extern void task_draw(void *pvParameters);
extern void set_pixel(uint8_t x, uint8_t y, uint8_t p);
extern void draw_line(Point_t p, int len, int is_horizontal, int on);
#endif
