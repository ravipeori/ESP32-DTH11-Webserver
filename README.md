# ESP32 DHT11 Web Server

An ESP32-based web server that allows you to monitor real-time temperature and humidity readings from a DHT11 sensor via a web browser.

## Features

* **Real-time Data:** Displays live temperature and humidity readings.
* **Web Interface:** Access sensor data from any device on the same local network via a simple web page.
* **Auto-Refresh:** The web page automatically refreshes every 5 seconds for up-to-date data.
* **Simple Setup:** Easy to configure and deploy on an ESP32 board.

## Hardware Requirements

* ESP32 Development Board (e.g., ESP32-WROOM-32)
* DHT11 Temperature and Humidity Sensor
* Jumper wires
* Breadboard (optional)

## Software Requirements

* Arduino IDE
* ESP32 Boards Manager (installation instructions [here](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html))
* **Libraries:**
    * `WiFi.h` (comes with ESP32 board package)
    * `DHT.h` (install via Arduino IDE: `Sketch > Include Library > Manage Libraries...` search for "DHT sensor library by Adafruit")

## Circuit Diagram

Connect the DHT11 sensor to your ESP32 board as follows:

* **DHT11 VCC** -> ESP32 **3.3V**
* **DHT11 GND** -> ESP32 **GND**
* **DHT11 Data Pin** -> ESP32 **GPIO 18** (or any other digital pin, remember to update `#define DHTPIN` in the code)

*(Consider adding a simple Fritzing diagram or a hand-drawn diagram picture here later)*

## Installation and Setup

1.  **Open in Arduino IDE:** Open the `main.ino` (or your sketch file name) in the Arduino IDE.
2.  **Install Libraries:** Ensure you have the `DHT sensor library by Adafruit` installed via the Library Manager.
3.  **Select Board:** Go to `Tools > Board > ESP32 Arduino` and select your specific ESP32 board (e.g., `ESP32 Dev Module`).
4.  **Select Port:** Go to `Tools > Port` and select the serial port connected to your ESP32.
5.  **Configure WiFi Credentials:**
    * **IMPORTANT:** For security reasons, sensitive information like WiFi credentials should ideally be stored outside the main code or handled securely.
    * In `main.ino`, replace `"YOUR_SSID"` and `"YOUR_PASSWORD"` with your actual WiFi network name and password:
        ```c++
        const char* ssid = "YOUR_SSID";       // REPLACE with your WiFi SSID
        const char* password = "YOUR_PASSWORD"; // REPLACE with your WiFi password
        ```
        *(If you implemented the `secrets.h` method, explain that here: "Create a `secrets.h` file in the same directory with `#define WIFI_SSID "your_ssid"` and `#define WIFI_PASSWORD "your_password"`.")*
6.  **Upload Code:** Click the "Upload" button in the Arduino IDE to compile and upload the code to your ESP32.
7.  **Monitor Serial Output:** Open the Serial Monitor (Tools > Serial Monitor) at 115200 baud. You should see the ESP32 connecting to WiFi and eventually displaying its assigned IP address.

## Usage

1.  **Find IP Address:** Note the IP address displayed in the Serial Monitor (e.g., `192.168.1.100`).
2.  **Access Web Interface:** Open a web browser on a device connected to the **same local WiFi network** as your ESP32.
3.  **Enter IP Address:** In the browser's address bar, type the IP address you noted (e.g., `http://192.168.1.100/`) and press Enter.
4.  **View Readings:** You should see a web page displaying the current temperature and humidity readings from your DHT11 sensor, which will auto-refresh every 5 seconds.

## Code Explanation (Optional, but good for complex projects)

* Briefly explain key sections of your code, e.g., how the WiFi connection is established, how sensor data is read, and how the HTML is generated.

## Contributing

Feel free to fork this repository, make improvements, and submit pull requests.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---
**Disclaimer:** This project is for educational purposes and basic monitoring. For critical applications, consider more robust sensor modules and data handling.