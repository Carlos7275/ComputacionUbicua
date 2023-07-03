
#define timeSeconds 5
const int led = 2;
const int motionSensor = 14;
unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;
boolean motion = false;
int AlarmStatus=13;

boolean alarmFlag = digitalRead(AlarmStatus);
boolean debug=false;

void IRAM_ATTR detectsMovement() {
  digitalWrite(led, HIGH);
  startTimer = true;
  lastTrigger = millis();
}
