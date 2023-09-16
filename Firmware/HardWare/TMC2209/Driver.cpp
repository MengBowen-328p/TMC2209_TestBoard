// ----------------------------------------------------------------------------
// Driver.h
// Use for TMC2209 on STM32
// Authors: Nico Meng
//
// ----------------------------------------------------------------------------
#include "Driver.h"

void TMC2209::serialWrite(uint8_t *data)
{
    HAL_UART_Transmit(&huart1, data, sizeof(&data), HAL_MAX_DELAY);
}

uint8_t TMC2209::serialRead(uint8_t *prxdata)
{
    HAL_UART_Receive(&huart1, prxdata, sizeof(read_buffer),HAL_MAX_DELAY);
    uint8_t buffer[10];
    buffer = &prxdata;
}

template<typename Datagram>
uint8_t TMC2209::calculateCrc(Datagram &datagram,
                              uint8_t datagram_size)
{
    uint8_t crc = 0;
    uint8_t byte;
    for (uint8_t i = 0; i < (datagram_size - 1); ++i)
    {
        byte = (datagram.bytes >> (i * BITS_PER_BYTE)) & BYTE_MAX_VALUE;
        for (uint8_t j = 0; j < BITS_PER_BYTE; ++j)
        {
            if ((crc >> 7) ^ (byte & 0x01))
            {
                crc = (crc << 1) ^ 0x07;
            } else
            {
                crc = crc << 1;
            }
            byte = byte >> 1;
        }
    }
    return crc;
}

uint32_t TMC2209::reverseData(uint32_t data)
{
    uint32_t reversed_data = 0;
    uint8_t right_shift;
    uint8_t left_shift;
    for (uint8_t i = 0; i < DATA_SIZE; ++i)
    {
        right_shift = (DATA_SIZE - i - 1) * BITS_PER_BYTE;
        left_shift = i * BITS_PER_BYTE;
        reversed_data |= ((data >> right_shift) & BYTE_MAX_VALUE) << left_shift;
    }
    return reversed_data;
}

template<typename Datagram>
void TMC2209::sendDatagramUnidirectional(Datagram &datagram,
                                         uint8_t datagram_size)
{
    uint8_t byte;

    for (uint8_t i = 0; i < datagram_size; ++i)
    {
        byte = (datagram.bytes >> (i * BITS_PER_BYTE)) & BYTE_MAX_VALUE;
        serialWrite(&byte);
    }
}

template<typename Datagram>
void TMC2209::sendDatagramBidirectional(Datagram &datagram, uint8_t datagram_size)
{
    uint8_t byte;

    // Wait for the transmission of outgoing serial data to complete
//    serialFlush();

    // clear the serial receive buffer if necessary
    while (HAL_UART_GetState(&huart1) == 0)
    {
        byte = serialRead();
    }

    // write datagram
    for (uint8_t i = 0; i < datagram_size; ++i)
    {
        byte = (datagram.bytes >> (i * BITS_PER_BYTE)) & BYTE_MAX_VALUE;
        serialWrite(byte);
    }

    // Wait for the transmission of outgoing serial data to complete
//    serialFlush();

    // wait for bytes sent out on TX line to be echoed on RX line
    uint32_t echo_delay = 0;
    while ((serialAvailable() < datagram_size) and
           (echo_delay < ECHO_DELAY_MAX_MICROSECONDS))
    {
        delayMicroseconds(ECHO_DELAY_INC_MICROSECONDS);
        echo_delay += ECHO_DELAY_INC_MICROSECONDS;
    }

    if (echo_delay >= ECHO_DELAY_MAX_MICROSECONDS)
    {
        return;
    }

    // clear RX buffer of echo bytes
    for (uint8_t i = 0; i < datagram_size; ++i)
    {
        byte = serialRead();
    }
}


void TMC2209::write(uint8_t register_address, uint32_t data)
{
    UARTWriteAccessDatagram write_data;
    write_data.bytes = 0;
    write_data.sync = SYNC;
    write_data.slave_address = SERIAL_ADDRESS_0;
    write_data.register_address = register_address;
    write_data.rw = RW_WRITE;
    write_data.data = reverseData(data);
    write_data.crc = calculateCrc(write_data, WRITE_READ_REPLY_DATAGRAM_SIZE);
    sendDatagramUnidirectional(write_data, WRITE_READ_REPLY_DATAGRAM_SIZE);
}

uint32_t TMC2209::read(uint8_t register_address)
{
    UARTReadAccessDatagram read_data;
    read_data.bytes = 0;
    read_data.sync = SYNC;
    read_data.slave_address = SERIAL_ADDRESS_0;
    read_data.register_address = register_address;
    read_data.rw = RW_READ;
    read_data.crc = calculateCrc(read_data, READ_REQUEST_DATAGRAM_SIZE);

}
//TMC2209 tmc2209;



