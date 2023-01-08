#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define CHAR_WIDTH 6
#define VERTICAL_OFFSET 8
#define TEXT_SIZE 2

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

char message[] = "Hello WOrrrrrllllllllllllllllllllllllllllldddd";
int  first_char_pixel, left_most_pixel;

void setup() {
  // Initialize display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32
  display.clearDisplay();
  display.setTextSize(TEXT_SIZE);
  display.setTextWrap(false);

  // By default, the background text color is transparent.
  // Setting the text background to BLACK allows the text to
  // scroll, without requiring the entire screen to be cleared.
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);

  // Begin scrolling in from off-screen (right)
  first_char_pixel = display.width();

  // Calculate the left-most pixel (starting position) of the cursor
  left_most_pixel = -1 * CHAR_WIDTH * TEXT_SIZE * strlen(message);
}

void loop() {
  /*
   * The screen will only display the text between pixels 0 to 132.
   * The cursor is the beginning pixel for a string to be printed.
   * The cursor can be moved to any non-printable position. By moving
   * the cursor into the negative space, you achieve the effect of left
   * scrolling, because the screen will act as a sliding window.
   *
   *              SSD1306 OLED:
   *              -------------
   * "Hello WOrrrr|rllllllllll|llllllllllllllllllldddd"
   *              -------------
   *   -1                    1          2         3
   *  210987654321|01234567890|1234567890123456789012345678
   *  <<< Negative | Positive >>>
   *
   * _**NOTE:** Numbers shown above represent characters, not pixels._
   */

  // Tell the OLED display where to begin printing the message
  display.setCursor(first_char_pixel, VERTICAL_OFFSET);

  // Print the message at the cursor position
  display.print(message);

  // Render the display contents
  display.display();

  // Advance the cursor into the negative space,
  // until message is no longer visible.
  if (--first_char_pixel < left_most_pixel) {
    first_char_pixel = display.width();
  }
}
