/*Practica 1 Computacion Ubicua
  Prender Foco por Medio de Comunicacion Serial por BT*/
#include "BluetoothSerial.h" //Biblioteca para Bluetooth
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;
const int Pin = 2; //Pin para Prender el Relay o LED
void setup() {

  Serial.begin(115200);
  SerialBT.begin("Esp32"); //Iniciara la Escucha BT con el Nombre que le queramos Asignar
  Serial.println("Inicializando Dispositivo!");
  pinMode(Pin, OUTPUT); //Declaramos el Pin de Salida
  digitalWrite(Pin,HIGH);
}

void loop() {


  int dato = SerialBT.read(); //Obtenemos lo Que enviamos por Comunicacion Serial por BT
  switch (dato) {
    case '0':
      digitalWrite(Pin, 0);
      break;
    case '1':
      digitalWrite(Pin, HIGH);
      break;
  }

}
