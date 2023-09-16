// ----------------------------------------------------------------------------
// Driver.h
// Use for TMC2209 on STM32
// Authors: Nico Meng
//
// ----------------------------------------------------------------------------

#ifndef FIRMWARE_DRIVER_H
#define FIRMWARE_DRIVER_H

#include "main.h"
#include "usart.h"

class TMC2209
{
public:
    uint8_t read_buffer[100];
    const static uint8_t SYNC = 0x05;
    const static uint8_t RW_WRITE = 1;
    const static uint8_t RW_READ = 0;
    const static uint8_t DATA_SIZE = 4;
    const static uint8_t BITS_PER_BYTE = 8;
    const static uint8_t BYTE_MAX_VALUE = 0xFF;
    const static uint8_t WRITE_READ_REPLY_DATAGRAM_SIZE = 8;
    const static uint8_t READ_REQUEST_DATAGRAM_SIZE = 4;
    enum SerialAddress
    {
        SERIAL_ADDRESS_0 = 0,
        SERIAL_ADDRESS_1 = 1,
        SERIAL_ADDRESS_2 = 2,
        SERIAL_ADDRESS_3 = 3,
    };

    union UARTWriteAccessDatagram     //串口写操作数据报文
    {
        struct
        {
            uint64_t sync: 4;                   //同步位:          4bit
            uint64_t reserved: 4;               //保留位:          4bit
            uint64_t slave_address: 8;          //从设备地址位:     8bit
            uint64_t register_address: 7;       //寄存器地址位:     7bit
            uint64_t rw: 1;                     //读写操作位:       1bit
            uint64_t data: 32;                  //数据位:          32bit
            uint64_t crc: 8;                    //CRC校验位:       8bit
        };
        uint64_t bytes;
    };

    union UARTReadAccessDatagram
    {
        struct
        {
            uint64_t sync: 4;
            uint64_t reserved: 4;
            uint64_t slave_address: 8;
            uint64_t register_address: 7;
            uint64_t rw: 1;
            uint64_t crc: 8;
        };
        uint64_t bytes;
    };

    void serialWrite(uint8_t *data);
    uint8_t serialRead(uint8_t *prxdata);

    template<typename Datagram>
    uint8_t calculateCrc(Datagram &datagram, uint8_t datagram_size);

    void write(uint8_t register_address, uint32_t data);

    uint32_t reverseData(uint32_t data);

    template<typename Datagram>
    void sendDatagramUnidirectional(Datagram &datagram, uint8_t datagram_size);


    template<typename Datagram>
    void sendDatagramBidirectional(Datagram &datagram, uint8_t datagram_size);

};

#endif