#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h> //  use Zip files provided with this branch
#include <ArduinoJson.h> // use Zip files provided with this branch
#include <StreamString.h>
#include <EEPROM.h>

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;
WiFiClient client;

// define the number of bytes you want to access
#define EEPROM_SIZE 1

#define MyApiKey "Your_API_KEY" // TODO: Change to your webservice.lk API Key.
#define MyDeviceId "Your_Device_ID" // TODO: Change to your webservice.lk API Key.
#define MySSID "Your_WiFi_SSID" // TODO: Change to your Wifi network SSID
#define MyWifiPassword "Your_WiFi_Password" // TODO: Change to your Wifi network password

#define out1 D0

bool isConnected = false;

 
void turnOn(String deviceId) {
  if (deviceId == MyDeviceId) // Device ID of first device
  {  
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    digitalWrite(out1, HIGH);
    delay(50);
    EEPROM.write(0, 1);
    EEPROM.commit();
  }
  else {
    Serial.print("Unknown device id: ");
    Serial.println(deviceId);    
  }     
}

void turnOff(String deviceId) {
   if (deviceId == MyDeviceId) // Device ID of first device
   {  
     Serial.print("Turn off Device ID: ");
     Serial.println(deviceId);
     digitalWrite(out1, LOW);
     delay(50);     
     EEPROM.write(0, 0);
     EEPROM.commit();
   }
  else {
     Serial.print("Unknown device id: ");
     Serial.println(deviceId);    
  }
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
    
  switch(type) {
    case WStype_DISCONNECTED:
      isConnected = false;    
      Serial.printf("Disconnected from iot.webservice.lk !\n");
      break;
    case WStype_CONNECTED: {
      isConnected = true;
      Serial.printf("Connected to iot.webservice.lk at url: %s\n", payload);
      Serial.printf("Waiting for commands from iot.webservice.lk ...\n");        
      }
      break;
    case WStype_TEXT: {
        Serial.printf("%s \n",payload);
        // For Switch  types
        // https://developers.google.com/actions/smarthome/traits/onoff
        // {"deviceId":"xxx","action":"action.devices.commands.OnOff","value":{"on":true}} 
        // {"deviceId":"xxx","action":"action.devices.commands.OnOff","value":{"on":false}}

        const uint8_t size = JSON_OBJECT_SIZE(10);
        StaticJsonDocument<size> json;
        DeserializationError err = deserializeJson(json, payload);
        if (err) {
            Serial.print(F("deserializeJson() failed with code "));
            Serial.println(err.c_str());
            return;
        }

        const char *action = json["action"];
        const char *deviceId = json ["deviceId"];   
        if (strcmp(action, "setPowerState") == 0) {
            
            const char *value = json ["value"];
            Serial.println(value); 
            
            if(strcmp(value, "ON") == 0) {
                turnOn(deviceId);
            } else {
                turnOff(deviceId);
            }
        }
        else if (strcmp(action, "test") == 0) {
            Serial.println("Received test command from iot.webservice.lk");
        }
      }
      break;
    case WStype_BIN:
      Serial.printf("Get binary length: %u\n", length);
      break;
    case WStype_PING:
      Serial.printf("WStype_PING sent\n");
      break;    
    case WStype_PONG:
      Serial.printf("WStype_PONG received\n");
      break;
    default:
      Serial.printf("Get default payload: %s\n", payload);
      break;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(out1, OUTPUT);
  
  EEPROM.begin(EEPROM_SIZE);
  boolean saved_state =  EEPROM.read(0);
  if(saved_state==1){
    digitalWrite(out1, HIGH);
    delay(50);
  }
  else {
    digitalWrite(out1, LOW);
    delay(50);
  }
  
  WiFiMulti.addAP(MySSID, MyWifiPassword);
  Serial.println();
  Serial.print("Connecting to Wifi: ");
  Serial.println(MySSID);  

  // Waiting for Wifi connect
  while(WiFiMulti.run() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  if(WiFiMulti.run() == WL_CONNECTED) {
    Serial.println("");
    Serial.print("WiFi connected. ");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }

  // server address, port and URL
  webSocket.begin("iot.webservice.lk", 8080, "/");

  // event handler
  webSocket.onEvent(webSocketEvent);
  webSocket.setAuthorization('"'+MyApiKey+'"', MyDeviceId);
  
  // try again every 5000ms if connection has failed
  // If you see 'class WebSocketsClient' has no member named 'setReconnectInterval' error update arduinoWebSockets
  webSocket.setReconnectInterval(5000);

  webSocket.enableHeartbeat(15000, 3000, 2);
}

void loop() {
  webSocket.loop();  
}
