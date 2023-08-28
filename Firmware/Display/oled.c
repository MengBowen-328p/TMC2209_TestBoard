//
// Created by 15216 on 2023/8/28.
//
#include "oled.h"

uint8_t I2C_OLED_GRAM[I2C_PIC_H * I2C_PIC_W]; // 画布8*128

// OLED的显存
// 存放格式如下.
//[0]0 1 2 3 ... 127
//[1]0 1 2 3 ... 127
//[2]0 1 2 3 ... 127
//[3]0 1 2 3 ... 127
//[4]0 1 2 3 ... 127
//[5]0 1 2 3 ... 127
//[6]0 1 2 3 ... 127
//[7]0 1 2 3 ... 127
// 其中每一页的每一列都有8个数据

void OLED_Delay(uint16_t MS)
{
    HAL_Delay(MS);
}

// IIC 写命令
static void I2C_OLED_Write_Cmd(uint8_t dat)
{
    // IIC_Mem_Write(I2C_OLED_ADDR, 0x00, I2C_MEMADD_SIZE_8BIT, &dat, 1); // 写命令
    HAL_I2C_Mem_Write(&hi2c2, I2C_OLED_ADDR, 0x00, I2C_MEMADD_SIZE_8BIT, &dat, 1, 0xffff);
}

// IIC 连续写数据
static void I2C_OLED_Write_Data(uint8_t *dat, uint16_t Size)
{
    HAL_I2C_Mem_Write(&hi2c2, I2C_OLED_ADDR, 0x40, I2C_MEMADD_SIZE_8BIT, dat, Size, 0xffff); // 写数据
    // HAL_I2C_Mem_Write_DMA(&hi2c1, I2C_OLED_ADDR, 0x40, I2C_MEMADD_SIZE_8BIT, dat, Size); // 写数据
}

// 颜色反显
void I2C_OLED_ColorTurn(uint8_t i)
{
    if (i == 0)
    {
        I2C_OLED_Write_Cmd(0xA6); // 正常显示
    }
    else if (i == 1)
    {
        I2C_OLED_Write_Cmd(0xA7); // 反色显示
    }
}

// 屏幕旋转180度
void I2C_OLED_DisplayTurn(uint8_t i)
{
    if (i == 0)
    {
        I2C_OLED_Write_Cmd(0xC8); // 正常显示
        I2C_OLED_Write_Cmd(0xA1);
    }
    else if (i == 1)
    {
        I2C_OLED_Write_Cmd(0xC0); // 反转显示
        I2C_OLED_Write_Cmd(0xA0);
    }
}
// 开启OLED显示
void I2C_OLED_DisPlay_On(void)
{
    I2C_OLED_Write_Cmd(0x8D); // 电荷泵使能
    I2C_OLED_Write_Cmd(0x14); // 开启电荷泵
    I2C_OLED_Write_Cmd(0xAF); // 点亮屏幕
}

// 关闭OLED显示
void I2C_OLED_DisPlay_Off(void)
{
    I2C_OLED_Write_Cmd(0x8D); // 电荷泵使能
    I2C_OLED_Write_Cmd(0x10); // 关闭电荷泵
    I2C_OLED_Write_Cmd(0xAF); // 关闭屏幕
}

/**
 * @brief OLED初始化
 *
 */
void I2C_OLED_Init(void)
{
    OLED_Delay(200);

    I2C_OLED_Write_Cmd(0xAE); //--turn off oled panel
    I2C_OLED_Write_Cmd(0x00); //---set low column address
    I2C_OLED_Write_Cmd(0x10); //---set high column address
    I2C_OLED_Write_Cmd(0x40); //--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    I2C_OLED_Write_Cmd(0x81); //--set contrast control register
    I2C_OLED_Write_Cmd(0xCF); // Set SEG Output Current Brightness
    I2C_OLED_Write_Cmd(0xA1); //--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
    I2C_OLED_Write_Cmd(0xC8); // Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
    I2C_OLED_Write_Cmd(0xA6); //--set normal display

    I2C_OLED_Write_Cmd(0xA8); //--set multiplex ratio(1 to 64)
    I2C_OLED_Write_Cmd(0x3f); //--1/64 duty

    I2C_OLED_Write_Cmd(0xD3); //-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
    I2C_OLED_Write_Cmd(0x00); //-not offset
    I2C_OLED_Write_Cmd(0xd5); //--set display clock divide ratio/oscillator frequency
    I2C_OLED_Write_Cmd(0x80); //--set divide ratio, Set Clock as 100 Frames/Sec
    I2C_OLED_Write_Cmd(0xD9); //--set pre-charge period
    I2C_OLED_Write_Cmd(0xF1); // Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    I2C_OLED_Write_Cmd(0xDA); //--set com pins hardware configuration
    I2C_OLED_Write_Cmd(0x12);
    I2C_OLED_Write_Cmd(0xDB); //--set vcomh
    I2C_OLED_Write_Cmd(0x40); // Set VCOM Deselect Level

    I2C_OLED_Write_Cmd(0x20); //-Set Page Addressing Mode (0x00/0x01/0x02)
    // I2C_OLED_Write_Cmd(0x02,OLED_CMD);//页地址模式
    I2C_OLED_Write_Cmd(0x00); // 水平寻址模式

    I2C_OLED_Write_Cmd(0x8D); //--set Charge Pump enable/disable
    I2C_OLED_Write_Cmd(0x14); //--set(0x10) disable
    I2C_OLED_Write_Cmd(0xA4); // Disable Entire Display On (0xa4/0xa5)
    I2C_OLED_Write_Cmd(0xA6); // Disable Inverse Display On (0xa6/a7)
    I2C_OLED_Write_Cmd(0xAF);

    I2C_OLED_ColorTurn(0);	 // 0正常显示，1 反色显示
    I2C_OLED_DisplayTurn(0); // 0正常显示 1 屏幕翻转显示

    memset(I2C_OLED_GRAM, 0, sizeof(I2C_OLED_GRAM)); // 初始化OLED数据缓冲区
}

