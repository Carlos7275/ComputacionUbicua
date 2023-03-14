
//#include "UbidotsMicroESP8266.h"
// Este archivo incluye una actualizacion de las librerias de Ubidots y observaras
// al conectarte a Ubidots que se crea otro dispostivo (Device) automaticamente
// tienes que configurar las etiquetas segun el nuevo dispositivo que se crea
// y adicionar la variable var_led  .... todo lo demás es identico 

#include "Ubidots.h"

#define DEVICE  "esp32carlitos"  // Put here your Ubidots device label
#define TOKEN  "BBFF-9V4cjjHoNNiDhOnH3GyD2VG705kunN"  // Put here your Ubidots TOKEN
#define VARIABLE  "PrenderFoco"  // Put here your Ubidots variable label


#define WIFISSID "RedChila" // Put here your Wi-Fi SSID
#define PASSWORD "cincomiamor"// Put here your Wi-Fi password

Ubidots client(TOKEN);
const byte  Pin_led = 2;

void setup() {
    Serial.begin(115200);
    client.wifiConnect(WIFISSID, PASSWORD);
    pinMode(Pin_led, OUTPUT);
    digitalWrite(Pin_led, LOW); 
}

void loop() 
{
    float Valor_Led = client.get(DEVICE, VARIABLE);
    if (Valor_Led != ERROR_VALUE){
      Serial.print(F(">>>>>>>>> VALOR OBTENIDO POR EL LED: "));
      Serial.println(Valor_Led);

     if (Valor_Led==1){      
      digitalWrite(Pin_led, HIGH);
      }else
      {
        digitalWrite(Pin_led, LOW);
      }
      
    }else{
      Serial.println(F("Error obteniendo Valor_Led"));
    }
   
    delay(500);
}
