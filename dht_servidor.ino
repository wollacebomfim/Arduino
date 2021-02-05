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
const char* ssid = "DUBVIRUS";// 
const char* password = "w19965882308@";
//WiFiClient client;
char server[] = "10.0.0.104";   //eg: 192.168.0.222


WiFiClient client;    


void setup()
{
 Serial.begin(115200);
  delay(10);
  dht.begin();
  
  Serial.println();
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
  Serial.println(" Conectando...");
 }
void loop()
{ 
  humidityData = dht.readHumidity();
  temperatureData = dht.readTemperature(); 
  Sending_To_phpmyadmindatabase(); 
  delay(3000); // interval
 }
 void Sending_To_phpmyadmindatabase()   //CONNECTING WITH MYSQL
 {
   if (client.connect(server, 8080)) {
    Serial.println("Conectado");
    // Make a HTTP request:
    Serial.print("GET /test/dht.php?humidity=");
    client.print("GET /test/dht.php?humidity=");
    Serial.println(humidityData);
    client.print(humidityData);
    client.print("&temperature=");
    Serial.println("&temperature=");
    client.print(temperatureData);
    Serial.println(temperatureData);
    client.print(" ");
    client.print("HTTP/1.1");
    client.println();
    client.println("Host: Seu IP Local");
    client.println("Conexão: fechada");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("Conexão falhou");
  }
 }
