#include <Wire.h>
#include <RTClib.h>

#define SDA_PIN 21
#define SCL_PIN 22
#define BUZZ_TRIG_1 34 
#define BUZZ_TRIG_2 35 

RTC_DS3231 rtc;

void setup() {
  Serial.begin(115200);

  Wire.begin(SDA_PIN, SCL_PIN);

  pinMode(BUZZ_TRIG_1, OUTPUT);
  pinMode(BUZZ_TRIG_2, OUTPUT);
  
  digitalWrite(BUZZ_TRIG_1, LOW);
  digitalWrite(BUZZ_TRIG_2, LOW);

  if (!rtc.begin()) {
    while (1);
  }

  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  chirp();
}

void loop() {
  DateTime now = rtc.now();

  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);

  if (now.second() == 0) {
    chirp();
    delay(1000); 
  }

  delay(1000);
}

void chirp() {
  digitalWrite(BUZZ_TRIG_1, HIGH);
  digitalWrite(BUZZ_TRIG_2, HIGH);
  delay(100);
  digitalWrite(BUZZ_TRIG_1, LOW);
  digitalWrite(BUZZ_TRIG_2, LOW);
}
