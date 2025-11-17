#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT22
#define LED_PIN LED_BUILTIN

DHT dht(DHTPIN, DHTTYPE);

unsigned long previousMillisDHT = 0;  // waktu terakhir baca sensor
unsigned long ledOnMillis = 0;        // waktu LED terakhir dinyalakan
const long intervalDHT = 10000;        // baca DHT tiap 10 detik
const long ledDuration = 300;         // LED nyala 300 ms

bool ledOn = false;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(LED_PIN, OUTPUT);
  Serial.println("Temperature Sensor started ==================");
}

void loop() {
  unsigned long currentMillis = millis();

  // --- Baca DHT tiap 10 detik tanpa delay ---
  if (currentMillis - previousMillisDHT >= intervalDHT) {
    previousMillisDHT = currentMillis;

    float humid = dht.readHumidity();
    float temp = dht.readTemperature();

    if (isnan(humid) || isnan(temp)) {
      Serial.println("Gagal membaca sensor DHT22!");
      return;
    }

    Serial.println("Humidity: " + String(humid) + "% , Temp: " + String(temp) + "°C");
    
    // === 2. Nyalakan LED selama 300 ms ===
    digitalWrite(LED_PIN, HIGH);
    ledOn = true;
    ledOnMillis = currentMillis;
  }

  // === 3. Matikan LED setelah 300 ms ===
  if (ledOn && (currentMillis - ledOnMillis >= ledDuration)) {
    digitalWrite(LED_PIN, LOW);
    ledOn = false;
  }
  
  // Proses lain tetap bisa berjalan di sini tanpa delay
}