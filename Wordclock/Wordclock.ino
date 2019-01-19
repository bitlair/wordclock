// Inspired by https://github.com/niekproductions/word-clock

// Required Libraries:
// - Arduino JSON (https://arduinojson.org/)
// - Time library (http://playground.arduino.cc/code/time)

// Web portal requires files on SPIFFS, please see the following URL for
// more information:

// http://esp8266.github.io/Arduino/versions/2.0.0/doc/filesystem.html

#define FASTLED_ESP8266_RAW_PIN_ORDER
#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>
#include <TimeLib.h>
#include <vector>
#include <ESP8266WiFi.h>
#include "ESP8266HTTPUpdateServer.h"

const char *version = "0.1";

#define MAX_WIFI_NETWORKS 32
#define MAX_SSID_LENGTH 32
#define WIFI_NETWORK_UPDATE_INTERVAL 60000

struct WifiNetwork {
  char ssid[MAX_SSID_LENGTH + 1];
  uint8_t encryptionType;
  int32_t RSSI;
  int32_t channel;
  bool isHidden;
};

enum LedMode {
  single,
  words,
  hourly,
  rainbow
};

enum BrightnessMode {
  fixedBrightness,
  ldrBrightness,
  timeBrightness
};

struct Configuration {
  char ntp_server[256];
  LedMode ledMode;
  uint8_t singleColorHue;
  uint8_t hourlyColors[24];
  uint8_t wordColors[25];
  BrightnessMode brightnessMode;
  uint8_t maxBrightness;
  uint8_t minBrightness;
  uint8_t brightnessStartHour;
  uint8_t brightnessEndHour;
  uint8_t checksum;
};

struct ClockfaceWord {
  std::vector<int> leds;
  int colorCodeInTable;
  bool (*isActive)(int, int);
};

Configuration config;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("BITLAIR Wordclock, v");
  Serial.println(version);
  Serial.print("ESP ID: ");
  Serial.println(String(ESP.getChipId()));

  configurationSetup();
  wifiSetup();
  webserverSetup();
  timeSetup();
  ledSetup();
}

void loop() {
  wifiLoop();
  webserverLoop();
  timeLoop();
  ledLoop();
}
