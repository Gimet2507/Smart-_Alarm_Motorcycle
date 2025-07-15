#define BLYNK_TEMPLATE_ID "TMPL6LJBqV0X1"
#define BLYNK_TEMPLATE_NAME "IOT Motor"
#define BLYNK_AUTH_TOKEN "MgkElE3ZdTX22l-PeD1JC9-OrOh-qcTX"

#include <SPI.h>
#include <BlynkSimpleEsp8266.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>


char auth[] = "MgkElE3ZdTX22l-PeD1JC9-OrOh-qcTX"; 
char ssid[] = "tenda";       // Your WiFi SSID
char pass[] = "duakelinci";  // Your WiFi Password



// Telegram Bot Configuration
#define BOT_TOKEN "7487838311:AAHyEHN4jjg_psiEhkQl7wwiVyg7nETtJpc" // Replace with your Telegram Bot Token
#define CHAT_ID "908955551"    // Replace with your Chat ID

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

// Variables for GPS timing
unsigned long previousGPSTime = 0; // Store the last time GPS data was sent
const unsigned long gpsInterval = 100000; // 10 seconds interval

BlynkTimer timer;   

// GPS Definitions
static const int RXPin = 5, TXPin = 4; // RX: D2 - TX: D1
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps; // The TinyGPS++ object
SoftwareSerial ss(RXPin, TXPin); // The serial connection to the GPS device

// Relay and Vibration Sensor
#define RELAY1 D6 // Relay pin
#define VibSen 14 // Sensor pada pin D3

String link;

void setup() {
  // Serial communication for debugging
  Serial.begin(115200);

  // WiFi connection
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Blynk Setup
  Blynk.begin(auth, ssid, pass);
// Tunggu sampai koneksi Blynk berhasil
  while (!Blynk.connected()) {
    Serial.println("Connecting to Blynk...");
    delay(1000);
  }
  Serial.println("Connected to Blynk!");
  
  // GPS Setup
  ss.begin(GPSBaud);

  // Secure client setup for Telegram
  client.setInsecure();

  // Relay and Vibration Sensor setup
  pinMode(RELAY1, OUTPUT);
  pinMode(VibSen, INPUT);
  digitalWrite(RELAY1, LOW); // Ensure relay is off initially

  Serial.println("Setup complete!");
}

void loop() {
  Blynk.run();
  timer.run();  // Menjalankan BlynkTimer

  
  if (millis() - previousGPSTime >= gpsInterval) {// GPS Data Processing
    while (ss.available() > 0) {
      gps.encode(ss.read());
      if (gps.location.isUpdated()) {
        float latitude = gps.location.lat();
        float longitude = gps.location.lng();

        Serial.print("Latitude: ");
        Serial.print(latitude, 6);
        Serial.print(" Longitude: ");
        Serial.println(longitude, 6);

        // Create Google Maps link
       link = "https://www.google.com/maps/place/" + String(latitude, 6) + "," + String(longitude, 6);

        // Send data to Telegram
        String message = "GPS Tracing Update:\n";
       message += "Latitude: " + String(latitude, 6) + "\n";
       message += "Longitude: " + String(longitude, 6) + "\n";
        message += "Google Maps: " + link;
        bot.sendMessage(CHAT_ID, message, "");

        previousGPSTime = millis();
      }
    }
    
  }

  // Handle vibration sensor
  int vib = digitalRead(VibSen);  // Read vibration sensor
  if (vib == HIGH) {     
    Serial.println("Getaran terdeteksi, RELAY ON");
    digitalWrite(RELAY1, HIGH);
    Blynk.virtualWrite(V0, "Getaran terdeteksi");
    Blynk.virtualWrite(V1, 1);
    delay(3000);
  } else {                        // If no vibration detected
    Serial.println("Tidak ada getaran, RELAY OFF");
    digitalWrite(RELAY1, LOW);
    Blynk.virtualWrite(V0, "Getaran Tidak terdeteksi");
    Blynk.virtualWrite(V1, 0);
  }


  delay(500);
}

// Fungsi untuk memeriksa koneksi ke server Blynk
void checkConnection()
{
  if (!Blynk.connected()) {
    Serial.println("Reconnecting...");
    if (Blynk.connect()) {
      Serial.println("Reconnected!");
    } else {
      Serial.println("Reconnect failed!");
    }
  }
}
