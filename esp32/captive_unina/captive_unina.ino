#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <SPIFFS.h>   // to load file on esp32
#include "web_handler.h"
#include "ap_handler.h"

// PIN setup
#define TX 17
#define RX 16
#define BAUD_RATE 9600

String received_command = "";

DNSServer dns_server;
WebServer http_server(80);

void setup() {
  Serial.begin(115200);

  if (!SPIFFS.begin(true)) {
      Serial.println("[ERROR] SPIFFS mount failed!");
      return;
  }

  File root = SPIFFS.open("/");
  File file = root.openNextFile();
  Serial.print("[SPIFFS] File uploaded on board: ");
  while (file) {
    Serial.println(file.name());
    file = root.openNextFile();
  }

  Serial1.begin(BAUD_RATE, SERIAL_8N1, RX, TX);
  Serial.println("[OK] Ready to receive command via Serial1 (USART).");
  
}

void loop() {

  while (Serial1.available()) {
    char c = Serial1.read();
    received_command += c;

    if (c == '\n') {
      received_command.trim();
      Serial.print("[INFO] Command received: ");
      Serial.println(received_command);

      if (received_command == "start" && !ap_is_active()) {
        ap_start();
      } else if (received_command == "stop_" && ap_is_active()) {
        ap_stop();
      }

      received_command = "";
    } 

  }

  // only if AP is active, manage DNS and HTTP requests
  if (ap_is_active()) {
    dns_server.processNextRequest();
    http_server.handleClient();
  }

  delay(10);

}
