#include "ssd1306.h"
#include "intf/i2c/ssd1306_i2c.h"

void setupLCD() {
  /* Select the font to use with menu and all font functions */
  ssd1306_setFixedFont(ssd1306xled_font6x8);

  ssd1306_128x64_i2c_initEx(I2C_SCL, I2C_SDA, SSD1306_SA);
  ssd1306_128x64_init();

  //ssd1306_128x64_i2c_init();
}

void testLCD() {
    debug.printf("Starting LCD Test");
    ssd1306_setFixedFont(ssd1306xled_font6x8);
    ssd1306_clearScreen();
    ssd1306_printFixed(0,  8, "Normal text", STYLE_NORMAL);
    ssd1306_printFixed(0, 16, "Bold text", STYLE_BOLD);
    ssd1306_printFixed(0, 24, "Italic text", STYLE_ITALIC);
    ssd1306_negativeMode();
    ssd1306_printFixed(0, 32, "Inverted bold", STYLE_BOLD);
    ssd1306_positiveMode();
    delay(3000);
    ssd1306_clearScreen();
    ssd1306_printFixedN(0, 0, "N3", STYLE_NORMAL, FONT_SIZE_8X);
    delay(3000);
    debug.printf("LCD Test complete.");
}