/**
 * @brief 画点或清除点
 *
 * @param x x:0~127
 * @param y y:0~63
 * @param PointState 0:清除, 1:设置
 */
void I2C_OLED_Point(uint16_t x, uint16_t y, uint16_t PointState)
{
    uint16_t i, m, n;

    if (x > 127 || y > 63)
    {
        return;
    }

    i = y / 8; // 获得坐标所在页数
    m = y % 8; // 获得偏移位数
    n = 1 << m;
    // 将数据传入图像帧
    if (PointState)
        I2C_OLED_GRAM[i * I2C_PIC_W + x] |= n; // 设置点
    else
        I2C_OLED_GRAM[i * I2C_PIC_W + x] &= ~n; // 清除点
}

// 清除缓存中数据
void I2C_OLED_Clear(void)
{
    memset(I2C_OLED_GRAM, 0, sizeof(I2C_OLED_GRAM));

    // uint8_t i, n;
    // for (i = 0; i < I2C_PIC_H; i++)
    // {
    // 	for (n = 0; n < I2C_PIC_W; n++)
    // 	{
    // 		I2C_OLED_GRAM[i * I2C_PIC_W + n] = 0;
    // 	}
    // }
}

// 更新显存到OLED
void I2C_OLED_UPdata(void)
{
    // 水平模式下设置
    I2C_OLED_Write_Cmd(0x21); // 设置列
    I2C_OLED_Write_Cmd(0x00); // 设置列起始地址
    I2C_OLED_Write_Cmd(0x7f); // 设置列结束地址
    I2C_OLED_Write_Cmd(0x22); // 设置页
    I2C_OLED_Write_Cmd(0x00); // 设置页起始地址
    I2C_OLED_Write_Cmd(0x07); // 设置页结束地址

    I2C_OLED_Write_Data(I2C_OLED_GRAM, I2C_PIC_H * I2C_PIC_W);
}

void I2C_OLED_ShowPic(uint8_t *Pic)
{
    // 水平模式下设置
    I2C_OLED_Write_Cmd(0x21); // 设置列
    I2C_OLED_Write_Cmd(0x00); // 设置列起始地址
    I2C_OLED_Write_Cmd(0x7f); // 设置列结束地址
    I2C_OLED_Write_Cmd(0x22); // 设置页
    I2C_OLED_Write_Cmd(0x00); // 设置页起始地址
    I2C_OLED_Write_Cmd(0x07); // 设置页结束地址

    I2C_OLED_Write_Data(Pic, I2C_PIC_H * I2C_PIC_W);
}

void OLED_DecodeFont(uint16_t X, uint16_t Y, uint16_t Width, uint16_t Height, uint8_t *Font_Buf)
{
    uint16_t i, j, k, Read_Count;
    uint8_t Font_Dat;
    Read_Count = 0;
    for (j = 0; j < Height; j++)
    {
        for (i = 0; i < Width / 8; i++)
        {
            Font_Dat = Font_Buf[Read_Count];
            Read_Count++;
            for (k = 0; k < 8; k++)
            {
                if (Font_Dat & (0x80 >> k))
                    I2C_OLED_Point(X + i * 8 + k, Y + j, 1);
                else
                    I2C_OLED_Point(X + i * 8 + k, Y + j, 0);
            }
        }
    }
}

/**
 * @brief OLED绘制多个字符
 *
 * @param X X轴
 * @param Y Y轴
 * @param Str 字符串
 * @param Size 字符串长度
 */
