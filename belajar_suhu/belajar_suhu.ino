#include "DHT.h"

#define DHTPIN 2        // Pin data DHT22 terhubung ke pin 2
#define DHTTYPE DHT22   // Tipe sensor DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHT22 sensor mulai...");
  dht.begin();
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  delay(5000); // Tunggu 2 detik antar pembacaan

  float humid = dht.readHumidity();
  float temp = dht.readTemperature(); // Celsius

  if (isnan(humid) || isnan(temp)) {
    Serial.println("Gagal membaca dari sensor DHT22");
    return;
  }

  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.println("Humidity: " + String(humid) + "% , Temp: " + String(temp) + "°C");

}