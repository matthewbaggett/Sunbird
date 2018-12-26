#include "ssd1306.h"
#include "ssd1306_console.h"
#include "ssd1306_fonts.h"
#include "intf/i2c/ssd1306_i2c.h"
#include "i2c.h"

Ssd1306Console console;

void setupLCD() {
  Serial.printf("Starting up oled service at i2c address %#04x... ", OLED_I2C_ADDRESS);
  if(i2cDeviceExists(OLED_I2C_ADDRESS) || true){
    /* Select the font to use with menu and all font functions */
    ssd1306_setFixedFont(ssd1306xled_font6x8);
  
    ssd1306_128x64_i2c_initEx(I2C_SCL, I2C_SDA, SSD1306_SA);
    ssd1306_128x64_init();
  
    //ssd1306_128x64_i2c_init();
    const int canvasWidth = 128; // Width must be power of 2, i.e. 16, 32, 64, 128...
    const int canvasHeight = 64; // Height must be divided on 8, i.e. 8, 16, 24, 32...
    uint8_t canvasData[canvasWidth*(canvasHeight/8)];
    /* Create canvas object */
    if(OLED_FONT == 6)
      ssd1306_setFixedFont(ssd1306xled_font6x8);
    else if(OLED_FONT == 5)
      ssd1306_setFixedFont(digital_font5x7_AB);
    else
      Serial.printf("Invalid font selected: %d", OLED_FONT);
    ssd1306_clearScreen();
    Serial.println("[OK]");
  }else{
    Serial.println("[SKIPPED, not detected]");
  }
}

void testLCD() {
    Serial.printf("Starting LCD Test");
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
    Serial.printf("LCD Test complete.");
}