void OLED_DrawMultiChar(uint16_t X, uint16_t Y, uint8_t *Str, uint8_t Size)
{
    uint8_t *Font;
    uint16_t Width, Height;
    uint8_t pos;

    while (Size--)
    {
        if (*Str == '\0') // 字符串末尾
        {
            return;
        }
        if (*Str == '\n') // 换行
        {
            Str++;
            X = 0;
            Y += Height;
            continue;
        }

        Font = (uint8_t *)Get_Font_Data(Str, &Width, &Height, &pos);
        Str += pos; // 移动到下一个字符
        OLED_DecodeFont(X, Y, Width, Height, Font);

        X += Width;
        if (X > 128)
        {
            X = 0;
            Y += Height;
        }
    }
    Font = NULL;
}

/**
 * @brief OLED绘制字符串
 *
 * @param X X轴
 * @param Y Y轴
 * @param Str 字符串
 */
void OLED_DrawString(uint16_t X, uint16_t Y, uint8_t *Str)
{
    OLED_DrawMultiChar(X, Y, Str, strlen((char *)Str));
}

/**
 * @brief OLED居中绘制字符串
 *
 * @param Y Y轴坐标(X轴自动计算)
 * @param Str 字符串
 */
void OLED_CenterDrawString(uint16_t Y, uint8_t *Str)
{
    uint8_t X;
    uint16_t Font_Width;
    Font_Width = statistics_StrWidth(Str);
    if (I2C_PIC_W > Font_Width)
    {
        X = (I2C_PIC_W - Font_Width) / 2;
    }
    else
    {
        X = 0;
    }

    OLED_DrawString(X, Y, Str);
}

/**
 * @brief OLED绘制字符串并更新到屏幕
 *
 * @param X X轴
 * @param Y Y轴
 * @param Str 字符串
 */
void OLED_ShowString(uint16_t X, uint16_t Y, uint8_t *Str)
{
    OLED_DrawString(X, Y, Str);
    I2C_OLED_UPdata();
}

/**
 * @brief OLED居中绘制字符串并更新到屏幕
 *
 * @param Y Y轴坐标(X轴自动计算)
 * @param Str 字符串
 */
void OLED_CenterShowString(uint16_t Y, uint8_t *Str)
{
    OLED_CenterDrawString(Y, Str);
    I2C_OLED_UPdata();
}

/**
 * @brief  在 ILI9341 显示器上使用 Bresenham 算法画线段
 * @param  usX1 ：在特定扫描方向下线段的一个端点X坐标
 * @param  usY1 ：在特定扫描方向下线段的一个端点Y坐标
 * @param  usX2 ：在特定扫描方向下线段的另一个端点X坐标
 * @param  usY2 ：在特定扫描方向下线段的另一个端点Y坐标
 * @note 可使用LCD_SetBackColor、LCD_SetTextColor、LCD_SetColors函数设置颜色
 * @retval 无
 */
void OLED_DrawLine(uint16_t usX1, uint16_t usY1, uint16_t usX2, uint16_t usY2)
{
    uint16_t us;
    uint16_t usX_Current, usY_Current;

    int32_t lError_X = 0, lError_Y = 0, lDelta_X, lDelta_Y, lDistance;
    int32_t lIncrease_X, lIncrease_Y;

    lDelta_X = usX2 - usX1; // 计算坐标增量
    lDelta_Y = usY2 - usY1;

    usX_Current = usX1;
    usY_Current = usY1;

    if (lDelta_X > 0)
        lIncrease_X = 1; // 设置单步方向
    else if (lDelta_X == 0)
        lIncrease_X = 0; // 垂直线
    else
    {
        lIncrease_X = -1;
        lDelta_X = -lDelta_X;
    }

    if (lDelta_Y > 0)
        lIncrease_Y = 1;
    else if (lDelta_Y == 0)
        lIncrease_Y = 0; // 水平线

    else
    {
        lIncrease_Y = -1;
        lDelta_Y = -lDelta_Y;
    }

    if (lDelta_X > lDelta_Y)
        lDistance = lDelta_X; // 选取基本增量坐标轴

    else
        lDistance = lDelta_Y;

    for (us = 0; us <= lDistance + 1; us++) // 画线输出
    {
        I2C_OLED_Point(usX_Current, usY_Current, 1); // 画点
        lError_X += lDelta_X;
        lError_Y += lDelta_Y;

        if (lError_X > lDistance)
        {
            lError_X -= lDistance;
            usX_Current += lIncrease_X;
        }
        if (lError_Y > lDistance)
        {
            lError_Y -= lDistance;
            usY_Current += lIncrease_Y;
        }
    }
}

