//
// Created by 15216 on 2023/8/28.
//

#include "font.h"

/*
 * 常用ASCII表，偏移量32，大小:16（高度）* 8 （宽度）
 * 共1520字节
 */
const uint8_t ASCII8x16_Table[1520] = { //@conslons字体，阴码点阵格式，逐行顺向取摸
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x08, 0x00, 0x08, 0x18, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x34, 0x24, 0x24, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x16, 0x24, 0x7f, 0x24, 0x24, 0x24, 0x7e, 0x24, 0x24, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x08, 0x3e, 0x68, 0x48, 0x68, 0x1c, 0x16, 0x12, 0x12, 0x7c, 0x10, 0x10, 0x00,
        0x00, 0x00, 0x00, 0x61, 0xd2, 0x96, 0x74, 0x08, 0x10, 0x16, 0x29, 0x49, 0xc6, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x3c, 0x64, 0x64, 0x38, 0x72, 0x4a, 0xce, 0x46, 0x7f, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x04, 0x08, 0x18, 0x10, 0x30, 0x30, 0x30, 0x30, 0x10, 0x10, 0x18, 0x0c, 0x04,
        0x00, 0x00, 0x00, 0x20, 0x10, 0x08, 0x08, 0x0c, 0x04, 0x04, 0x04, 0x0c, 0x08, 0x18, 0x10, 0x20,
        0x00, 0x00, 0x00, 0x08, 0x0a, 0x34, 0x1c, 0x6a, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x7f, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x08, 0x30, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x02, 0x06, 0x04, 0x0c, 0x08, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x3c, 0x66, 0x42, 0x47, 0x5b, 0x73, 0x42, 0x66, 0x3c, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x18, 0x78, 0x48, 0x08, 0x08, 0x08, 0x08, 0x08, 0x7e, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x3c, 0x46, 0x06, 0x06, 0x04, 0x08, 0x10, 0x20, 0x7e, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x7c, 0x06, 0x06, 0x04, 0x3c, 0x02, 0x02, 0x06, 0x7c, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x0c, 0x1c, 0x14, 0x24, 0x64, 0x44, 0xff, 0x04, 0x04, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x7e, 0x60, 0x60, 0x60, 0x7e, 0x02, 0x02, 0x06, 0x7c, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x1e, 0x30, 0x60, 0x48, 0x76, 0x42, 0x42, 0x62, 0x3c, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x7e, 0x02, 0x06, 0x04, 0x0c, 0x08, 0x18, 0x10, 0x30, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x3c, 0x62, 0x42, 0x36, 0x1c, 0x66, 0x42, 0x42, 0x3c, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x3c, 0x66, 0x42, 0x42, 0x66, 0x1a, 0x02, 0x04, 0x78, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x18, 0x18, 0x08, 0x30, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x18, 0x30, 0x60, 0x10, 0x0c, 0x06, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x18, 0x04, 0x06, 0x0c, 0x10, 0x20, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x30, 0x1c, 0x06, 0x06, 0x06, 0x18, 0x10, 0x00, 0x10, 0x10, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x1c, 0x22, 0x41, 0x41, 0xdd, 0xb5, 0xa5, 0xa5, 0xaf, 0x94, 0xc0, 0x40, 0x3c,
        0x00, 0x00, 0x00, 0x00, 0x18, 0x1c, 0x34, 0x24, 0x26, 0x62, 0x7e, 0x43, 0xc1, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x7c, 0x46, 0x42, 0x46, 0x7c, 0x42, 0x42, 0x42, 0x7c, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x1e, 0x20, 0x40, 0x40, 0x40, 0x40, 0x40, 0x60, 0x3e, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x7c, 0x46, 0x42, 0x43, 0x43, 0x43, 0x42, 0x46, 0x78, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x7e, 0x60, 0x60, 0x60, 0x7e, 0x60, 0x60, 0x60, 0x7e, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x7e, 0x60, 0x60, 0x60, 0x7e, 0x60, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x1e, 0x60, 0x40, 0x40, 0xce, 0x42, 0x42, 0x62, 0x3e, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x7c, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x44, 0x78, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x42, 0x44, 0x48, 0x50, 0x70, 0x58, 0x4c, 0x44, 0x42, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3e, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x62, 0x66, 0x67, 0x5f, 0x5b, 0x5b, 0xc1, 0xc1, 0xc1, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x62, 0x62, 0x72, 0x52, 0x5a, 0x4a, 0x4e, 0x46, 0x46, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x3c, 0x62, 0x43, 0xc3, 0xc3, 0xc3, 0x43, 0x62, 0x3c, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x7c, 0x46, 0x42, 0x42, 0x46, 0x78, 0x40, 0x40, 0x40, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x3c, 0x62, 0x43, 0xc3, 0xc3, 0xc3, 0x43, 0x62, 0x3c, 0x18, 0x0f, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x7c, 0x66, 0x62, 0x66, 0x7c, 0x6c, 0x64, 0x66, 0x62, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x3e, 0x60, 0x40, 0x60, 0x1c, 0x06, 0x02, 0x02, 0x7c, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x7f, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x62, 0x3c, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xc1, 0x43, 0x42, 0x62, 0x26, 0x24, 0x34, 0x1c, 0x18, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xc1, 0xc1, 0x41, 0x49, 0x5b, 0x5b, 0x76, 0x66, 0x66, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x43, 0x66, 0x34, 0x18, 0x18, 0x1c, 0x24, 0x66, 0xc3, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xc1, 0x42, 0x66, 0x34, 0x1c, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x7e, 0x02, 0x04, 0x0c, 0x18, 0x10, 0x20, 0x60, 0x7e, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x1c, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1c,
        0x00, 0x00, 0x00, 0x40, 0x20, 0x20, 0x10, 0x10, 0x08, 0x08, 0x0c, 0x04, 0x06, 0x02, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x3c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x3c,
        0x00, 0x00, 0x00, 0x00, 0x18, 0x1c, 0x24, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
        0x00, 0x00, 0x00, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x06, 0x02, 0x3e, 0x42, 0x46, 0x7a, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x5c, 0x62, 0x42, 0x42, 0x42, 0x42, 0x7c, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x20, 0x60, 0x40, 0x60, 0x20, 0x3e, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x3e, 0x62, 0x42, 0x42, 0x42, 0x66, 0x3a, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x62, 0x42, 0x7e, 0x40, 0x60, 0x3e, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x0f, 0x18, 0x10, 0x10, 0x7e, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x66, 0x42, 0x66, 0x58, 0x40, 0x3e, 0x43, 0x42, 0x3c,
        0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x5c, 0x62, 0x42, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x78, 0x08, 0x08, 0x08, 0x08, 0x08, 0x7e, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x04, 0x0c, 0x00, 0x7c, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0c, 0x78,
        0x00, 0x00, 0x00, 0x60, 0x60, 0x60, 0x62, 0x6c, 0x78, 0x70, 0x68, 0x64, 0x62, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x78, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x7e, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x4b, 0x4b, 0x4b, 0x4b, 0x4b, 0x4b, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5c, 0x62, 0x42, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x62, 0x42, 0x43, 0x42, 0x62, 0x3c, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5c, 0x62, 0x42, 0x42, 0x42, 0x42, 0x7c, 0x40, 0x40, 0x40,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x62, 0x42, 0x42, 0x42, 0x66, 0x3a, 0x02, 0x02, 0x02,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6e, 0x72, 0x63, 0x60, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x20, 0x20, 0x3c, 0x06, 0x02, 0x7c, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0xfe, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1e, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x66, 0x3a, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0x42, 0x66, 0x24, 0x34, 0x18, 0x18, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc1, 0xc1, 0x5b, 0x5a, 0x5e, 0x66, 0x66, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x62, 0x26, 0x1c, 0x18, 0x1c, 0x26, 0x62, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0x42, 0x66, 0x24, 0x34, 0x1c, 0x18, 0x18, 0x30, 0xe0,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x06, 0x0c, 0x18, 0x10, 0x20, 0x7e, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x0e, 0x18, 0x10, 0x10, 0x10, 0x30, 0x70, 0x10, 0x10, 0x10, 0x10, 0x18, 0x0e,
        0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
        0x00, 0x00, 0x00, 0x30, 0x18, 0x08, 0x08, 0x08, 0x0c, 0x0e, 0x08, 0x08, 0x08, 0x08, 0x18, 0x30,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x71, 0x4b, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00};

