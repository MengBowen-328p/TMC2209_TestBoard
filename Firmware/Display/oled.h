//
// Created by 15216 on 2023/8/28.
//

#ifndef FIRMWARE_OLED_H
#define FIRMWARE_OLED_H

#include "main.h"
#include "i2c.h"

#include "font.h"


// OLED 设备地址（8位）,0x78为右移一位的地址,0x3c未原始地址
// #define I2C_OLED_ADDR 0x3c
#define I2C_OLED_ADDR 0x78

#define OLED_CMD 0  // 写命令
#define OLED_DATA 1 // 写数据

#define I2C_PIC_W 128
#define I2C_PIC_H 8 // 画布大小

void I2C_OLED_Point(uint16_t x, uint16_t y, uint16_t PointState);
void I2C_OLED_Clear(void);
void I2C_OLED_UPdata(void);
void I2C_OLED_ShowPic(uint8_t *Pic);

void OLED_DecodeFont(uint16_t X, uint16_t Y, uint16_t Width, uint16_t Height, uint8_t *Font_Buf);
void OLED_DrawString(uint16_t X, uint16_t Y, uint8_t *Str);
void OLED_CenterDrawString(uint16_t Y, uint8_t *Str);

void OLED_ShowString(uint16_t X, uint16_t Y, uint8_t *Str);
void OLED_CenterShowString(uint16_t Y, uint8_t *Str);

void I2C_OLED_Init(void);

void OLED_DrawLine(uint16_t usX1, uint16_t usY1, uint16_t usX2, uint16_t usY2);
void OLED_DrawRectangle(uint16_t usX_Start, uint16_t usY_Start, uint16_t usWidth, uint16_t usHeight, uint8_t ucFilled);
void OLED_DrawCircle(uint16_t usX_Center, uint16_t usY_Center, uint16_t usRadius, uint8_t ucFilled);



#endif //FIRMWARE_OLED_H
