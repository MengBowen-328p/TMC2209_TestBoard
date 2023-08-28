//
// Created by 15216 on 2023/8/28.
//

#ifndef FIRMWARE_FONT_H
#define FIRMWARE_FONT_H



#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"
#include "stdio.h"
#include "string.h"

typedef struct __CH_Font_Def
{
    uint8_t index[4];	  //中文索引占4字节(GB2312编码)
    uint8_t FontData[32]; //字体数据96字节(16X16)
} CH_Font_Def;

const uint8_t *Get_Font_Data(uint8_t *chr, uint16_t *Width, uint16_t *Height, uint8_t *Next_Pos);
uint32_t statistics_StrWidth(uint8_t *Str);

#ifdef __cplusplus
}
#endif






#endif //FIRMWARE_FONT_H
