#ifndef KS_ST7687S_LATCH_H
#define KS_ST7687S_LATCH_H

#include "KSRobot_ST7687S.h"

class KS_ST7687S_Latch : public KSRobot_ST7687S
{
  public:
    KS_ST7687S_Latch(uint8_t cs,uint8_t rs,uint8_t wr,uint8_t lck,uint8_t spi_scl,uint8_t spi_mosi);      //add

    int16_t     begin();
    void        drawPixel(int16_t x, int16_t y, uint16_t color);

  private:
    uint8_t     pin_cs, pin_rs, pin_wr, pin_lck, pin_spi_scl, pin_spi_mosi;

    void        writeCmd(uint8_t cmd);
    void        writeDat(uint8_t dat);
    void        WriteBit(uint8_t dat);
    void        writeDatBytes(uint8_t* pDat, uint16_t count);
    void        writeRepeatPixel(uint16_t color, uint16_t count, uint16_t repeatCount);
};


#endif


