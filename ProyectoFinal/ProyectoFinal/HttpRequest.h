
#include <HTTPClient.h>
#include <UrlEncode.h>

#define api_key 38236040
String mobile_number = "5216682566496";
// Token para Telegram
String chat_id = "1012418934";
String api_key2 = "70637498";


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
