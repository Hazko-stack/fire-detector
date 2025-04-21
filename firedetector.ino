#define BLYNK_TEMPLATE_ID "TMPL66YX1Cb1d"
#define BLYNK_TEMPLATE_NAME "FIre Detector"
#define BLYNK_AUTH_TOKEN "0UyQY9t1dA7nbEi_5lox85pg4tzNXTvv"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_PRINT Serial

int mq2 = 34;
int buzzer = 13;
int gasThreshold = 1000;

char ssid[] = "Wokwi-GUEST"; 
char pass[] = "";
BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  pinMode(mq2, INPUT);
  pinMode(buzzer, OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  int gasValue = analogRead(mq2);
  Serial.print("Gas Value: ");
  Serial.println(gasValue);

  if (gasValue > gasThreshold) {
    digitalWrite(buzzer, HIGH);
    Blynk.virtualWrite(V0, 1);
  } else {
    digitalWrite(buzzer, LOW);
    Blynk.virtualWrite(V0, 0);
  }

  Blynk.virtualWrite(V1, gasValue);

  delay(500);
}
