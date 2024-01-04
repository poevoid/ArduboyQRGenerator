#include <Arduboy2.h>
#include "qrcode.h"

Arduboy2 arduboy;
QRCode qrcode;
const uint8_t CHAR_LIMIT = 20;
//char fav[CHAR_LIMIT];
char text[CHAR_LIMIT + 1] = "HELLO ARDUBOY       "; // Initial text, padded with spaces
uint8_t cursorPosition = 0;

void setup() {
  arduboy.begin();
  arduboy.clear();
  arduboy.setCursor(0, 0);
  arduboy.print("Use arrows to edit:");
  arduboy.setFrameRate(10);
}

void loop() {
  if (!arduboy.nextFrame()) return;
  arduboy.pollButtons();

  handleInput();
  displayText();
   for (uint8_t y = 0; y< qrcode.size; y++) {
    for (uint8_t x = 0; x< qrcode.size; x++){
      if (qrcode_getModule(&qrcode, x, y)){
        arduboy.drawPixel(x, y+25, WHITE);
      } else {
        arduboy.drawPixel(x, y+25, BLACK);
      }
    }
  }
  arduboy.display();
}

void handleInput() {
  if (arduboy.justPressed(LEFT_BUTTON) && cursorPosition > 0) {
    cursorPosition--;
  }

  if (arduboy.justPressed(RIGHT_BUTTON) && cursorPosition < CHAR_LIMIT) {
    cursorPosition++;
  }

  if (arduboy.pressed(UP_BUTTON) && text[cursorPosition]< 127) {
    text[cursorPosition]++;
  }

  if (arduboy.pressed(DOWN_BUTTON) && text[cursorPosition > 0]) {
    text[cursorPosition]--;
  }
  if (arduboy.justPressed(A_BUTTON)) {
    generateQRCode();
  }
}

void displayText() {
  arduboy.clear();
  arduboy.setCursor(0, 10);
  arduboy.print(text);

  // Display cursor
  arduboy.setCursor(cursorPosition * 6, 20); // 6 pixels per character
  arduboy.print("^");

}

void generateQRCode(){
  uint8_t qrcodeData[qrcode_getBufferSize(6)];
qrcode_initText(&qrcode, qrcodeData, 3, 0, text);
}