#include "web_handler.h"
#include "ap_handler.h"

// PIN setup
#define TX 43
#define RX 44
#define BAUD_RATE 9600

String received_command = "";

void setup() {
  Serial.begin(115200);
  Serial1.begin(baud_rate, SERIAL_8N1, RX, TX);
  Serial.println("Ready to receive command via Serial1 (USART).");

  if (!SPIFFS.begin(true)) {
      Serial.println("SPIFFS mount failed!");
      return;
  }
}

void loop() {

  while (Serial1.available()) {
    char c = Serial1.read();
    if (c == '\n') {
      received_command.trim();
      Serial.print("Command received: ");
      Serial.println(received_command);

      if (received_command == "start" && !ap_is_active()) {
        ap_start();
      } else if (received_command == "stop" && !ap_is_active()) {
        ap_stop()
      }

      received_command = "";
    } 
    
    else { received_command += c; }

  }

  // solo se AP attivo, gestisci DNS e web
  if (ap_is_active()) {
    dns_server.processNextRequest();
    http_server.handleClient();
  }

  delay(10);
}

