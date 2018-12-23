#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define NTP_SYNC_INTERVAL   1200
#define NTP_RETRY_INTERVAL  60

const int NTP_PACKET_SIZE = 48;
byte packetBuffer[NTP_PACKET_SIZE]; 
WiFiUDP udp;
const int timeZone = 1;

// Check if Daylight saving time (DST) applies
// Northern Hemisphere - +1 hour between March and October
bool isDST(int d, int m, int y) {
  bool dst = false;
  dst = (m > 3 && m < 10); // October-March
  
  if (m == 3){
    // Last sunday of March
    dst = (d >= ((31 - (5 * y /4 + 4) % 7)));
  }else if (m == 10){
    // Last sunday of October
    dst = (d < ((31 - (5 * y /4 + 1) % 7)));
  }
  
  return dst;
}

bool isDSTSwitchDay(int d, int m, int y){
  bool dst = false;
  if (m == 3){
    // Last sunday of March
    dst = (d == ((31 - (5 * y /4 + 4) % 7)));
  } else if (m == 10){
    // Last sunday of October
    dst = (d == ((31 - (5 * y /4 + 1) % 7)));
  }
  return dst;
}

time_t adjustForDaylightSavingTime(time_t original_time) {
  if (isDSTSwitchDay(day(original_time), month(original_time), year(original_time))) {
    if (month(original_time) == 3 && hour(original_time) >= 2) {
      return original_time + SECS_PER_HOUR;
    } else if (month(original_time) == 10 && hour(original_time) < 2) {
      return original_time + SECS_PER_HOUR;
    }
  } else if (isDST(day(original_time), month(original_time), year(original_time))) {
    return original_time + SECS_PER_HOUR;
  }
                
  return original_time;  
}

time_t getNtpTime() {
  IPAddress server_ip;
    
  Serial.print("Retrieving time from NTP server ");
  Serial.println(config.ntp_server);

  if(!WiFi.hostByName(config.ntp_server, server_ip)) {
    Serial.println("Unable to retrieve NTP server IP");
    setSyncInterval(NTP_RETRY_INTERVAL);
    return 0;
  }
  
  Serial.print("IP: ");
  Serial.println(server_ip.toString());

  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  udp.beginPacket(server_ip, 123); 
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();

  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      Serial.println("Received NTP sized package");

      udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      
      // New time in seconds since Jan 1, 1970
      unsigned long newTime = secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
      setSyncInterval(NTP_SYNC_INTERVAL);
      return adjustForDaylightSavingTime(newTime);
    }
  }

  Serial.println("Unable to retrieve time from NTP server");
  setSyncInterval(NTP_RETRY_INTERVAL);
  return 0;
}

void timeSetup() {
  setSyncProvider(getNtpTime);
  setSyncInterval(NTP_SYNC_INTERVAL);
  udp.begin(8888);
}

void timeSync() {
  setSyncInterval(1);
}

void timeLoop() {
  now();
}