//const CH_Font_Def GB2312_Table[] =
//	{
//		{"初", {0x20, 0x00, 0x10, 0x00, 0x01, 0xFC, 0xFC, 0x44, 0x08, 0x44, 0x10, 0x44, 0x10, 0x44, 0x34, 0x44, 0x58, 0x44, 0x94, 0x44, 0x14, 0x44, 0x10, 0x84, 0x10, 0x84, 0x11, 0x04, 0x12, 0x28, 0x14, 0x10}}, /*"初",20*/
//		{"始", {0x10, 0x20, 0x10, 0x20, 0x10, 0x20, 0x10, 0x40, 0xFC, 0x48, 0x24, 0x84, 0x25, 0xFE, 0x24, 0x82, 0x24, 0x00, 0x48, 0xFC, 0x28, 0x84, 0x10, 0x84, 0x28, 0x84, 0x44, 0x84, 0x80, 0xFC, 0x00, 0x84}}, /*"始",21*/
//		{"化", {0x08, 0x80, 0x08, 0x80, 0x08, 0x84, 0x10, 0x88, 0x10, 0x90, 0x30, 0xA0, 0x30, 0xC0, 0x50, 0x80, 0x91, 0x80, 0x12, 0x80, 0x14, 0x80, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x7E, 0x10, 0x00}}, /*"化",22*/
//		{"数", {0x08, 0x20, 0x49, 0x20, 0x2A, 0x20, 0x08, 0x3E, 0xFF, 0x44, 0x2A, 0x44, 0x49, 0x44, 0x88, 0xA4, 0x10, 0x28, 0xFE, 0x28, 0x22, 0x10, 0x42, 0x10, 0x64, 0x28, 0x18, 0x28, 0x34, 0x44, 0xC2, 0x82}}, /*"数",23*/
//		{"据", {0x20, 0x00, 0x23, 0xFC, 0x22, 0x04, 0x22, 0x04, 0xFB, 0xFC, 0x22, 0x20, 0x22, 0x20, 0x2B, 0xFE, 0x32, 0x20, 0xE2, 0x20, 0x22, 0xFC, 0x22, 0x84, 0x22, 0x84, 0x24, 0x84, 0xA4, 0xFC, 0x48, 0x84}}, /*"据",24*/
//};

