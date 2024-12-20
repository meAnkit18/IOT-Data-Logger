#define BLYNK_TEMPLATE_ID "TMPL3xd7aXgfr"
#define BLYNK_TEMPLATE_NAME "Temperature and Humidity Monitor"
#define BLYNK_AUTH_TOKEN "ztBIQ9UMOoLr2C-85MzTZJ-Ie9MyFv21"



// Include libraries
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// Blynk authentication token, WiFi credentials
 char auth[] = "ztBIQ9UMOoLr2C-85MzTZJ-Ie9MyFv21";  // Replace with your Blynk Auth Token
char ssid[] = "Ankit";         // Replace with your WiFi SSID
char pass[] = "13062004";     // Replace with your WiFi Password

// DHT sensor settings
#define DHTPIN D2  // Connect the DHT sensor to pin D2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Create a timer for periodic tasks
BlynkTimer timer;

// Function to send sensor data to Blynk and print to Serial Monitor
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // Celsius (use dht.readTemperature(true) for Fahrenheit)

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Send data to Blynk
  Blynk.virtualWrite(V0, t); // Temperature
  Blynk.virtualWrite(V1, h); // Humidity

  // Print data to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" °C    Humidity: ");
  Serial.print(h);
  Serial.println(" %");
}

void setup()
{
  // Start the Serial Monitor
  Serial.begin(115200);
  Serial.println("Connecting to Blynk...");

  // Connect to WiFi and Blynk
  Blynk.begin(auth, ssid, pass);

  // Initialize DHT sensor
  dht.begin();

  // Set a timer to send data every 2 seconds
  timer.setInterval(2000L, sendSensor);

  Serial.println("Setup complete.");
}

void loop()
{
  Blynk.run();   // Run Blynk
  timer.run();   // Run timer
}
