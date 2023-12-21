#ifndef XMAS_H
#define XMAS_H

typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

#define REG(P) (*(volatile uint32_t *)(P))
#define GPIO_BASE 0x10012000
#define GPIO_INPUT_EN 0x4
#define GPIO_OUTPUT_EN 0x8
#define GPIO_OUTPUT_VAL 0xc
#define GPIO_IOF_EN 0x38
#define GPIO_PULLUP_EN 0x10
#define CLINT_CTRL_ADDR 0x02000000
#define CLINT_MTIME 0xbff8
#define CLINT_MTIMECMP 0x4000

#define LED_STRIPE 9U
#define P_BUZZER 11U

typedef enum
{
  RED,
  GREEN,
  YELLOW,
} Colors;

// No clue why misra complains about this.
// Dont see why 8.4 should apply here.
// Nothing I tried worked.
Colors color_sequence[] = {RED, GREEN, YELLOW, RED, GREEN, YELLOW, RED, GREEN, YELLOW, RED};

#endif
