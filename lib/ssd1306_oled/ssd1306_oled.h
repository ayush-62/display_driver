#ifndef _SSD1306_OLED_H_
#define _SSD1306_OLED_H_

#include "i2c.h"

#define DISPLAY_PORT (GPIOB)
#define SCL_PIN (GPIO8)
#define SDA_PIN (GPIO9)
#define CCR_VAL (17)
#define TRISE_VAL (14)

// #define OLED_ADDRESS (0b0111100)
#define OLED_COMMAND (0x00)
#define OLED_DATA (0x40)

#define DEFAULT_7bit_OLED_SLAVE_ADDRESS (0x3C)
#define I2C_COMMAND 0x00
#define I2C_DATA 0x40

#define true 1
#define false 0

void ssd1306_send_data(uint8_t spec, uint8_t data);
void OLED_init(void);
void OLED_Clear(void);
void setBuffer();
void display(void);

void drawPixel(int x, int y, int color);
void drawLine();
void drawFlatLine(int x, int y, int h, uint8_t horizontal);
void draw_rectangle(int x0, int y0, int x1, int y1);
void drawCircle(int xc, int yc, int x, int y);
void draw_circle(int xc, int yc, int r); 


#endif