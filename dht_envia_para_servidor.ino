#include <DHT.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SPI.h>
#include <MFRC522.h>

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN,DHTTYPE);

float humidityData;
float temperatureData;
const char* ssid = "DUBVIRUS";
const char* password = "w19965882308@";
char server[] = "10.0.0.104";   

WiFiClient client;    
void setup(){
 Serial.begin(9600);
  delay(10);
  dht.begin();
  Serial.println();
  Serial.print("Conectando ao Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);


 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado!");
  dht.begin();
  Serial.println("Servidor Iniciado");
  Serial.print(WiFi.localIP());
  delay(1000);
  Serial.println("Conectando...");
 }

void loop(){ 
  
  humidityData = dht.readHumidity();
  temperatureData = dht.readTemperature();  
  delay(60000);

  Serial.print("Conectando com");
  Serial.println(server);
 
   const int httpPort = 8080; 
   if (!client.connect(server, httpPort)) {
    Serial.println("Conectado");
    return;
    }

    
String url = "/projeto/processar/sede.php?";
url += "humidity=";
url += humidityData;
url += "&temperature=";
url += temperatureData;
       
     Serial.print("Requisitando URL: ");
     Serial.println(url);

     client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                  "Host: " + server + "\r\n" +
                  "Conectando: close\r\n\r\n");

     unsigned long timeout = millis();
     while (client.available() == 0){
      if (millis () - timeout > 60000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        delay(5000);
        return;
      }
     }
     while(client.available()){
      String line = client.readStringUntil('\r');
      Serial.print(line);
     }
    Serial.println();
    Serial.println("Conexão: fechada");
    client.stop();
    delay(60000);
   }
