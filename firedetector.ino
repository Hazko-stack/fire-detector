#define BLYNK_TEMPLATE_ID "TMPL66YX1Cb1d"
#define BLYNK_TEMPLATE_NAME "Fire Detector"
#define BLYNK_AUTH_TOKEN "0UyQY9t1dA7nbEi_5lox85pg4tzNXTvv"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial

int flameSensor = D6;   
int buzzer = D5;       

char ssid[] = "Home1"; 
char pass[] = "cucidulu";

BlynkTimer timer;

void checkFlame() {
  int flameValue = digitalRead(flameSensor);
  Serial.print("Flame Detected: ");
  Serial.println(flameValue == LOW ? "YES" : "NO");

  if (flameValue == LOW) {
    digitalWrite(buzzer, HIGH);         // Nyalakan buzzer
    Blynk.virtualWrite(V0, 1);          // Kirim status api = ada
  } else {
    digitalWrite(buzzer, LOW);          // Matikan buzzer
    Blynk.virtualWrite(V0, 0);          // Kirim status api = aman
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(flameSensor, INPUT);
  pinMode(buzzer, OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(500L, checkFlame); // Cek setiap 500ms
}

void loop() {
  Blynk.run();
  timer.run();
}
