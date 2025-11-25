#include <SoftwareSerial.h>

SoftwareSerial sim(10, 11);

void setup() {
  Serial.begin(9600);
  sim.begin(9600);
  
  Serial.println(F("=== SIGNAL STRENGTH MONITOR ==="));
  Serial.println(F("This will check signal every 10 seconds"));
  Serial.println(F("Try moving antenna/module to different locations"));
  Serial.println(F("Target: RSSI > 5 (minimum), RSSI > 10 (good)"));
  Serial.println();
  
  delay(5000);
}

void loop() {
  // Clear buffer
  while (sim.available()) sim.read();
  
  // Get current time
  unsigned long seconds = millis() / 1000;
  Serial.print(F("Time: "));
  Serial.print(seconds);
  Serial.print(F("s - "));
  
  // Request signal strength
  sim.println(F("AT+CSQ"));
  
  // Read response
  String response = "";
  unsigned long start = millis();
  
  while (millis() - start < 3000) {
    if (sim.available()) {
      response += (char)sim.read();
    }
  }
  
  // Parse signal
  if (response.indexOf("+CSQ:") >= 0) {
    int colonPos = response.indexOf(':');
    int commaPos = response.indexOf(',');
    
    if (colonPos >= 0 && commaPos > colonPos) {
      int rssi = response.substring(colonPos + 1, commaPos).toInt();
      
      Serial.print(F("RSSI: "));
      Serial.print(rssi);
      Serial.print(F(" ("));
      
      if (rssi == 0 || rssi == 99) {
        Serial.print(F("NO SIGNAL"));
      } else {
        int dbm = -113 + (rssi * 2);
        Serial.print(dbm);
        Serial.print(F(" dBm"));
      }
      
      Serial.print(F(") - "));
      
      // Status
      if (rssi == 0 || rssi == 99) {
        Serial.println(F("✗ MOVE ANTENNA!"));
      } else if (rssi < 5) {
        Serial.println(F("⚠ Too weak"));
      } else if (rssi < 10) {
        Serial.println(F("△ Weak but may work"));
      } else if (rssi < 15) {
        Serial.println(F("○ Fair"));
      } else if (rssi < 20) {
        Serial.println(F("● Good"));
      } else {
        Serial.println(F("✓ Excellent"));
      }
    }
  } else {
    Serial.println(F("No response from module"));
  }
  
  delay(10000); // Check every 10 seconds
}