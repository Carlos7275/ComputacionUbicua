
#include <WiFi.h>
#include <HTTPClient.h>
#include <UrlEncode.h>
//Credenciales de la Red
#define WIFISSID "Fam Sandoval Lizarraga" 
#define PASSWORD "Sandovallizarraga7275"
//Token para Whatbot
#define api_key 38236040
String mobile_number = "5216682566496";
// Token para Telegram
String chat_id = "1012418934";
String api_key2 = "70637498";
#define timeSeconds 5
const int led = 2;
const int motionSensor = 14;
unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;
boolean motion = false;
boolean alarmFlag = true;
boolean debug=false;
void send_whatsapp_message(String message){
  String API_URL = "https://api.whatabot.net/whatsapp/sendMessage?apikey=";
  API_URL+= (String)api_key + "&text="+ urlEncode(message) +"&phone="+mobile_number;
  //Serial.println(API_URL);
  
  HTTPClient http;
  http.begin(API_URL);

  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int http_response_code = http.GET();
  if (http_response_code == 200){
    Serial.print("Mensaje Enviado con Exito");
  }
  else{
    Serial.println("Error al Enviar el Mensaje");
    Serial.print("Codigo de Respuestaa HTTP: ");
    Serial.println(http_response_code);
  }
  http.end();
}
void send_telegram_message(String message){
  String API_URL = "https://api.whatabot.net/telegram/sendMessage?apikey=";
  API_URL+= api_key2 + "&text="+ urlEncode(message) +"&chatId="+chat_id;
  HTTPClient http;
  http.begin(API_URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int http_response_code = http.GET();
  if (http_response_code == 200){
    Serial.println("El mensaje de telegram se envio correctamente");
  }
  else{
    Serial.println("Error al Enviar el Mensaje");
    Serial.print("Codigo de Respuesta HTTP:");
    Serial.println(http_response_code);
  }
  http.end();
}
void IRAM_ATTR detectsMovement() {
  digitalWrite(led, HIGH);
  startTimer = true;
  lastTrigger = millis();
}

void setup() {
  Serial.begin(115200);
  Serial.println("Sistema de Alarma para Casas \nEstado de la Alarma:" + (String)alarmFlag);
 
  pinMode(motionSensor, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  Serial.print("Conectando a Red ");
  Serial.println(WIFISSID);
  WiFi.begin(WIFISSID, PASSWORD);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  Serial.println("Conexion Exitosa");
}
void InputAlarmManuallyDebug(){
  Serial.flush();
  if(Serial.available()>0){
    alarmFlag=Serial.read();
    Serial.println("Estatus de la Alarma:"+(String)alarmFlag);
  }
}

void PirDetected() {
  if(debug)
  Serial.println("Valor del Sensor"+(String)digitalRead(motionSensor));
  if (alarmFlag) {
    now = millis();
    if ((digitalRead(led) == HIGH) && (motion == false)) {
      Serial.println("\nMovimiento Detectado por PIR");
      send_whatsapp_message("*Alerta*\n¡Se Detecto un Movimiento en su hogar!!!!");
      send_telegram_message("*Alerta*\n¡Se Detecto un Movimiento en su hogar!!!!");
      motion = true;
    }
    if (startTimer && (now - lastTrigger > (timeSeconds * 1000))) {
       
      Serial.println("\nEl movimiento ha parado");
      digitalWrite(led, LOW);
      startTimer = false;
      motion = false;
    }
  }

}
void loop() {
 // InputAlarmManuallyDebug();
  PirDetected();
}
