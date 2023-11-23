/**
 * @file senso.c
 * @author Finn Bechinka (finn.bechinka@hsbi.de)
 * @brief Senso game.
 * @version 0
 * @date 2023-11-23
 *
 * @copyright Copyright (c) 2023
 *
 * I tried to implement MISRA C but I broke my code doing so.
 * Therefore I scapped it all again...
 */
#include "senso.h"
#include "mersenne_twister_800.h"
// #include <stdio.h>
// #include <wrap.h>

/**
 * @brief Current game-state, starting as init.
 */
state current_state = STATE_INIT;

/**
 * @brief Current level, starting with 1.
 */
int level = 1;
/**
 * @brief Current Amount of LEDs per session, starting with 3.
 */
int n = 3;
/**
 * @brief Time period where LED is on and time for input. Starting as T_LONG
 */
float t = T_LONG;

int led_sequence[13];

/**
 * @brief Resets level, n and t to start values.
 */
void reset(void)
{
	level = 1;
	n = 3;
	t = T_LONG;
}

/**
 * @brief Light up LED
 *
 * @param pin GPIO-Pin of LED
 */
void led_on(int pin)
{
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1 << pin);
}

/**
 * @brief Turn LED off.
 *
 * @param pin GPIO-Pin of LED
 */
void led_off(int pin)
{
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << pin);
}

/**
 * @brief Delay using for loop.
 *
 * @param ms Time to wait in milliseconds
 */
void delay(int ms)
{
	volatile uint32_t i = 0;
	for (i = 0; i < ms * MILLI; i++)
	{
	}
}

/**
 * @brief Initialize LED as output.
 *
 * @param pin GPIO-Pin of LED
 */
void init_led(int pin)
{
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1 << pin);
	REG(GPIO_BASE + GPIO_INPUT_EN) &= ~(1 << pin);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= 1 << pin;
}

/**
 * @brief Initialize Button as input.
 *
 * @param pin GPIO-Pin of Button
 */
void init_button(int pin)
{
	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1 << pin);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) &= ~(1 << pin);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << pin);
	REG(GPIO_BASE + GPIO_INPUT_EN) |= 1 << pin;
	REG(GPIO_BASE + GPIO_PULLUP_EN) |= 1 << pin;
}

/**
 * @brief Check for button press.
 *
 * Buttons are active low.
 *
 * @param pin GPIO-Pin of Button
 * @return 1 if pressed, 0 if not
 */
int is_pressed(int pin)
{
	int value = REG(GPIO_BASE) & (1 << pin);
	return (value == 0) ? 1 : 0;
}

/**
 * @brief Check activation of all buttons.
 *
 * @return GPIO-Pin of pressed button, -1 if none
 */
int button_pressed(void)
{
	if (is_pressed(BUTTON_GREEN) == 1)
	{
		return BUTTON_GREEN;
	}

	if (is_pressed(BUTTON_BLUE) == 1)
	{
		return BUTTON_BLUE;
	}

	if (is_pressed(BUTTON_YELLOW) == 1)
	{
		return BUTTON_YELLOW;
	}

	if (is_pressed(BUTTON_RED) == 1)
	{
		return BUTTON_RED;
	}

	return -1;
}

/**
 * @brief Light up LED, wait and turn off.
 *
 * @param pin GPIO-Pin of LED
 * @param ms Time to wait in milliseconds
 */
void led_blink(int pin, int ms)
{
	led_on(pin);
	delay(ms);
	led_off(pin);
}

/**
 * @brief Light up add LEDs, wait and turn off.
 *
 * Like led_blink but for all LEDs.
 *
 * @param ms Time to wait in milliseconds
 */
void leds_blink(int ms)
{
	led_on(LED_GREEN);
	led_on(LED_BLUE);
	led_on(LED_YELLOW);
	led_on(LED_RED);
	delay(ms);
	led_off(LED_GREEN);
	led_off(LED_BLUE);
	led_off(LED_YELLOW);
	led_off(LED_RED);
}

