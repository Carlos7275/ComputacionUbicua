//Practica 4 Prender Foco con Alexa
#include <WiFi.h>
#include <Espalexa.h>

int Led = 2; //Indicamos el Led para Depuracion
int Foco = 4; //Indicamos el Pin para prender el foco
const char* ssid = "Fam Sandoval Lizarraga";
const char* password = "Sandovallizarraga7275";
//const char* ssid = "RedChila";
//const char* password = "123456789";
Espalexa alexita; 

void FuncionFoco(uint8_t brightness); //Prototipo de Funcion que prende el foco
//Conecta al Wifi
void ConectarWifi() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");
    Serial.println("Conectando a Red Wifi");
    while (WiFi.status() != WL_CONNECTED) {
      digitalWrite(Led, 1);
      delay(500);
      digitalWrite(Led, 0);
      delay(500);
      Serial.print(".");
    }
    Serial.print("Conectado a ");
    Serial.println(ssid);
    Serial.print("Direccion IP: ");
    Serial.println(WiFi.localIP());
    
  }
}
void setup() {
  Serial.begin(115200);
  pinMode(Led, OUTPUT); //Indicamos los Pines de Salida
  pinMode(Foco, OUTPUT);
  digitalWrite(Foco, 1); //Apagamos el Foco por Default
  ConectarWifi();
  alexita.addDevice("Foco", FuncionFoco); //Añadimos el Dispositivo para que lo reconozca alexa
  alexita.begin();
}

void loop() {
  ConectarWifi();
  alexita.loop();
  delay(1);
}

void FuncionFoco(uint8_t brightness) {
  Serial.print("Funcion Foco - ");

  if (brightness) {
    digitalWrite(Foco, 0);
    Serial.println(" Encender ");
  }
  else {
    digitalWrite(Foco, 1);
    Serial.println(" EApagar ");
  }
}
