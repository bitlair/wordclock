// Serving files from SPIFFS inspired by https://tttapa.github.io/ESP8266/Chap11%20-%20SPIFFS.html

#include <ESP8266WebServer.h>
#include <FS.h>
#include "ArduinoJson.h"

ESP8266WebServer webserver(80);
StaticJsonBuffer<10000> jsonBuffer;

void webserverSetup() {
  SPIFFS.begin();

  webserver.on("/status", apiStatus);
  webserver.on("/wifi/networks", apiWifiNetworks);
  webserver.on("/wifi/disconnect", apiWifiDisconnect);
  webserver.on("/wifi/connect", apiWifiConnect);
  
  webserver.onNotFound([]() {
    if (!webserverServeFileFromSPIFFS(webserver.uri()))
      webserver.send(404, "text/plain", "404: Not Found");
  });

  webserver.begin();   
}

void webserverLoop() {
  webserver.handleClient();
}

String webserverGetContentType(String filename) { 
  if(filename.endsWith(".htm")) return "text/html";
  else if(filename.endsWith(".html")) return "text/html";
  else if(filename.endsWith(".css")) return "text/css";
  else if(filename.endsWith(".js")) return "application/javascript";
  else if(filename.endsWith(".svg")) return "image/svg+xml";
  else if(filename.endsWith(".png")) return "image/png";
  else if(filename.endsWith(".gif")) return "image/gif";
  else if(filename.endsWith(".jpg")) return "image/jpeg";
  else if(filename.endsWith(".ico")) return "image/x-icon";
  else if(filename.endsWith(".xml")) return "text/xml";
  else if(filename.endsWith(".pdf")) return "application/x-pdf";
  else if(filename.endsWith(".zip")) return "application/x-zip";
  else if(filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}

bool webserverServeFileFromSPIFFS(String path) { 
  Serial.println("handleFileRead: " + path);
  if(path.endsWith("/")) path += "index.html";
  String content_type = webserverGetContentType(path);
  String compressed_path = path + ".gz";
  if(SPIFFS.exists(compressed_path) || SPIFFS.exists(path)) {
    if(SPIFFS.exists(compressed_path)) path += ".gz";
    File file = SPIFFS.open(path, "r"); 
    size_t sent = webserver.streamFile(file, content_type);
    file.close();
    Serial.println(String("\tSent file: ") + path);
    return true;
  }
  Serial.println(String("\tFile Not Found: ") + path);
  return false;
}

void apiStatus() {
  JsonObject &root = jsonBuffer.createObject();
  root["version"] = version;

  String json;
  root.printTo(json);
  
  webserver.send(200, "application/json", json);
}

void apiWifiNetworks() {
  WifiNetwork *wifiNetworks = knownWifiNetworks();
  JsonArray& networks = jsonBuffer.createArray();

  for(int i = 0; i < totalKnownWifiNetworks(); i++) {
    JsonObject& network = networks.createNestedObject();
    network["ssid"] = wifiNetworks[i].ssid;
    network["rssi"] = wifiNetworks[i].RSSI;
    network["channel"] = wifiNetworks[i].channel;
    switch(wifiNetworks[i].encryptionType) {
      case ENC_TYPE_WEP: network["encryption"] = "WEP"; break;
      case ENC_TYPE_TKIP: network["encryption"] = "WPA/PSK"; break;
      case ENC_TYPE_CCMP: network["encryption"] = "WPA2/PSK"; break;
      case ENC_TYPE_NONE: break;
      case ENC_TYPE_AUTO: network["encryption"] = "WPA/WPA2/PSK"; break;
      default: network["encryption"] = "WPA2 Enterprise`"; break;
    }
  }

  String json;
  networks.printTo(json);
  
  webserver.send(200, "application/json", json);
}

void apiWifiDisconnect() {
  JsonObject &root = jsonBuffer.createObject();
  root["status"] = "ok";

  String json;
  root.printTo(json);
  
  webserver.send(200, "application/json", json);
  wifiDisconnect();
}

void apiWifiConnect() {
  String ssid = webserver.arg("ssid");
  String password = webserver.arg("password");

  wifiConnect(ssid, password);

  JsonObject &root = jsonBuffer.createObject();
  root["status"] = "connecting";

  String json;
  root.printTo(json);
  
  webserver.send(200, "application/json", json);
}
