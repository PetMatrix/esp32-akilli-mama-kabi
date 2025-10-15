/*
  ESP32 + DS3231 + DRV8825 test
  - Bluetooth adı: MamaKabiESP
  - Komutlar (Bluetooth Terminal uygulamasından):
      TIME           -> Saati gönder
      DIR 0/1        -> Yönü ayarla (0=CCW, 1=CW)
      SPEED <us>     -> Adım arası gecikme (mikrosaniye), örn: SPEED 800
      STEP <n>       -> n adım at (örn: STEP 200)
      ENABLE         -> Sürücüyü aktifle (EN LOW)
      DISABLE        -> Sürücüyü kapat (EN HIGH)

  Donanım:
    RTC (DS3231): VCC=3V3, GND, SDA=GPIO21, SCL=GPIO22
    DRV8825: VDD=3V3, GND, STEP=GPIO26, DIR=GPIO27, EN=GPIO25 (LOW=aktif)
             SLEEP & RESET birlikte 3V3, VMOT=12V (kondansatör şart)
*/

#include <Wire.h>
#include "RTClib.h"
#include "BluetoothSerial.h"

RTC_DS3231 rtc;
BluetoothSerial SerialBT;

// Pinler
const int PIN_STEP = 26;
const int PIN_DIR  = 27;
const int PIN_EN   = 25;

// Ayarlar
volatile uint32_t stepDelayUs = 400; // adımlar arası gecikme (us)
volatile bool directionCW = true;    // true=CW, false=CCW

// Basit step atma
void stepN(uint32_t n) {
  // EN LOW = aktif, emin ol
  digitalWrite(PIN_EN, LOW);
  digitalWrite(PIN_DIR, directionCW ? HIGH : LOW);

  for (uint32_t i = 0; i < n; i++) {
    digitalWrite(PIN_STEP, HIGH);
    delayMicroseconds(stepDelayUs);
    digitalWrite(PIN_STEP, LOW);
    delayMicroseconds(stepDelayUs);
  }
}

// Komut satırını (Bluetooth) parçala
void handleCommand(String cmd) {
  cmd.trim();
  cmd.toUpperCase();

  if (cmd == "TIME") {
    DateTime now = rtc.now();
    char buf[40];
    sprintf(buf, "%02d:%02d:%02d %02d/%02d/%04d",
            now.hour(), now.minute(), now.second(),
            now.day(), now.month(), now.year());
    SerialBT.println(buf);
    Serial.println(buf);
  }
  else if (cmd.startsWith("DIR ")) {
    int v = cmd.substring(4).toInt();
    directionCW = (v != 0);
    SerialBT.printf("DIR=%d\n", directionCW ? 1 : 0);
  }
  else if (cmd.startsWith("SPEED ")) {
    uint32_t v = (uint32_t)cmd.substring(6).toInt();
    if (v < 200) v = 200; // çok küçük değer motoru kaçırabilir
    stepDelayUs = v;
    SerialBT.printf("SPEED=%lu us\n", (unsigned long)stepDelayUs);
  }
  else if (cmd.startsWith("STEP ")) {
    uint32_t n = (uint32_t)cmd.substring(5).toInt();
    if (n == 0) n = 200; // default 1 tur için çoğu 1.8° motorda 200 adım (full-step)
    SerialBT.printf("STEP %lu...\n", (unsigned long)n);
    stepN(n);
    SerialBT.println("DONE");
  }
  else if (cmd == "ENABLE") {
    digitalWrite(PIN_EN, LOW);
    SerialBT.println("EN=LOW (aktif)");
  }
  else if (cmd == "DISABLE") {
    digitalWrite(PIN_EN, HIGH);
    SerialBT.println("EN=HIGH (pasif)");
  }
  else {
    SerialBT.println("KOMUTLAR: TIME | DIR 0/1 | SPEED <us> | STEP <n> | ENABLE | DISABLE");
  }

