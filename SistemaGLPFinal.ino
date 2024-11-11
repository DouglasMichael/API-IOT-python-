#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define GasA 35
#define GasD 34

// Telegram BOT Token (Get from Botfather)
#define BOT_TOKEN "8176560619:AAG9a6K3XA-gbSpwyFxdJvvOX0KQEFd2jS0"

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);


const char *ssid = "Michael";
const char *password = "luci160172";

char jsonOutput[1100];

void setup()
{
  pinMode(GasD, INPUT);
  Serial.begin(115200);

  // attempt to connect to Wifi network:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int ValorD = digitalRead(GasD);
  int ValorA = analogRead(GasA);

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient client;

    Serial.println("Enviando para: ");
    Serial.println("http://192.168.15.22:3000/api/v1/sensor/");
    Serial.print("Valor Digital: ");
    Serial.println(ValorD);
    Serial.print("Valor analógico: ");
    Serial.println(ValorA);
    
    client.begin("http://192.168.15.22:3000/api/v1/sensor/");  //HTTP
    client.addHeader("Content-Type","application/json");

    const size_t CAPACITY = JSON_OBJECT_SIZE(10);
    StaticJsonDocument<CAPACITY> doc;

    JsonObject object = doc.to<JsonObject>();
    

    if (ValorA > 1000 || ValorD == 0) {  
      object["tipo"] = "Alerta";
      object["dados"] = ValorA;
      bot.sendMessage(String(8073277275), "ALERTA!!!\n\n O dispositivo ESP32 detectou um vazamento de gás. Por favor, verifique a situação imediatamente para garantir a segurança do local.");
    }else{
      object["tipo"] = "Estável";
      object["dados"] = ValorA;
    }

    serializeJson(doc, Serial);
    serializeJson(doc, jsonOutput);

    int httpCode = client.POST(String(jsonOutput));

    if (httpCode > 0){
      String payload = client.getString();
      Serial.println("\nStatuscode: " + String(httpCode));
      Serial.println(payload);   

      client.end();      
    }
    else{
      Serial.println("Erro na requisição do HTTP");      
    }
  }
  else {
    Serial.println("Conexão com o WIFI perdida");
  }
   delay(5000);
}