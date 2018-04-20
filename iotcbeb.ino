#include <DHT.h>  // Including library for dht

#include <ESP8266WiFi.h>
 
String apiKey = "GZFXJXTOC32M9F0Q";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "cbeb";     // replace with your wifi ssid and wpa2 key
const char *pass =  "cbebteste";
const char* server = "api.thingspeak.com";

#define DHTPIN 0          //pin where the dht11 is connected
 
DHT dht(DHTPIN, DHT22);


WiFiClient client;
 
void setup() 
{
       
       dht.begin();
       WiFi.begin(ssid, pass);
       pinMode(12, OUTPUT);
       pinMode(13, OUTPUT);
 
}
 
void loop() 
{
  
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      
                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(h);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
                        }
                        client.stop();
                          if((t>34 && t<34.4) || (t<35 && t>34.6)){
                          digitalWrite(12, HIGH); }
                          else{
                            digitalWrite(12, LOW);
                          }
                          if(t<34 || t>35){
                          digitalWrite(13, HIGH);}
                          else{
                          digitalWrite(13, LOW);}
                          
          

delay(15000); }
