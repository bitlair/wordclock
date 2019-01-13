#include <DNSServer.h>

WifiNetwork known_wifi_networks[MAX_WIFI_NETWORKS];
int total_known_wifi_networks = 0;
long last_wifi_network_update = 0;
int updating_wifi_networks = 0;
wl_status_t last_wifi_status = WL_DISCONNECTED;

const byte DNS_PORT = 53;
DNSServer dnsServer;

enum access_point_status {
  AP_OFF,
  AP_PENDING_ON,
  AP_ON,
  AP_PENDING_OFF
};

access_point_status access_point_status = AP_OFF;
long access_point_pending_action ;

void wifiSetup() {
  WiFi.begin();  

  if (WiFi.SSID().length() == 0) {
    wifiActivateAccessPoint();
  } else {
    Serial.print("Wifi configured, connecting to ");
    Serial.println(WiFi.SSID());
    wifiDeactivateAccessPoint();
  }
}

void wifiLoop() {
  wl_status_t status = WiFi.status();
  
  if (last_wifi_status != status) {
    last_wifi_status = status;
    
    if (status == WL_CONNECTED) {
      WiFi.setAutoReconnect(true);
      Serial.print("Connected, IP address: ");
      Serial.println(WiFi.localIP());
      wifiDelayedDeactivateAccessPoint();
      timeSync();
    } else if (WiFi.SSID().length() == 0) {
      wifiActivateAccessPoint();
    } else if ((status == WL_NO_SSID_AVAIL) || (status == WL_CONNECT_FAILED)) {
      wifiDelayedActivateAccessPoint();
    } else {
      Serial.print("New WiFi status: ");
      Serial.println(status);
    }
  }

  if (!updating_wifi_networks) {
    if ((last_wifi_network_update == 0) || ((millis() - last_wifi_network_update) > WIFI_NETWORK_UPDATE_INTERVAL)) {
      updating_wifi_networks = true;
      WiFi.scanNetworksAsync(updateKnownWifiNetworks);
    }
  }

  wifiAccessPointDelayedAction();
  dnsServer.processNextRequest();
}

void wifiConnect(String ssid, String password) {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  if (password.length() > 0) {
    WiFi.begin(ssid.c_str(), password.c_str());
  } else {
    WiFi.begin(ssid.c_str());
  }
}

bool wifiIsAccessPointActive() {
  return access_point_status == AP_ON;
}

void wifiActivateAccessPoint() {
  switch(access_point_status) {
    case AP_OFF:
    case AP_PENDING_ON: {
      Serial.println("Activating access point for configuration");
      String ssid = "WordClock-" + String(ESP.getChipId());
      access_point_status = WiFi.softAP(ssid.c_str()) ? AP_ON : AP_OFF;

      Serial.println(WiFi.softAPIP());

      dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
      dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());
      break;
    }
    case AP_PENDING_OFF:
      Serial.println("Cancelled pending deactivation of access point");
      access_point_pending_action = 0;
      access_point_status = AP_ON;
      break;
  }
}

void wifiDelayedActivateAccessPoint() {
   switch(access_point_status) {
      case AP_OFF:
        Serial.println("Scheduled access point activation");
        access_point_status = AP_PENDING_ON;
        access_point_pending_action = millis() + 10000;
        break;
      case AP_PENDING_OFF:
        Serial.println("Cancelled pending deactivation of access point");
        access_point_status = AP_ON;
        access_point_pending_action = 0;
        break;
   }
}

void wifiDeactivateAccessPoint() {
  Serial.println("Deactivating access point");
  WiFi.mode(WIFI_AP);
  WiFi.softAPdisconnect(false);
  access_point_status = AP_OFF;
}

void wifiDelayedDeactivateAccessPoint() {
   switch(access_point_status) {
      case AP_ON:
        Serial.println("Scheduled access point deactivation");
        access_point_status = AP_PENDING_OFF;
        access_point_pending_action = millis() + 10000;
        break;
      case AP_PENDING_ON:
        Serial.println("Cancelled pending activation of access point");
        access_point_status = AP_OFF;
        access_point_pending_action = 0;
        break;
   } 
}

void wifiAccessPointDelayedAction() {
  if (access_point_pending_action == 0) return;
  if (millis() < access_point_pending_action) return;

  if (access_point_status == AP_PENDING_ON) {
    wifiActivateAccessPoint();
  } else if (access_point_status == AP_PENDING_OFF) {
    wifiDeactivateAccessPoint();
  }

  access_point_pending_action = 0;
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

void wifiDisconnect() {
  WiFi.disconnect(false);
  wifiActivateAccessPoint();
}
