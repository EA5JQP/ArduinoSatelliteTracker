#include <TinyGPS++.h>        // Include TinyGPS++ library
#include <HardwareSerial.h>   // Include HardwareSerial for ESP32

TinyGPSPlus gps;              // Create a TinyGPSPlus object

HardwareSerial serialGPS(1);  // Use Serial1 for GPS communication

// Global variables to store latitude and longitude as floats
float latitude = 0.0;
float longitude = 0.0;

void gpsSetup() {
  Serial.begin(115200);       // Initialize Serial Monitor
  serialGPS.begin(9600, SERIAL_8N1, SERIAL_FULL,16);  // Initialize GPS module serial communication
  Serial.println("GPS Module with ESP32");
}

void gpsLoop() {
  while (serialGPS.available() > 0) {
    gps.encode(serialGPS.read());  // Parse GPS data
  }

  if (gps.location.isValid()) {
    latitude = gps.location.lat();  // Update latitude global variable
    longitude = gps.location.lng(); // Update longitude global variable

    Serial.print("Latitude: ");
    Serial.print(latitude, 6);      // Print latitude
    Serial.print(", Longitude: ");
    Serial.println(longitude, 6);   // Print longitude

  } else {
    Serial.println("Waiting for GPS signal...");
  }

}