/**
 * @brief 获取字体字模
 *
 * @param chr 要获取的字模
 * @param Width 获取到的宽度
 * @param Height 获取到的高度
 * @return uint8_t* 返回字模地址
 */
const uint8_t *Get_Font_Data(uint8_t *chr, uint16_t *Width, uint16_t *Height, uint8_t *Next_Pos)
{
    uint16_t pos, datnum;
//	uint16_t i;

    if (*chr < 127)
    {
        *Next_Pos = 1;
        if (*chr >= ' ')
        {
            *Width = 8;
            *Height = 16;

            pos = *chr - ' ';

            // 要读取的字节数量(该字体下占datnum个字节)
            datnum = (8 * 16) / 8;
            /*字模偏移地址*/
            pos = pos * datnum;

            return &ASCII8x16_Table[pos]; // 复制该字体的字模}
        }
        else
        {
            return NULL; // 复制该字体的字模
        }
    }
    //	return NULL;
}

/**
 * @brief 统计字符串宽度
 *
 * @param Str 输入字符串
 * @return uint16_t 字符串的宽度
 */
uint32_t statistics_StrWidth(uint8_t *Str)
{
    uint32_t Width = 0;
    while (*Str != '\0')
    {
        if (*Str < 127)
        {
            Width = Width + 8;
            Str++;
        }
    }
    return Width;
}