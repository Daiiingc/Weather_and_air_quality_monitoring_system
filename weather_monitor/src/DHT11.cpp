#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 5     // Chân kết nối cảm biến DHT
#define DHTTYPE DHT11   // DHT11

// Cấu hình thông số cho DHT11
DHT dht(DHTPIN, DHTTYPE);

void DHT11_Setup()
{
  Serial.println(F("DHTxx test!"));
  dht.begin();
}

float Read_Temp()
{
    // Đọc giá trị nhiệt độ (độ C) của DHT11
    float t = dht.readTemperature();
    return t;
}

float Read_Humidity()
{
    // Đọc giá trị độ ẩm của DHT11
    float h = dht.readHumidity();
    return h;
}