//
// Created by 15216 on 2023/8/28.
//
#include "Driver.h"


void Driver_Init(void)
{
    HAL_GPIO_WritePin(Driver_EN_GPIO_Port, Driver_EN_Pin, GPIO_PIN_SET);
}

void Driver_DeInit(void)
{
    HAL_GPIO_WritePin(Driver_EN_GPIO_Port, Driver_EN_Pin, GPIO_PIN_RESET);
}

void Driver_CW(void)
{
    Driver_Init();
    HAL_GPIO_WritePin(Driver_DIR_GPIO_Port, Driver_DIR_Pin, GPIO_PIN_SET);
    HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_4); //此处一句后可直接进入中断
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
}

void Driver_CCW(void)
{
    Driver_Init();
    HAL_GPIO_WritePin(Driver_DIR_GPIO_Port, Driver_DIR_Pin, GPIO_PIN_RESET);
    HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_4); //此处一句后可直接进入中断
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) //中断回调
{
    static uint16_t i = 0;
    i++;
    if (i >= 200)  //此处10为产生PWM的数量，可设置为变量实时改变
    {
        i = 0;
        HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4); //产生指定数量的PWM波后停止PWM的产生
        Driver_DeInit();    //关闭驱动
    }
}
