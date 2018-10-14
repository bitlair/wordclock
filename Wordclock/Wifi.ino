#include <ESP8266WiFi.h>

WifiNetwork known_wifi_networks[MAX_WIFI_NETWORKS];
int total_known_wifi_networks = 0;
long last_wifi_network_update = 0;
int updating_wifi_networks = 0;
wl_status_t last_wifi_status = WL_DISCONNECTED;

void wifiSetup() {
  WiFi.begin();  
}

void wifiLoop() {
  wl_status_t status = WiFi.status();
  
  if (last_wifi_status != status) {
    last_wifi_status = status;
    
    if (status == WL_CONNECTED) {
      Serial.print("Connected, IP address: ");
      Serial.println(WiFi.localIP());
    }
  }

  if (!updating_wifi_networks) {
    if ((last_wifi_network_update == 0) || ((millis() - last_wifi_network_update) > WIFI_NETWORK_UPDATE_INTERVAL)) {
      updating_wifi_networks = true;
      WiFi.scanNetworksAsync(updateKnownWifiNetworks);
    }
  }
}

void updateKnownWifiNetworks(int networksFound)
{
  updating_wifi_networks = false;
  last_wifi_network_update = millis();
  
  Serial.printf("%d network(s) found\n", networksFound);
  for (int i = 0; i < min(networksFound, MAX_WIFI_NETWORKS); i++)
  {
    WiFi.SSID(i).toCharArray(known_wifi_networks[i].ssid, MAX_SSID_LENGTH);
    known_wifi_networks[i].channel = WiFi.channel(i);
    known_wifi_networks[i].encryptionType = WiFi.encryptionType(i);
    known_wifi_networks[i].RSSI = WiFi.RSSI(i);
    known_wifi_networks[i].isHidden = WiFi.isHidden(i);
  }

  total_known_wifi_networks = min(networksFound, MAX_WIFI_NETWORKS);
}

int totalKnownWifiNetworks() {
  return total_known_wifi_networks;
}

WifiNetwork *knownWifiNetworks() {
  return known_wifi_networks;
}
