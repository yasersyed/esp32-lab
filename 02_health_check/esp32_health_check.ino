// ESP32 health check sketch
// Prints chip and flash info, scans Wi-Fi networks, and blinks LED.

#include <WiFi.h>

const int LED_PIN = 2;
unsigned long lastBlink = 0;
bool ledState = false;

void printChipInfo() {
  Serial.println("=== CHIP INFO ===");
  Serial.printf("Model: %s\n", ESP.getChipModel());
  Serial.printf("Revision: %d\n", ESP.getChipRevision());
  Serial.printf("Cores: %d\n", ESP.getChipCores());
  Serial.printf("CPU Frequency: %d MHz\n", ESP.getCpuFreqMHz());
  Serial.printf("SDK Version: %s\n", ESP.getSdkVersion());
  Serial.println();
}

void printMemoryInfo() {
  Serial.println("=== MEMORY INFO ===");
  Serial.printf("Flash Size: %u bytes\n", ESP.getFlashChipSize());
  Serial.printf("Sketch Size: %u bytes\n", ESP.getSketchSize());
  Serial.printf("Free Sketch Space: %u bytes\n", ESP.getFreeSketchSpace());
  Serial.printf("Heap Size: %u bytes\n", ESP.getHeapSize());
  Serial.printf("Free Heap: %u bytes\n", ESP.getFreeHeap());
  Serial.println();
}

void scanWifi() {
  Serial.println("=== WIFI SCAN ===");
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true);
  delay(100);

  int networks = WiFi.scanNetworks();
  if (networks == 0) {
    Serial.println("No networks found.");
  } else {
    Serial.printf("Found %d network(s):\n", networks);
    for (int i = 0; i < networks; i++) {
      Serial.printf("%2d) %-32s RSSI: %4d dBm  CH: %2d  %s\n",
                    i + 1,
                    WiFi.SSID(i).c_str(),
                    WiFi.RSSI(i),
                    WiFi.channel(i),
                    (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "OPEN" : "SECURED");
      delay(10);
    }
  }
  WiFi.scanDelete();
  Serial.println();
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  delay(1200);

  Serial.println();
  Serial.println("ESP32 Health Check Starting...");
  Serial.println();

  printChipInfo();
  printMemoryInfo();
  scanWifi();

  Serial.println("Health check complete. LED heartbeat running.");
}

void loop() {
  if (millis() - lastBlink >= 1000) {
    lastBlink = millis();
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState ? HIGH : LOW);

    Serial.printf("Heartbeat | Uptime: %lu sec | Free Heap: %u bytes\n",
                  millis() / 1000,
                  ESP.getFreeHeap());
  }
}
