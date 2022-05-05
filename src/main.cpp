#include "game.h"
#include <Arduino.h>

#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);
game_data_t game;

volatile bool button_pressed = false;
void button_isr() { button_pressed = true; }

void reset() {
  reset_game(&game);
  button_pressed = false;
}

void showSplash(const char *greeting) {
  uint16_t w, h;
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  h = tft.fontHeight();
  w = tft.textWidth(greeting);
  tft.setRotation(1);
  tft.setCursor((tft.width() - w) / 2, (tft.height() - h) / 2);
  tft.printf(greeting);
}

void draw(uint16_t x, uint16_t y, uint8_t v) {
  tft.drawPixel(x, y, v ? TFT_WHITE : TFT_BLACK);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), button_isr, FALLING);

  tft.init();
  showSplash("Game Of Life");

  init_game(&game, TFT_WIDTH, TFT_HEIGHT);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (button_pressed) {
    reset();
  }

  tft.setRotation(0);
  update_game(&game, draw);
}