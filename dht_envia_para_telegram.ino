#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include "DHT.h"


// Initialize Wifi connection to the router
char ssid[] = "DUBVIRUS";     // your network SSID (name)
char password[] = "w199658823086@"; // your network key

// Initialize Telegram BOT
#define BOTtoken "1316762648:AAHrT944-8qKB6fMx9eJ3kaI6U-M7M0NDZk"  // your Bot Token (Get from Botfather)

#define DHTPIN 3
#define DHTTYPE DHT22

DHT dht11 (DHTPIN, DHTTYPE);

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done
bool Start = false;

float temp ;
float humid;
String chat_id1;

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;
    chat_id1 = chat_id;

    float humid= dht11.readHumidity();    
    float temp = dht11.readTemperature(); 

    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "guest";

    if (text == "/send_test_action") {
        bot.sendChatAction(chat_id, "typing");
        delay(4000);
        bot.sendMessage(chat_id, "Did you see the action message?");

        // You can't use own message, just choose from one of bellow

        //typing for text messages
        //upload_photo for photos
        //record_video or upload_video for videos
        //record_audio or upload_audio for audio files
        //upload_document for general files
        //find_location for location data

        //more info here - https://core.telegram.org/bots/api#sendchataction
    }

    if (text == "/start") {
      String welcome = "Welcome to Universal Arduino Telegram Bot library, " + from_name + ".\n";
      welcome += "This is Chat Action Bot example.\n\n";
      welcome += "/send_test_action : to send test chat action message\n";
      bot.sendMessage(chat_id, welcome);
    }

    if (text == "SUHU RUANG") {
      String suhu = "--SUHU RUANG--\n\n";
      suhu +="1.  Suhu Ruang A       :   ";
      suhu +=   float(temp);
      suhu += " ⁰C\n";
      suhu +="     Humidity Ruang A:   ";
      suhu +=   float(humid);
      suhu += " %\n";
      bot.sendMessage(chat_id, suhu, "");
      }

    
  }
}


void setup() {
  client.setInsecure();
  Serial.begin(9600);
  dht11.begin();

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  pinMode(3, INPUT);
}

void loop() {
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

     float humid= dht11.readHumidity();    
     float temp = dht11.readTemperature(); 

     if (temp > 30.00) {
    bot.sendChatAction(chat_id1, "Sedang mengetik...");
    String suhu = "Waspada Suhu Ruang A\n";
    suhu +="Suhu :";
    suhu +=int(temp);
    suhu +=" ⁰C\n";
    suhu +="Humidity :";
    suhu +=int(humid);
    suhu +=" %\n";
    bot.sendMessage(chat_id1, suhu, "");
    Serial.print("Mengirim data sensor ke telegram");
    }


    Bot_lasttime = millis();
      Serial.print("Suhu: ");
  Serial.println(temp);
  Serial.print(" ");
  Serial.print("Humidity: ");
  Serial.println(humid);
  delay(2000);
  }

}
