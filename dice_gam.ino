#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define BUTTON_PIN 4   // Push button pin
#define BUZZER_PIN 5   // Buzzer pin

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;); // Stop if OLED fails
  }

  // Startup sequence
  startupScreen();
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    tone(BUZZER_PIN, 1000, 150); // Start tone
    rollDice();
    delay(300); // debounce
  }
}

void startupScreen() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(10, 20);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.print("Welcome to");
  display.setTextSize(2);
  display.setCursor(10, 35);
  display.print("Tech Zaid");
  display.display();
  delay(2000);

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(5, 25);
  display.print("Where Tech Begins");
  display.display();
  delay(2000);

  for (int i = 3; i > 0; i--) {
    display.clearDisplay();
    display.setTextSize(3);
    display.setCursor(55, 20);
    display.print(i);
    display.display();
    tone(BUZZER_PIN, 800 + i * 200, 200);
    delay(1000);
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(20, 25);
  display.print("Let's Go!");
  display.display();
  tone(BUZZER_PIN, 1500, 300);
  delay(1500);
}

void rollDice() {
  unsigned long startTime = millis();
  while (millis() - startTime < 1500) { // rolling
    int value = random(1, 7);
    drawDice(value);
    delay(100);
  }

  // Final result
  int finalValue = random(1, 7);
  drawDice(finalValue);
  tone(BUZZER_PIN, 1500, 300); // Final tone
}

void drawDice(int value) {
  display.clearDisplay();

  // Show "ANS =" on left
  display.setTextSize(1);
  display.setCursor(5, 28);
  display.print("ANS =");
  display.setTextSize(2);
  display.setCursor(40, 24);
  display.print(value);

  // Draw dice box
  display.drawRect(80, 8, 40, 48, SSD1306_WHITE);

  // Pip positions relative to dice box
  int x1 = 88, y1 = 16;
  int x3 = 112, y3 = 16;
  int x5 = 100, y5 = 32;
  int x7 = 88, y7 = 48;
  int x9 = 112, y9 = 48;
  int xLeftMid = 88, yMid = 32;
  int xRightMid = 112, yMid2 = 32;

  switch (value) {
    case 1:
      pip(x5, y5); break;
    case 2:
      pip(x1, y1); pip(x9, y9); break;
    case 3:
      pip(x1, y1); pip(x5, y5); pip(x9, y9); break;
    case 4:
      pip(x1, y1); pip(x3, y1); pip(x7, y9); pip(x9, y9); break;
    case 5:
      pip(x1, y1); pip(x3, y1); pip(x5, y5); pip(x7, y9); pip(x9, y9); break;
    case 6:
      pip(x1, y1); pip(x3, y1); pip(xLeftMid, yMid); pip(xRightMid, yMid2); pip(x7, y9); pip(x9, y9); break;
  }

  display.display();
}

void pip(int x, int y) {
  display.fillCircle(x, y, 3, SSD1306_WHITE);
}
