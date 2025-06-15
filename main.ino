#include <WiFi.h>
#include <DHT.h>
#include "secrets.h" 

// WiFi Credentials
const char* ssid = WIFI_SSID; // Use the define from secrets.h
const char* password = WIFI_PASSWORD; // Use the define from secrets.h
// DHT Sensor Setup
#define DHTPIN 18          // GPIO where DHT11 is connected
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Web server on port 80
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Connect to WiFi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConnected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin(); // Start the web server
}

void loop() {
  WiFiClient client = server.available(); // Listen for incoming clients

  if (client) {
    Serial.println("Client connected");

    // Wait until client sends data
    while (!client.available()) {
      delay(1);
    }

    String request = client.readStringUntil('\r');
    client.flush();

    // Read from DHT sensor
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    // Debugging sensor reading issues
    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("Error: Failed to read from DHT sensor.");
    }

    // Build HTML page
    String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    html += "<meta http-equiv='refresh' content='5'>";
    html += "<title>DHT11 Sensor</title></head>";
    html += "<body style='font-family:sans-serif;text-align:center;background-color:#e3f2fd;'>";
    html += "<h2 style='color:#1565c0;'>ESP32 DHT11 Sensor Readings</h2>";
    html += "<div style='background:#fff176;padding:20px;border-radius:10px;'>";
    html += "<p><strong>Temperature:</strong> " + (isnan(temperature) ? "--" : String(temperature, 1)) + " &deg;C</p>";
    html += "<p><strong>Humidity:</strong> " + (isnan(humidity) ? "--" : String(humidity, 1)) + " %</p>";
    html += "</div><p style='font-size:14px;color:#555;'>Auto-refreshes every 5 seconds</p>";
    html += "</body></html>";

    // Send HTTP response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type: text/html");
    client.println("Connection: close");
    client.println();
    client.println(html);

    client.stop();
    Serial.println("Client disconnected");
  }
}