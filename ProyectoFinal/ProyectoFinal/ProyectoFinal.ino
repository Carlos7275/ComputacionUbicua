#include <BlynkSimpleEsp32.h>
#include <WiFiManager.h>
#include "HttpRequest.h"
#include "sensorMotion.h"

#define BLYNK_AUTH_TOKEN "c2pnq46Hpkr9hvAHb9PAkgaKj4Q694LW"

void setup()
{
    Serial.begin(115200);
    pinMode(led, OUTPUT);
    digitalWrite(led, LOW);
    pinMode(AlarmStatus, OUTPUT);
    pinMode(AlarmStatus, LOW);
    WiFi.mode(WIFI_STA);
    WiFiManager wm;
    bool res;
    // wm.resetSettings();
    res = wm.autoConnect("Alarmas"); // password protected ap

    if (!res)
    {
        Serial.println("Fallo al Conectar");
        wm.resetSettings();
        // ESP.restart();
    }
    else
    {
        Serial.println("Sistema de Alarma para Casas \nEstado de la Alarma:" + (String)alarmFlag);
        ;
        Blynk.begin(BLYNK_AUTH_TOKEN, WiFi.SSID().c_str(), WiFi.psk().c_str());
        pinMode(motionSensor, INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);
    }
}

void InputAlarmManuallyDebug()
{
    Serial.flush();
    if (Serial.available() > 0)
    {
        alarmFlag = Serial.read();
        Serial.println("Estatus de la Alarma:" + (String)alarmFlag);
    }
}

void PirDetected()
{
    if (debug)
        Serial.println("Valor del Sensor" + (String)digitalRead(motionSensor));
    if (alarmFlag)
    {
        now = millis();
        if ((digitalRead(led) == HIGH) && (motion == false))
        {
            Serial.println("\nMovimiento Detectado por PIR");
            send_whatsapp_message("*Alerta*\n¡Se Detecto un Movimiento en su hogar!!!!");
            send_telegram_message("*Alerta*\n¡Se Detecto un Movimiento en su hogar!!!!");
            motion = true;
        }
        if (startTimer && (now - lastTrigger > (timeSeconds * 1000)))
        {

            Serial.println("\nEl movimiento ha parado");
            digitalWrite(led, LOW);
            startTimer = false;
            motion = false;
        }
    }
}
void loop()
{
    Blynk.run();
    Serial.println(digitalRead(AlarmStatus));
    // InputAlarmManuallyDebug();
    PirDetected();
}
