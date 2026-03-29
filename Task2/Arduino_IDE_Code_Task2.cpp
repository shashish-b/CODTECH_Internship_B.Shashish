"Task-2: Demonstrate Switching lights on /off remotely using NodeMCU as part of home automation using bluetooth"

#include<ESP8266WiFi.h>
#include"Adafruit_MQTT.h"
#include"Adafruit_MQTT_Client.h"

#define ledPin D4
#define WLAN_SSID "$wifi_name$"
#define WLAN_PASS "$password$"

#define AIO_SERVER        "io.adafruit.com"
#define AIO_SERVERPORT    1883
#define AIO_USERNAME      "$xxxxx$"
#define AIO_KEY           "$yyyyy$"

WiFiClient client;

Adafruit_MQTT_Client mqtt(&client,AIO_SERVER,AIO_SERVERPORT,AIO_USERNAME,AIO_KEY);

Adafruit_MQTT_Subscribe onoffbutton= Adafruit_MQTT_Subscribe(&mqtt,"$xxxxx$/feeds/$feed_name$",MQTT_QOS_1);

void onoffcallback(char *data,uint16_t len){
  Serial.print("obtained value:");
  Serial.println(data);
  if(String(data).equals("ON")){
    digitalWrite(ledPin,HIGH);
    }else{
      digitalWrite(ledPin,LOW);
      }
}
void setup() {
  pinMode(ledPin,OUTPUT);
  Serial.begin(115200);
  delay(10);
  Serial.println("Adafruit MQTT Demo");
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID,WLAN_PASS);
  while(WiFi.status() !=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  onoffbutton.setCallback(onoffcallback);
  mqtt.subscribe(&onoffbutton);
}


void loop()
{
  MQTT_connect();
  mqtt.processPackets(10000);
  delay(1000);
}
void MQTT_connect(){
if(mqtt.connected()){
  return;
}
Serial.println("Connecting to MQTT.....");
while(mqtt.connect() !=0){
  Serial.println("retrying MQTT connection in 10 seconds...");
  mqtt.disconnect();
  delay(200);
}
Serial.println("MQTT Conncted!");
}

 
