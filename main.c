#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"

void crc_16_tbl();
uint16_t UpdateCRC(uint8_t byte, uint16_t prevCRC);
uint16_t CalcCRC(uint8_t* bytes, int32_t len, uint16_t initValue);

uint16_t polynomial =0x1021;
uint16_t tableCRC[256];
uint16_t initValue = 0x0000;

void main() {

     uint8_t data[]={0x31, 0x32,  0x33 ,0x34,  0x35, 0x36,  0x37, 0x38, 0x39,0x41, 0x42, 0x43,  0x45, 0x44,  0x46,0x30,0x31,0x32 ,0x33,0x34 ,0x35,0x36 ,0x37,0x38 ,0x39,0x41 ,0x42,0x43 ,0x44,0x45 ,0x46 };

    stdio_init_all();
    crc_16_tbl();

    sleep_ms(5000);

        for(int j=0;j<32;j++)
        {
            for(int i=0;i<8;i++)
            {
                printf("%04X ",tableCRC[i+j*8]);
            }
            printf("\n");
        }
        printf("%04X \n",CalcCRC(data,(sizeof(data)/sizeof(data[0])),initValue));

    sleep_ms(5000);

        for(int j=0;j<32;j++)
        {
            for(int i=0;i<8;i++)
            {
                printf("%04X ",tableCRC[i+j*8]);
            }
            printf("\n");
        }
        printf("%04X \n",CalcCRC(data,(sizeof(data)/sizeof(data[0])),initValue));

    while(true){    
        
    }        
}

void crc_16_tbl()
{
    uint16_t LengthCRC=16;
    uint16_t mask = (1 << (LengthCRC - 1));    
    for (uint16_t i = 0; i < 256; i++)
    {
        uint16_t crc = i << 8;
        
        for (uint8_t bit = 0; bit < 8; bit++)
        {
            if (crc & mask)
                crc = (crc << 1) ^ polynomial;
            else
                crc <<= 1;
        }
     tableCRC[i]=crc;
    }
}

uint16_t UpdateCRC(uint8_t byte, uint16_t prevCRC)
{   
    return tableCRC[((prevCRC >> 8) ^ byte) & 0xff] ^ (prevCRC << 8);
}

uint16_t CalcCRC(uint8_t* bytes, int32_t len, uint16_t initValue)
{
    uint16_t prevCRC = initValue;
    for (int i = 0; i < len; i++)
    {
        prevCRC = UpdateCRC(bytes[i], prevCRC);
    }
    return prevCRC;
}
