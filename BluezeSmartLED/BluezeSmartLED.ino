/*
  Project by Blueze or Blues follow me on https://github.com/Blues24
  Project Tree should be like this
  .
├── libraries
│   ├── ArduinoJson
│   ├── Firebase_Arduino_Client_Library_for_ESP8266_and_ESP32
│   ├── FirebaseClient
│   ├── Firebase_ESP8266_Client
│   ├── FirebaseJson
│   └── WiFiManager
└── BluezeSmartLED
    └── BluezeSmartLED.ino 

*/
#include <Arduino.h>
#if defined(ESP32)
  #include <Wifi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESP8266WebServer.h>
#endif
#include <Firebase_ESP_Client.h>
#include <FirebaseHelper.h> // Handtype custom library made by Blueze
#include <DNSServer.h>
#include <WiFiManager.h>
// Provide token generation info
#include "addons/TokenHelper.h"
// Provide Realtime Database payload
#include "addons/RTDBHelper.h"
// End of dependencies line
// Firebase configuration begin in this next line
#define API_KEY "YOUR_API_KEY" // Go through your project settings on firebase console
#define DB_URL "YOUR_DB_URL" // Go into your realtime database console and find your url 
// Define firebase objects
FirebaseData rtdb;  // Real time database object
FirebaseAuth auth;  // Firebase Auth object
FirebaseConfig config; // Firebase Config object
FirebaseHelper helper; // Firebase client Helper object

unsigned long sendDataMillis = 0;
int count = 0;
bool loginOK = false;
// End of the configuration

// WifiManager setup
WiFiServer server(80);
// Variable to store header of HTTP request
String Header;
// End of the setup
// Lamps pinout
const int out1 = 5; // D1
const int out2 = 4; // D2
const int out3 = 0; // D3
const int out4 = 14; // D5
const int builtInLED = 2; // Built in ESP8266 LED
// Lamps status
bool L1Status = false;
bool L2Status = false;
bool L3Status = false;
bool L4Status = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("\nStarting the machine");
  // Wifi manager init
  WiFiManager manager;
  // Set the access point for configure the network that we will use
  // You can change the name of the access point , look at the arrow
  //                   |
  //                   v
  if(!manager.autoConnect("FreeWifi")){
    Serial.println("Failed to connect to the network.Restarting the connection....");
    delay(300);
    ESP.restart(); // Restart the ESP if the wifi cannot connect
  }
  Serial.println("Connected to Wifi!");
  Serial.print("Listening to the network IP: ");
  Serial.println(WiFi.localIP());
  // If you want to reset the configuration each time you turn off the device uncomment the code in line 45
  //manager.resetSettings();
  // If you want custom ip check code line 47
  //manager.setAPConfig(IPAddress(Custom_Your_IP_Here), IPAddress(And_In_Here_too, IPAddress(In_Here_Too)));
  
  // Assign the firebase configuration api key and database url
  config.api_key = API_KEY;
  config.database_url = DB_URL;
  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    loginOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  // Initialize the output
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  pinMode(out3, OUTPUT);
  pinMode(out4, OUTPUT);
  pinMode(builtInLED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(helper.readBoolean(rtdb, "/LAMPS/L1", L1Status)){
    digitalWrite(out1, HIGH);
    Serial.print("Lamp 1 Status: ");
    Serial.println(L1Status ? "ON" : "OFF");
  }
  if(helper.readBoolean(rtdb, "/LAMPS/L2", L2Status)){
    digitalWrite(out2, HIGH);
    Serial.print("Lamp 2 Status: ");
    Serial.println(L2Status ? "ON" : "OFF");
  }
  if(helper.readBoolean(rtdb, "/LAMPS/L3", L3Status)){
    digitalWrite(out3, HIGH);
    Serial.print("Lamp 3 Status: ");
    Serial.println(L3Status ? "ON" : "OFF");
  }
  if(helper.readBoolean(rtdb, "/LAMPS/L4", L4Status)){
    digitalWrite(out4, HIGH);
    Serial.print("Lamp 4 Status: ");
    Serial.println(L4Status ? "ON" : "OFF");
  }
  else{
    Serial.println("Cannot find the right path!");
    Serial.println("Please provide the right path! ASAP");
  }
  delay(4500);
}
