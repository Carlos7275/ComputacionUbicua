#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <WiFiClient.h>
int pin = 2;
char auth[] = "xVJUROGu7RoCUpdZKmUq-V7GB4ylUaU7";       // You should get Auth Token in the Blynk App.
#define WIFISSID "Fam Sandoval Lizarraga" // Put here your Wi-Fi SSID
#define PASSWORD "Sandovallizarraga7275"// Put here your Wi-Fi password

void setup() {  
  pinMode(pin, OUTPUT); 
  pinMode(pin, HIGH);
  Serial.begin(115200);
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(WIFISSID);
  WiFi.begin(WIFISSID, PASSWORD);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  Serial.println("WiFi connected");  
  Blynk.begin(auth, WIFISSID, PASSWORD);
}
void loop(){
    Blynk.run();
}
 
