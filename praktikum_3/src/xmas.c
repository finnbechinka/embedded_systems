/**
 * @file xmas.c
 * @author Finn Bechinka (finn.bechinka@hsbi.de)
 * @brief xmas stuff.
 * @version 0
 * @date 20.12.2023
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "xmas.h"
#include "song.h"

/* void x()
{

 NOT WORK, sad >:(
	volatile uint32_t *out = (volatile uint32_t *)(GPIO_BASE + GPIO_OUTPUT_VAL);
	volatile uint32_t op1 = (1U << LED_STRIPE);
	volatile uint32_t op2 = ~(1U << LED_STRIPE);

	asm volatile("or x0, x0, x1\n"
							 : "=m"(out)
							 : "r"(op1));
	asm volatile("nop\n");
	asm volatile("nop\n");
	asm volatile("nop\n");
	asm volatile("nop\n");
	asm volatile("nop\n");
	asm volatile("nop\n");
	asm volatile("nop\n");
	asm volatile("nop\n");
	asm volatile("nop\n");
	asm volatile("nop\n");
	asm volatile("and x0, x0, x1\n"
							 : "=m"(out)
							 : "r"(op2));
} */

#define SEND_BIT1                                          \
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1U << LED_STRIPE);  \
	asm("nop\n");                                            \
	asm("nop\n");                                            \
	asm("nop\n");                                            \
	asm("nop\n");                                            \
	asm("nop\n");                                            \
	asm("nop\n");                                            \
	asm("nop\n");                                            \
	asm("nop\n");                                            \
	asm("nop\n");                                            \
	asm("nop\n");                                            \
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1U << LED_STRIPE); \
	asm("nop\n");                                            \
	asm("nop\n");

#define SEND_BIT0                                          \
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1U << LED_STRIPE);  \
	asm("nop\n");                                            \
	asm("nop\n");                                            \
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1U << LED_STRIPE); \
	asm("nop\n");                                            \
	asm("nop\n");                                            \
	asm("nop\n");                                            \
	asm("nop\n");                                            \
	asm("nop\n");                                            \
	asm("nop\n");                                            \
	asm("nop\n");                                            \
	asm("nop\n");                                            \
	asm("nop\n");                                            \
	asm("nop\n");

#define SEND_BYTE1 SEND_BIT1 SEND_BIT1 SEND_BIT1 SEND_BIT1 SEND_BIT1 SEND_BIT1 SEND_BIT1 SEND_BIT1

#define SEND_BYTE0 SEND_BIT0 SEND_BIT0 SEND_BIT0 SEND_BIT0 SEND_BIT0 SEND_BIT0 SEND_BIT0 SEND_BIT0

void send_color(Colors color)
{
	switch (color)
	{
	case RED:
		SEND_BYTE0;
		SEND_BYTE1;
		SEND_BYTE0;
		break;
	case GREEN:
		SEND_BYTE1;
		SEND_BYTE0;
		SEND_BYTE0;
		break;
	case YELLOW:
		SEND_BYTE1;
		SEND_BYTE1;
		SEND_BYTE0;
		break;
	default:
		break;
	}
}

void sleep(double ms)
{
	const uint64_t *mtime = (uint64_t *)(CLINT_CTRL_ADDR + CLINT_MTIME);
	volatile double stop = (double)*mtime + (ms * (30000.0 / 1000.0));
	while (*mtime < (uint64_t)stop)
	{
	}
}

void init(void)
{
	// Set LED_STRIPE and P_BUZZER to output.
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= (1U << LED_STRIPE);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) |= (1U << P_BUZZER);
}

void advance_stripe(int n)
{
	for (int i = 0; i < 10; i++)
	{
		send_color(color_sequence[(i + n) % 10]);
	}
}

void play(void)
{
	for (uint32_t i = 0U; i < 48U; i++)
	{
		float ms = (duration[i] * 1000.0);
		int note = song[i];

		// double period = (1.0 / note);
		// double half_period = (period / 2.0);
		// double periods = period * note;

		advance_stripe((int)i);

		// for (int i = 0; i < periods; i++)
		// {
		// 	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1U << P_BUZZER);
		// 	sleep(half_period);
		// 	REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1U << P_BUZZER);
		// 	sleep(half_period);
		// }

		const uint64_t *mtime = (uint64_t *)(CLINT_CTRL_ADDR + CLINT_MTIME);
		volatile double stop = (double)*mtime + (ms * (30000.0 / 1000.0));
		double duration = (double)((1000 / (note * 2.0)) * 12U);

		while (*mtime < stop)
		{
			REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1U << P_BUZZER);
			sleep(duration);
			REG(GPIO_BASE + GPIO_OUTPUT_VAL) |= (1U << P_BUZZER);
			sleep(duration);
		}
	}
}

int main(void)
{
	init();

	sleep(5000);
	for (;;)
	{
		play();
		sleep(2000);
	}

	return 0;
}