/**
 * @brief Choose random LED.
 *
 * @return GPIO-Pin of chosen LED, -1 on error
 */
int random_led(void)
{
	switch (TT800() % 4)
	{
	case 0:
		return LED_GREEN;
	case 1:
		return LED_BLUE;
	case 2:
		return LED_YELLOW;
	case 3:
		return LED_RED;
	default:
		return -1;
	}
}
/**
 * @brief Initialize GPIO-Pins.
 *
 * Defines LEDs and Buttons.
 * Following state is STATE_READY.
 */
void init_sequence(void)
{
	init_led(LED_GREEN);
	init_led(LED_BLUE);
	init_led(LED_YELLOW);
	init_led(LED_RED);
	init_button(BUTTON_GREEN);
	init_button(BUTTON_BLUE);
	init_button(BUTTON_YELLOW);
	init_button(BUTTON_RED);

	delay(T_VERY_LONG);

	current_state = STATE_STANDBY;
}

/**
 * @brief Standby, waiting for user input to start the game.
 *
 * Following state is STATE_IMITATION.
 */
void standby_sequence(void)
{
	// printf("\nStandby\n");
	// printf("\nPress green button to start\n");
	while (current_state == STATE_STANDBY)
	{
		led_on(LED_GREEN);
		volatile uint32_t i = 0;
		for (i = 0; i < (T_SHORT * MILLI) / 2; i++)
		{
			if (is_pressed(BUTTON_GREEN) == 1)
			{
				led_off(LED_GREEN);
				current_state = STATE_DEMONSTARTION;
				return;
			}
		}
		led_off(LED_GREEN);

		led_on(LED_BLUE);
		for (i = 0; i < (T_SHORT * MILLI) / 2; i++)
		{
			if (is_pressed(BUTTON_GREEN) == 1)
			{
				led_off(LED_BLUE);
				current_state = STATE_DEMONSTARTION;
				return;
			}
		}
		led_off(LED_BLUE);

		led_on(LED_YELLOW);
		for (i = 0; i < (T_SHORT * MILLI) / 2; i++)
		{
			if (is_pressed(BUTTON_GREEN) == 1)
			{
				led_off(LED_YELLOW);
				current_state = STATE_DEMONSTARTION;
				return;
			}
		}
		led_off(LED_YELLOW);

		led_on(LED_RED);
		for (i = 0; i < (T_SHORT * MILLI) / 2; i++)
		{
			if (is_pressed(BUTTON_GREEN) == 1)
			{
				led_off(LED_RED);
				current_state = STATE_DEMONSTARTION;
				return;
			}
		}
		led_off(LED_RED);
	}
}

/**
 * @brief Demonstation sequence.
 *
 * Following state is STATE_IMITATION
 */
void demonstration_sequence(void)
{
	// printf("\nDemonstration\n");
	led_on(LED_BLUE);
	led_on(LED_YELLOW);
	delay(T_SHORT);
	led_off(LED_BLUE);
	led_off(LED_YELLOW);
	delay(T_SHORT);

	volatile uint32_t i = 0;
	for (i = 0; i < n; i++)
	{
		int current_led = random_led();
		led_sequence[i] = current_led;
		led_blink(current_led, t);
		delay(T_SHORT);
	}
	leds_blink(T_SHORT);
	current_state = STATE_IMITATION;
}

/**
 * @brief Imitation sequence.
 *
 * !TODO Sometimes clicking right after the led is off after a correct guess
 * !the game counts it as a wrong guess.
 *
 *	Following state is STATE_TRANSITION or STATE_LOST.
 */
