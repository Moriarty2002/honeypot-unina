#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>

#include "web_handler.h"
#include "ap_handler.h"

const char *ap_ssid = "Wi-Fi UniNA";
const char *ap_password = "";
const byte DNS_PORT = 53;

bool ap_active = false;

void ap_start() {
    WiFi.softAP(ap_ssid, ap_password);
    dns_server.start(DNS_PORT, "*", WiFi.softAPIP());
    setup_web_handler();
    http_server.begin();
    ap_active = true;

    Serial.println("[INFO] Honeypot Unina Started");
    Serial.println("[INFO] IP Address:");
    Serial.println(WiFi.softAPIP());
}

void ap_stop() {
    http_server.stop();
    dns_server.stop();
    WiFi.softAPdisconnect(true);
    ap_active = false;

    Serial.println("[INFO] Honeypot Unina Stopped");
}

bool ap_is_active() {
    return ap_active;
}
