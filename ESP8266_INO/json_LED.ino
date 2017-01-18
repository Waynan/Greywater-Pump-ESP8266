#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

const char* ssid     = "*****";  
const char* password = "******";

const char* host     = "*******"; // Your domain  
String path          = "/ESP8266/light.json";  
String path2         = "/ESP8266/ESPCONTROL.php"; 
const int pin        = 13;
const int buttonPin = 0;
boolean switchState;


void setup() {  
  pinMode(pin, OUTPUT); 
 // pinMode(pin, LOW);
  pinMode(buttonPin, INPUT); 
  digitalWrite(buttonPin, HIGH);
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);
  Serial.begin(115200);

  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected"); 
 //delay(1000); 
 Serial.println("IP address: ");
 Serial.print(WiFi.localIP());
}

void loop() {  
  
    WiFiClient client;
   Serial.print("connecting to ");
  Serial.println(host);
  
   const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
   //button read
   int reading = digitalRead(buttonPin);

    if (reading == LOW)
    {
    Serial.println("button pressed");
    digitalWrite(BUILTIN_LED, LOW);
    
      if (switchState == HIGH)
        {
      client.print(String("GET ") + path2 + "?light=off" + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: keep-alive\r\n\r\n");
      Serial.println("turning LED OFF");
      delay(500); // wait for server to respond
        }
      if (switchState == LOW)
       {
        client.print(String("GET ") + path2 + "?light=on" + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: keep-alive\r\n\r\n");
      Serial.println("turning LED ON");
      delay(500); // wait for server to respond  
       } 
      digitalWrite(BUILTIN_LED, HIGH); 
      delay(500);  
    }
  //button read end
  client.print(String("GET ") + path + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: keep-alive\r\n\r\n");

  delay(500); // wait for server to respond

  // read response
  String section="header";
  while(client.available()){
    String line = client.readStringUntil('\r');
    // Serial.print(line);
    // we’ll parse the HTML body here
    if (section=="header") { // headers..
      Serial.print(".");
      if (line=="\n") { // skips the empty space at the beginning 
        section="json";
      }
    }
    else if (section=="json") {  // print the good stuff
      section="ignore";
      String result = line.substring(1);
      
      // Parse JSON
      int size = result.length() + 1;
      char json[size];
      result.toCharArray(json, size);
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& json_parsed = jsonBuffer.parseObject(json);
      if (!json_parsed.success())
      {
        Serial.println("parseObject() failed");
        return;
      }

      // Make the decision to turn off or on the LED
      if (strcmp(json_parsed["light"], "on") == 0) {
        digitalWrite(pin, HIGH); 
        switchState = HIGH;
        Serial.println("LED ON");
      }
      else {
        digitalWrite(pin, LOW);
        switchState = LOW;
        Serial.println("led off");
      }
    }
  }
  Serial.print("closing connection. ");
}
