#ifndef SENSO_H
#define SENSO_H

/**
 * @brief Green LED GPIO-Pin
 */
#define LED_GREEN 18
/**
 * @brief Blue LED GPIO-Pin
 */
#define LED_BLUE 21
/**
 * @brief Yellow LED GPIO-Pin
 */
#define LED_YELLOW 0
/**
 * @brief RED LED GPIO-Pin
 */
#define LED_RED 3
/**
 * @brief Green button GPIO-Pin
 */
#define BUTTON_GREEN 19
/**
 * @brief Blue button GPIO-Pin
 */
#define BUTTON_BLUE 20
/**
 * @brief Yellow button GPIO-Pin
 */
#define BUTTON_YELLOW 1
/**
 * @brief Red button GPIO-Pin
 */
#define BUTTON_RED 2

#define REG(P) (*(volatile uint32_t *)(P))
#define GPIO_BASE 0x10012000
#define GPIO_INPUT_EN 0x4
#define GPIO_OUTPUT_EN 0x8
#define GPIO_OUTPUT_VAL 0xc
#define GPIO_IOF_EN 0x38
#define GPIO_PULLUP_EN 0x10

/**
 * @brief Value representing 1 millisecond for loop delay.
 *
 * Based on experimentation.
 */
#define MILLI 270

/**
 * @brief Short time.
 *
 * Has to be at least 500ms.
 */
#define T_SHORT 500
/**
 * @brief Long time.
 *
 * Twice as long as T_SHORT.
 */
#define T_LONG 2 * T_SHORT
/**
 * @brief Very long time
 *
 * Twice as long as T_LONG.
 */
#define T_VERY_LONG 2 * T_LONG

/**
 * @brief Maximum level of the game.
 */
#define MAX_LEVEL 10

/**
 * @brief Multiplier for reducing input time limit.
 */
#define T_MULTIPLIER 0.9f

/**
 * @brief All game states.
 */
typedef enum
{
  STATE_INIT = 0,
  STATE_STANDBY = 1,
  STATE_DEMONSTARTION = 2,
  STATE_IMITATION = 3,
  STATE_LOST = 4,
  STATE_TRANSITION = 5,
  STATE_END = 6,
} state;
#endif
