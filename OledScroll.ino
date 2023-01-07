#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_DC    11
#define OLED_CS    12
#define OLED_CLK   10
#define OLED_MOSI   9
#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

char message[] = "Hello WOrrrrrllllllllllllllllllllllllllllldddd";
int  x, minX;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setTextWrap(false);
  x    = display.width();
  minX = -12 * strlen(message); // 12 = 6 pixels/character * text size 2
}

void loop() {
  display.clearDisplay();
  display.setCursor(x, 20);
  display.print(message);
  display.display();

  if(--x < minX) x = display.width();
}