/**
 * @brief  在 ILI9341 显示器上画一个矩形
 * @param  usX_Start ：在特定扫描方向下矩形的起始点X坐标
 * @param  usY_Start ：在特定扫描方向下矩形的起始点Y坐标
 * @param  usWidth：矩形的宽度（单位：像素）
 * @param  usHeight：矩形的高度（单位：像素）
 * @param  ucFilled ：选择是否填充该矩形
 *   该参数为以下值之一：
 *     @arg 0 :空心矩形
 *     @arg 1 :实心矩形
 * @note 可使用LCD_SetBackColor、LCD_SetTextColor、LCD_SetColors函数设置颜色
 * @retval 无
 */
void OLED_DrawRectangle(uint16_t usX_Start, uint16_t usY_Start, uint16_t usWidth, uint16_t usHeight, uint8_t ucFilled)
{
    if (ucFilled)
    {
        for (size_t i = 0; i < usHeight; i++)
        {
            OLED_DrawLine(usX_Start, usY_Start + i, usX_Start + usWidth - 1, usY_Start);
        }
    }
    else
    {
        OLED_DrawLine(usX_Start, usY_Start, usX_Start + usWidth - 1, usY_Start);
        OLED_DrawLine(usX_Start, usY_Start + usHeight - 1, usX_Start + usWidth - 1, usY_Start + usHeight - 1);
        OLED_DrawLine(usX_Start, usY_Start, usX_Start, usY_Start + usHeight - 1);
        OLED_DrawLine(usX_Start + usWidth - 1, usY_Start, usX_Start + usWidth - 1, usY_Start + usHeight - 1);
    }
}

/**
 * @brief  在 ILI9341 显示器上使用 Bresenham 算法画圆
 * @param  usX_Center ：在特定扫描方向下圆心的X坐标
 * @param  usY_Center ：在特定扫描方向下圆心的Y坐标
 * @param  usRadius：圆的半径（单位：像素）
 * @param  ucFilled ：选择是否填充该圆
 *   该参数为以下值之一：
 *     @arg 0 :空心圆
 *     @arg 1 :实心圆
 * @note 可使用LCD_SetBackColor、LCD_SetTextColor、LCD_SetColors函数设置颜色
 * @retval 无
 */
void OLED_DrawCircle(uint16_t usX_Center, uint16_t usY_Center, uint16_t usRadius, uint8_t ucFilled)
{
    int16_t sCurrentX, sCurrentY;
    int16_t sError;

    sCurrentX = 0;
    sCurrentY = usRadius;
    sError = 3 - (usRadius << 1); // 判断下个点位置的标志

    while (sCurrentX <= sCurrentY)
    {
        int16_t sCountY;

        if (ucFilled)
        {
            for (sCountY = sCurrentX; sCountY <= sCurrentY; sCountY++)
            {
                I2C_OLED_Point(usX_Center + sCurrentX, usY_Center + sCountY, 1); // 1，研究对象
                I2C_OLED_Point(usX_Center - sCurrentX, usY_Center + sCountY, 1); // 2
                I2C_OLED_Point(usX_Center - sCountY, usY_Center + sCurrentX, 1); // 3
                I2C_OLED_Point(usX_Center - sCountY, usY_Center - sCurrentX, 1); // 4
                I2C_OLED_Point(usX_Center - sCurrentX, usY_Center - sCountY, 1); // 5
                I2C_OLED_Point(usX_Center + sCurrentX, usY_Center - sCountY, 1); // 6
                I2C_OLED_Point(usX_Center + sCountY, usY_Center - sCurrentX, 1); // 7
                I2C_OLED_Point(usX_Center + sCountY, usY_Center + sCurrentX, 1); // 0
            }
        }
        else
        {
            I2C_OLED_Point(usX_Center + sCurrentX, usY_Center + sCurrentY, 1); // 1，研究对象
            I2C_OLED_Point(usX_Center - sCurrentX, usY_Center + sCurrentY, 1); // 2
            I2C_OLED_Point(usX_Center - sCurrentY, usY_Center + sCurrentX, 1); // 3
            I2C_OLED_Point(usX_Center - sCurrentY, usY_Center - sCurrentX, 1); // 4
            I2C_OLED_Point(usX_Center - sCurrentX, usY_Center - sCurrentY, 1); // 5
            I2C_OLED_Point(usX_Center + sCurrentX, usY_Center - sCurrentY, 1); // 6
            I2C_OLED_Point(usX_Center + sCurrentY, usY_Center - sCurrentX, 1); // 7
            I2C_OLED_Point(usX_Center + sCurrentY, usY_Center + sCurrentX, 1); // 0
        }
        sCurrentX++;

        if (sError < 0)
            sError += 4 * sCurrentX + 6;

        else
        {
            sError += 10 + 4 * (sCurrentX - sCurrentY);
            sCurrentY--;
        }
    }
}
