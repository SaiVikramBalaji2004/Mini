#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // Initialize the display
  if(!display.begin(SSD1306_I2C_ADDRESS, OLED_RESET)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, SSD1306_WHITE);

  // Show the display buffer on the screen
  display.display();
  delay(2000);

  // Clear the display buffer
  display.clearDisplay();

  // Draw a line
  display.drawLine(0, 0, 127, 63, SSD1306_WHITE);
  display.display();
  delay(2000);

  // Clear the display buffer
  display.clearDisplay();

  // Draw a rectangle
  display.drawRect(10, 10, 50, 30, SSD1306_WHITE);
  display.display();
  delay(2000);

  // Clear the display buffer
  display.clearDisplay();

  // Draw some text
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0,0);     // Start at top-left corner
  display.println(F("Hello, world!"));
  display.display();
  delay(2000);
}

void loop() {
  // Nothing to do here
}
