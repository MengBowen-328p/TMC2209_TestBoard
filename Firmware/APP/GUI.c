//
// Created by 15216 on 2023/8/28.
//

#include "GUI.h"

void show_GUI(void)
{
    I2C_OLED_Init();
    OLED_DrawRectangle(0, 0, 63, 127, 0);
    OLED_ShowString(1,1,"TMC2209 Test Board");

}