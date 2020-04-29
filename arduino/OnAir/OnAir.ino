/*
 *  Simple HTTP get webclient test
 */

#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* WiFi Access Point *********************************/
#define WLAN_SSID       "RH10A30"
#define WLAN_PASS       "yavinendoralderaan"

#define REFRESH 20  // seconds between refresh
#define LED 13
#define PIN 12

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "192.168.1.183"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "user"
#define AIO_KEY         "key"
boolean isStreaming = false;

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'time' for subscribing to current time
Adafruit_MQTT_Subscribe onairstatus = Adafruit_MQTT_Subscribe(&mqtt, "onair1/status");

Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, PIN, NEO_GRB + NEO_KHZ800);  // change to NEO_GRBW + NEO_KHZ800 if using RGB + white strips


void onairstatuscallback(char *data, uint16_t len) {
  Serial.print("Hey we're in a onoff callback, the button value is: ");
  Serial.println(data);
  if(*data=='0'){
    isStreaming=false;
  } else {
    isStreaming=true;
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void setup() {
  boolean wifiState = false;
  strip.begin();
  onairstatus.setCallback(onairstatuscallback);
  Serial.begin(115200);
  delay(100);
    // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if(wifiState){
      colorWipe(strip.Color(0, 0, 255), 50); // Blue
    } else {
      colorWipe(strip.Color(0, 0, 30), 50); // Blue
    }
    wifiState = !wifiState;
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for time feed.
  mqtt.subscribe(&onairstatus);
  }

int value = 0;

void loop() {

   // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // this is our 'wait for incoming subscription packets and callback em' busy subloop
  // try to spend your time here:
  mqtt.processPackets(1000);
  
  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }

  Serial.print("Streaming status: "); 
  Serial.println(isStreaming);
  digitalWrite(LED, isStreaming);
  if (isStreaming) {
    colorWipe(strip.Color(255, 0, 0), 50); // Red
  } else {
    colorWipe(strip.Color(0, 0, 0), 50); // Off
  }
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 10 seconds...");
       mqtt.disconnect();
       delay(10000);  // wait 10 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
