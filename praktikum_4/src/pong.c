/**
 * @file pong.c
 * @author Finn Bechinka (finn.bechinka@hsbi.de)
 * @brief ping ponging
 * @version 0
 * @date 25.01.2024
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "FreeRTOS.h"
#include "task.h"
#include "startup.h"
#include "wrap.h"
#include "pong.h"
#include "display.h"
#include "font.h"
#include "framebuffer.h"

void draw_line(Point_t p, int len, int is_horizontal, int on)
{
	int i;
	if (is_horizontal == 0)
	{
		for (i = p.y; i <= (p.y + len); i++)
		{
			set_pixel(p.x, i, on);
		}
	}
	else
	{
		for (i = p.x; i <= (p.x + len); i++)
		{
			set_pixel(i, p.y, on);
		}
	}
}

void set_pixel(uint8_t x, uint8_t y, uint8_t p)
{
	xSemaphoreTake(xPixelMutex, portMAX_DELAY);
	fb_set_pixel(x, y, p);
	xSemaphoreGive(xPixelMutex);
}

void task_draw(void *pvParameters)
{
	for (;;)
	{
		// if (xSemaphoreTake(xInterruptSemaphore, pdMS_TO_TICKS(1)) == pdFALSE)
		// {
		// 	return;
		// }
		xSemaphoreTake(xDrawMutex, portMAX_DELAY);
		xSemaphoreTake(xPixelMutex, portMAX_DELAY);
		fb_flush();
		xSemaphoreGive(xPixelMutex);
		xSemaphoreGive(xDrawMutex);
		// xSemaphoreGive(xInterruptSemaphore);
		vTaskDelay(pdMS_TO_TICKS(20));
	}
}

void task_update_score(void *pvParameters)
{
	for (;;)
	{
		xSemaphoreTake(xDrawMutex, portMAX_DELAY);
		if (p_left.score_updated == 0)
		{
			int i;
			for (i = 0; i <= 6; i++)
			{
				int is_horizontal = i % 2;
				draw_line(p_left_score[i], SEGMENT_LENGTH, is_horizontal, 0);
			}
			switch (p_left.score % 10)
			{
			case 1:
				draw_line(p_left_score[2], SEGMENT_LENGTH, 0, 1);
				draw_line(p_left_score[6], SEGMENT_LENGTH, 0, 1);
				break;
			case 2:
				draw_line(p_left_score[1], SEGMENT_LENGTH, 1, 1);
				draw_line(p_left_score[2], SEGMENT_LENGTH, 0, 1);
				draw_line(p_left_score[3], SEGMENT_LENGTH, 1, 1);
				draw_line(p_left_score[4], SEGMENT_LENGTH, 0, 1);
				draw_line(p_left_score[5], SEGMENT_LENGTH, 1, 1);
				break;
			case 3:
				draw_line(p_left_score[1], SEGMENT_LENGTH, 1, 1);
				draw_line(p_left_score[2], SEGMENT_LENGTH, 0, 1);
				draw_line(p_left_score[3], SEGMENT_LENGTH, 1, 1);
				draw_line(p_left_score[5], SEGMENT_LENGTH, 1, 1);
				draw_line(p_left_score[6], SEGMENT_LENGTH, 0, 1);
				break;
			case 4:
				draw_line(p_left_score[0], SEGMENT_LENGTH, 0, 1);
				draw_line(p_left_score[2], SEGMENT_LENGTH, 0, 1);
				draw_line(p_left_score[3], SEGMENT_LENGTH, 1, 1);
				draw_line(p_left_score[6], SEGMENT_LENGTH, 0, 1);
				break;
			case 5:
				draw_line(p_left_score[0], SEGMENT_LENGTH, 0, 1);
				draw_line(p_left_score[1], SEGMENT_LENGTH, 1, 1);
				draw_line(p_left_score[3], SEGMENT_LENGTH, 1, 1);
				draw_line(p_left_score[5], SEGMENT_LENGTH, 1, 1);
				draw_line(p_left_score[6], SEGMENT_LENGTH, 0, 1);
				break;
			case 6:
				draw_line(p_left_score[0], SEGMENT_LENGTH, 0, 1);
				draw_line(p_left_score[1], SEGMENT_LENGTH, 1, 1);
				draw_line(p_left_score[3], SEGMENT_LENGTH, 1, 1);
				draw_line(p_left_score[4], SEGMENT_LENGTH, 0, 1);
				draw_line(p_left_score[5], SEGMENT_LENGTH, 1, 1);
				draw_line(p_left_score[6], SEGMENT_LENGTH, 0, 1);
				break;
			case 7:
				draw_line(p_left_score[1], SEGMENT_LENGTH, 1, 1);
				draw_line(p_left_score[2], SEGMENT_LENGTH, 0, 1);
				draw_line(p_left_score[6], SEGMENT_LENGTH, 0, 1);
				break;
			case 8:
				draw_line(p_left_score[0], SEGMENT_LENGTH, 0, 1);
				draw_line(p_left_score[1], SEGMENT_LENGTH, 1, 1);
				draw_line(p_left_score[2], SEGMENT_LENGTH, 0, 1);
				draw_line(p_left_score[3], SEGMENT_LENGTH, 1, 1);
				draw_line(p_left_score[4], SEGMENT_LENGTH, 0, 1);
				draw_line(p_left_score[5], SEGMENT_LENGTH, 1, 1);
				draw_line(p_left_score[6], SEGMENT_LENGTH, 0, 1);
				break;
			case 9:
				draw_line(p_left_score[0], SEGMENT_LENGTH, 0, 1);
				draw_line(p_left_score[1], SEGMENT_LENGTH, 1, 1);
				draw_line(p_left_score[2], SEGMENT_LENGTH, 0, 1);
				draw_line(p_left_score[3], SEGMENT_LENGTH, 1, 1);
				draw_line(p_left_score[5], SEGMENT_LENGTH, 1, 1);
				draw_line(p_left_score[6], SEGMENT_LENGTH, 0, 1);
				break;
			default:
				draw_line(p_left_score[0], SEGMENT_LENGTH, 0, 1);
				draw_line(p_left_score[1], SEGMENT_LENGTH, 1, 1);
				draw_line(p_left_score[2], SEGMENT_LENGTH, 0, 1);
				draw_line(p_left_score[4], SEGMENT_LENGTH, 0, 1);
				draw_line(p_left_score[5], SEGMENT_LENGTH, 1, 1);
				draw_line(p_left_score[6], SEGMENT_LENGTH, 0, 1);
				break;
			}
			p_left.score_updated = 1;
		}
		if (p_right.score_updated == 0)
		{
			int i;
			for (i = 0; i <= 6; i++)
			{
				int is_horizontal = i % 2;
				draw_line(p_right_score[i], SEGMENT_LENGTH, is_horizontal, 0);
			}
			switch (p_right.score % 10)
			{
			case 1:
				draw_line(p_right_score[2], SEGMENT_LENGTH, 0, 1);
				draw_line(p_right_score[6], SEGMENT_LENGTH, 0, 1);
				break;
			case 2:
				draw_line(p_right_score[1], SEGMENT_LENGTH, 1, 1);
				draw_line(p_right_score[2], SEGMENT_LENGTH, 0, 1);
				draw_line(p_right_score[3], SEGMENT_LENGTH, 1, 1);
				draw_line(p_right_score[4], SEGMENT_LENGTH, 0, 1);
				draw_line(p_right_score[5], SEGMENT_LENGTH, 1, 1);
				break;
			case 3:
				draw_line(p_right_score[1], SEGMENT_LENGTH, 1, 1);
				draw_line(p_right_score[2], SEGMENT_LENGTH, 0, 1);
				draw_line(p_right_score[3], SEGMENT_LENGTH, 1, 1);
				draw_line(p_right_score[5], SEGMENT_LENGTH, 1, 1);
				draw_line(p_right_score[6], SEGMENT_LENGTH, 0, 1);
				break;
			case 4:
				draw_line(p_right_score[0], SEGMENT_LENGTH, 0, 1);
				draw_line(p_right_score[2], SEGMENT_LENGTH, 0, 1);
				draw_line(p_right_score[3], SEGMENT_LENGTH, 1, 1);
				draw_line(p_right_score[6], SEGMENT_LENGTH, 0, 1);
				break;
			case 5:
				draw_line(p_right_score[0], SEGMENT_LENGTH, 0, 1);
				draw_line(p_right_score[1], SEGMENT_LENGTH, 1, 1);
				draw_line(p_right_score[3], SEGMENT_LENGTH, 1, 1);
				draw_line(p_right_score[5], SEGMENT_LENGTH, 1, 1);
				draw_line(p_right_score[6], SEGMENT_LENGTH, 0, 1);
				break;
			case 6:
				draw_line(p_right_score[0], SEGMENT_LENGTH, 0, 1);
				draw_line(p_right_score[1], SEGMENT_LENGTH, 1, 1);
				draw_line(p_right_score[3], SEGMENT_LENGTH, 1, 1);
				draw_line(p_right_score[4], SEGMENT_LENGTH, 0, 1);
				draw_line(p_right_score[5], SEGMENT_LENGTH, 1, 1);
				draw_line(p_right_score[6], SEGMENT_LENGTH, 0, 1);
				break;
			case 7:
				draw_line(p_right_score[1], SEGMENT_LENGTH, 1, 1);
				draw_line(p_right_score[2], SEGMENT_LENGTH, 0, 1);
				draw_line(p_right_score[6], SEGMENT_LENGTH, 0, 1);
				break;
			case 8:
				draw_line(p_right_score[0], SEGMENT_LENGTH, 0, 1);
				draw_line(p_right_score[1], SEGMENT_LENGTH, 1, 1);
				draw_line(p_right_score[2], SEGMENT_LENGTH, 0, 1);
				draw_line(p_right_score[3], SEGMENT_LENGTH, 1, 1);
				draw_line(p_right_score[4], SEGMENT_LENGTH, 0, 1);
				draw_line(p_right_score[5], SEGMENT_LENGTH, 1, 1);
				draw_line(p_right_score[6], SEGMENT_LENGTH, 0, 1);
				break;
			case 9:
				draw_line(p_right_score[0], SEGMENT_LENGTH, 0, 1);
				draw_line(p_right_score[1], SEGMENT_LENGTH, 1, 1);
				draw_line(p_right_score[2], SEGMENT_LENGTH, 0, 1);
				draw_line(p_right_score[3], SEGMENT_LENGTH, 1, 1);
				draw_line(p_right_score[5], SEGMENT_LENGTH, 1, 1);
				draw_line(p_right_score[6], SEGMENT_LENGTH, 0, 1);
				break;
			default:
				draw_line(p_right_score[0], SEGMENT_LENGTH, 0, 1);
				draw_line(p_right_score[1], SEGMENT_LENGTH, 1, 1);
				draw_line(p_right_score[2], SEGMENT_LENGTH, 0, 1);
				draw_line(p_right_score[4], SEGMENT_LENGTH, 0, 1);
				draw_line(p_right_score[5], SEGMENT_LENGTH, 1, 1);
				draw_line(p_right_score[6], SEGMENT_LENGTH, 0, 1);
				break;
			}
			p_right.score_updated = 1;
		}
		xSemaphoreGive(xDrawMutex);
	}
}

void task_update_ball(void *pvParameters)
{
	for (;;)
	{
		// if (xSemaphoreTake(xInterruptSemaphore, pdMS_TO_TICKS(1)) == pdFALSE)
		// {
		// 	continue;
		// }
		xSemaphoreTake(xDrawMutex, portMAX_DELAY);
		int x, y = 0;
		// remove old ball
		for (y = -ball.radius; y <= ball.radius; y++)
		{
			for (x = -ball.radius; x <= ball.radius; x++)
			{
				if (x * x + y * y <= ball.radius * ball.radius)
				{
					set_pixel(ball.pos.x + x, ball.pos.y + y, 0);
				}
			}
		}

		// check if ball is past top or bottom
		if (ball.pos.y + ball.radius >= DISP_H - PADDING)
		{
			ball.dir.y = -ball.dir.y;
		}
		if (ball.pos.y - ball.radius <= PADDING)
		{
			ball.dir.y = -ball.dir.y;
		}

		// check if ball is behing left player
		if (ball.pos.x < p_left.pos.x)
		{
			p_right.score++;
			p_right.score_updated = 0;
			ball.pos.x = DISP_W / 2;
			ball.pos.y = DISP_H / 2;
			ball.dir.y = 0;
			ball.dir.x = -1;
		}

		// check if ball is behing right player
		else if (ball.pos.x > p_right.pos.x + p_right.width)
		{
			p_left.score++;
			p_left.score_updated = 0;
			ball.pos.x = DISP_W / 2;
			ball.pos.y = DISP_H / 2;
			ball.dir.y = 0;
			ball.dir.x = 1;
		}
		// check for collisions
		else if (
				(ball.pos.x - ball.radius <= p_left.pos.x + p_left.width) &&
				(ball.pos.y + ball.radius >= p_left.pos.y - p_left.height / 2) &&
				(ball.pos.y - ball.radius <= p_left.pos.y + p_left.height / 2))
		{
			ball.dir.x = ball.pos.x - p_left.pos.x;
			ball.dir.y = ball.pos.y - p_left.pos.y;
		}
		else if (
				(ball.pos.x + ball.radius >= p_right.pos.x - p_right.width) &&
				(ball.pos.y + ball.radius >= p_right.pos.y - p_right.height / 2) &&
				(ball.pos.y - ball.radius <= p_right.pos.y + p_right.height / 2))
		{
			ball.dir.x = ball.pos.x - p_right.pos.x;
			ball.dir.y = ball.pos.y - p_right.pos.y;
		}
		ball.pos.x += ball.dir.x;
		ball.pos.y += ball.dir.y;

		// draw new ball
		for (y = -ball.radius; y <= ball.radius; y++)
		{
			for (x = -ball.radius; x <= ball.radius; x++)
			{
				if (x * x + y * y <= ball.radius * ball.radius)
				{
					set_pixel(ball.pos.x + x, ball.pos.y + y, 1);
				}
			}
		}
		// flush();
		xSemaphoreGive(xDrawMutex);
		// xSemaphoreGive(xInterruptSemaphore);
		// vTaskDelay(pdMS_TO_TICKS(50));
	}
}

void task_update_players(void *pvParameters)
{
	for (;;)
	{
		// if (xSemaphoreTake(xInterruptSemaphore, pdMS_TO_TICKS(1)) == pdFALSE)
		// {
		// 	continue;
		// }
		xSemaphoreTake(xDrawMutex, portMAX_DELAY);
		int x, y;

		for (y = -(p_left.height - 1) / 2; y <= (p_left.height - 1) / 2; y++)
		{
			for (x = 0; x <= p_left.width; x++)
			{
				set_pixel(p_left.old.x + x, p_left.old.y + y, 0);
			}
		}
		for (y = -(DISP_H - 1) / 2; y <= (p_right.height - 1) / 2; y++)
		{
			for (x = 0; x >= -p_right.width; x--)
			{
				set_pixel(p_right.old.x + x, p_right.old.y + y, 0);
			}
		}

		for (y = -(p_left.height - 1) / 2; y <= (p_left.height - 1) / 2; y++)
		{
			for (x = 0; x <= p_left.width; x++)
			{
				set_pixel(p_left.pos.x + x, p_left.pos.y + y, 1);
			}
		}
		for (y = -(p_right.height - 1) / 2; y <= (p_right.height - 1) / 2; y++)
		{
			for (x = 0; x >= -p_right.width; x--)
			{
				set_pixel(p_right.pos.x + x, p_right.pos.y + y, 1);
			}
		}

		p_left.old = p_left.pos;
		p_right.old = p_right.pos;
		// flush();
		xSemaphoreGive(xDrawMutex);
		// xSemaphoreGive(xInterruptSemaphore);
	}
}

void irq_handler(void)
{
	// if (xSemaphoreTake(xInterruptSemaphore, pdMS_TO_TICKS(25)) == pdFALSE)
	// {
	// 	return;
	// }
	uint32_t nb = REG(PLIC_BASE + PLIC_CLAIM);
	if (nb == (8 + BTN_GREEN))
	{
		p_left.pos.y -= 3;
		REG(GPIO_BASE + GPIO_RISE_IP) |= (1 << BTN_GREEN);
	}
	if (nb == (8 + BTN_RED))
	{
		p_right.pos.y -= 3;
		REG(GPIO_BASE + GPIO_RISE_IP) |= (1 << BTN_RED);
	}
	if (nb == (8 + BTN_BLUE))
	{
		p_left.pos.y += 3;
		REG(GPIO_BASE + GPIO_RISE_IP) |= (1 << BTN_BLUE);
	}
	if (nb == (8 + BTN_YELLOW))
	{
		p_right.pos.y += 3;
		REG(GPIO_BASE + GPIO_RISE_IP) |= (1 << BTN_YELLOW);
	}
	// flush();
	REG(PLIC_BASE + PLIC_CLAIM) = nb;
	// xSemaphoreGive(xInterruptSemaphore);
}

void init_btn(int btn)
{

	REG(GPIO_BASE + GPIO_IOF_EN) &= ~(1 << btn);
	REG(GPIO_BASE + GPIO_OUTPUT_EN) &= ~(1 << btn);
	REG(GPIO_BASE + GPIO_OUTPUT_VAL) &= ~(1 << btn);
	REG(GPIO_BASE + GPIO_INPUT_EN) |= (1 << btn);
	REG(GPIO_BASE + GPIO_PULLUP_EN) |= (1 << btn);
	REG(PLIC_BASE + PLIC_ENABLE) |= (1 << (8 + btn));
	REG(PLIC_BASE + 4 * (8 + btn)) = 1;
	asm volatile("csrw mtvec, %0" ::"r"(irq_handler));
	REG(GPIO_BASE + GPIO_RISE_IE) |= (1 << btn);
	REG(GPIO_BASE + GPIO_RISE_IP) |= (1 << btn);
}

void init(void)
{
	fb_init();
	oled_init();
	init_btn(BTN_BLUE);
	init_btn(BTN_RED);
	init_btn(BTN_GREEN);
	init_btn(BTN_YELLOW);

	// init players
	p_left = (Player_t){
			5,
			11,
			0,
			{PADDING, DISP_H / 2},
			{PADDING, DISP_H / 2},
			0};

	p_right = (Player_t){
			5,
			11,
			0,
			{DISP_W - PADDING, DISP_H / 2},
			{DISP_W - PADDING, DISP_H / 2},
			0};

	// init ball
	ball = (Ball_t){
			3,
			{DISP_W / 2, DISP_H / 2},
			{1, 0}};

	// scores
	int x = 0;
	int y = 0;

	p_left_score[0].x = x;
	p_left_score[0].y = y;
	p_left_score[1].x = x;
	p_left_score[1].y = y;
	p_left_score[2].x = x + SEGMENT_LENGTH;
	p_left_score[2].y = y;
	p_left_score[3].x = x;
	p_left_score[3].y = y + SEGMENT_LENGTH;
	p_left_score[4].x = x;
	p_left_score[4].y = y + SEGMENT_LENGTH;
	p_left_score[5].x = x;
	p_left_score[5].y = y + (2 * SEGMENT_LENGTH);
	p_left_score[6].x = x + SEGMENT_LENGTH;
	p_left_score[6].y = y + SEGMENT_LENGTH;

	x = (DISP_W - SEGMENT_LENGTH) - 1;

	p_right_score[0].x = x;
	p_right_score[0].y = y;
	p_right_score[1].x = x;
	p_right_score[1].y = y;
	p_right_score[2].x = x + SEGMENT_LENGTH;
	p_right_score[2].y = y;
	p_right_score[3].x = x;
	p_right_score[3].y = y + SEGMENT_LENGTH;
	p_right_score[4].x = x;
	p_right_score[4].y = y + SEGMENT_LENGTH;
	p_right_score[5].x = x;
	p_right_score[5].y = y + (2 * SEGMENT_LENGTH);
	p_right_score[6].x = x + SEGMENT_LENGTH;
	p_right_score[6].y = y + SEGMENT_LENGTH;
}

int main(void)
{
	xPixelMutex = xSemaphoreCreateMutex(); // only one task can access the framebuffer at a time
	xDrawMutex = xSemaphoreCreateMutex();	 // make sure only complete objects are drawn
	xInterruptSemaphore = xSemaphoreCreateBinary();

	init();

	xTaskCreate(task_draw, "draw", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(task_update_players, "update_players", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(task_update_ball, "update_ball", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(task_update_score, "update_score", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

	vTaskStartScheduler();

	return 0;
}
