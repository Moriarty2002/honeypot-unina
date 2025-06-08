#ifndef AP_HANDLER_H
#define AP_HANDLER_H

extern WebServer http_server;
extern DNSServer dns_server; 

void ap_start();
void ap_stop();
bool ap_is_active();

#endif
