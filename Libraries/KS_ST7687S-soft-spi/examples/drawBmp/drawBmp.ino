#include "qq_logo.c"
#include "KS_ST7687S_Latch.h"

uint8_t pin_cs = 7, pin_rs = 5, pin_wr = 13, pin_db0 = 2, pin_db1 = 3, pin_db2 = 4, pin_db3 = 12, pin_db4 = 6, pin_db5 = 8, pin_db6 = 9, pin_db7 = 10;
KS_ST7687S_Latch tft(pin_cs, pin_rs, pin_wr , pin_db0, pin_db1, pin_db2, pin_db3, pin_db4, pin_db5, pin_db6, pin_db7);

void setup(void)
{
  Serial.begin(115200);
  tft.begin();
  tft.fillScreen(DISPLAY_BLACK);
  tft.drawBmp((uint8_t*)gImage_qq_logo, -50, -50, 100, 100);
}

void loop(void)
{

}
