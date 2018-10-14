// Required Libraries:
// - Arduino JSON (https://arduinojson.org/)

// Web portal requires files on SPIFFS, please see the following URL for
// more information:

// http://esp8266.github.io/Arduino/versions/2.0.0/doc/filesystem.html

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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("BITLAIR Wordclock, v");
  Serial.println(version);

  wifiSetup();
  webserverSetup();
}

void loop() {
  wifiLoop();
  webserverLoop();
}