void imitation_sequence(void)
{
	// printf("\nImitation\n");
	volatile uint32_t i = 0;

	for (i = 0; i < n; i++)
	{
		int current_button;
		int current_led = led_sequence[i];

		switch (current_led)
		{
		case LED_GREEN:
			current_button = BUTTON_GREEN;
			break;
		case LED_BLUE:
			current_button = BUTTON_BLUE;
			break;
		case LED_YELLOW:
			current_button = BUTTON_YELLOW;
			break;
		case LED_RED:
			current_button = BUTTON_RED;
			break;
		default:
			break;
		}

		// printf("\nnext\n");

		int pressed_counter = 0;
		volatile int j = 0;
		// devide by 30 comes from experimentation
		for (j = 0; j < t * MILLI / 30; j++)
		{
			int pressed_button = button_pressed();
			if (pressed_button == -1)
			{
				continue;
			}

			pressed_counter++;
			if (pressed_button != current_button)
			{
				current_state = STATE_LOST;
				return;
			}
			led_blink(current_led, T_SHORT);
			break;
		}
		if (pressed_counter == 0 || pressed_counter > 1)
		{
			current_state = STATE_LOST;
			return;
		}
	}
	current_state = STATE_TRANSITION;
}

/**
 * @brief Lost sequence for lost game.
 *
 * Following state is STATE_STANDBY
 */
void lost_sequence(void)
{
	// printf("\nLost\n");
	volatile uint32_t i = 0;
	int reached = level - 1;
	for (i = 0; i < 2; i++)
	{
		led_on(LED_RED);
		led_on(LED_GREEN);
		delay(T_SHORT);
		led_off(LED_RED);
		led_off(LED_GREEN);
		delay(T_SHORT);
	}

	if ((reached & 8) != 0)
	{
		led_on(LED_GREEN);
	}
	if ((reached & 4) != 0)
	{
		led_on(LED_BLUE);
	}
	if ((reached & 2) != 0)
	{
		led_on(LED_YELLOW);
	}
	if ((reached & 1) != 0)
	{
		led_on(LED_RED);
	}

	delay(T_VERY_LONG);

	if ((reached & 8) != 0)
	{
		led_off(LED_GREEN);
	}
	if ((reached & 4) != 0)
	{
		led_off(LED_BLUE);
	}
	if ((reached & 2) != 0)
	{
		led_off(LED_YELLOW);
	}
	if ((reached & 1) != 0)
	{
		led_off(LED_RED);
	}

	reset();
	current_state = STATE_STANDBY;
}

/**
 * @brief Transition sequence between levels.
 *
 * Following state is STATE_DEMONSTRATION or STATE_END
 */
void transition_sequence(void)
{
	// printf("\ntransition\n");
	level++;
	n++;
	t = t * T_MULTIPLIER;

	volatile uint32_t i = 0;
	for (i = 0; i < 2; i++)
	{
		led_on(LED_GREEN);
		led_on(LED_YELLOW);
		delay(T_SHORT);
		led_off(LED_GREEN);
		led_off(LED_YELLOW);
		led_on(LED_BLUE);
		led_on(LED_RED);
		delay(T_SHORT);
		led_off(LED_BLUE);
		led_off(LED_RED);
	}

	if (level > MAX_LEVEL)
	{
		current_state = STATE_END;
		return;
	}
	current_state = STATE_DEMONSTARTION;
}

/**
 * @brief End sequence for game win.
 *
 * Following state is STATE_STANDBY
 */
void end_sequence(void)
{
	// printf("\nend\n");
	leds_blink(T_SHORT);
	delay(T_SHORT);
	leds_blink(T_LONG);
	delay(T_SHORT);
	leds_blink(T_SHORT);
	delay(T_SHORT);
	leds_blink(T_LONG);
	reset();
	current_state = STATE_STANDBY;
}

/**
 * @brief Main game loop.
 *
 * Calls sequences depending on state.
 *
 * @return 0 on exit success.
 */
int main(void)
{
	while (1)
	{
		switch (current_state)
		{
		case STATE_INIT:
			init_sequence();
			break;
		case STATE_STANDBY:
			standby_sequence();
			break;
		case STATE_DEMONSTARTION:
			demonstration_sequence();
			break;
		case STATE_IMITATION:
			imitation_sequence();
			break;
		case STATE_LOST:
			lost_sequence();
			break;
		case STATE_TRANSITION:
			transition_sequence();
			break;
		case STATE_END:
			end_sequence();
			break;
		default:
			break;
		}
	}
	return 0;
}
