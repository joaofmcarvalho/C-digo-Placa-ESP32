#include "BleGamepad.h"
#include <WiFi.h>

#define num_bot 2

const byte analog[num_bot] = {34,35};
const byte botao_pin[num_bot] = {4,16}; // 4 ,16
const byte botao[num_bot] = {1,2};
const byte hat_pin[num_bot] = {17,18}; // 17,18
signed char hat_botao[num_bot] = {1,5};
bool botao_estado[num_bot] = {false, false}; // Estado dos botões

byte i = 0;
BleGamepadConfiguration config; 
BleGamepad gamepad("Miritiboard Gamepad","Inteceleri");


void setup() {
  Serial.begin(115200);
  // Definir a frequência da CPU para 80 MHz
  setCpuFrequencyMhz(8);
  // Desativa a funcionalidade Wi-Fi
  WiFi.mode(WIFI_OFF);
  WiFi.disconnect(true);
  
  for (i=0; i<num_bot; i++){
    pinMode(botao_pin[i], INPUT_PULLUP);
    pinMode(hat_pin[i], INPUT_PULLUP);
  }

  gamepad.begin();
  config.setAutoReport(false);
}

void loop() {
  if(gamepad.isConnected()){
    int vrx = map(analogRead(analog[0]), 4095, 0, 0, 32737);
    int vry = map(analogRead(analog[1]), 4095, 0, 0, 32737);
    gamepad.setLeftThumb(vrx, vry);
    for (i=0; i<num_bot; i++){
      !digitalRead(hat_pin[i]) ? gamepad.setHat1(hat_botao[i]), delay(200): gamepad.setHat1(HAT_CENTERED);
    }
    for (i=0; i<num_bot; i++){
      !digitalRead(botao_pin[i]) ? gamepad.press(botao[i]): gamepad.release(botao[i]);
    }
  }
}
