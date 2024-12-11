#if defined(ESP32)
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
#define DEVICE "ESP32"
#elif defined(ESP8266)
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
#define DEVICE "ESP8266"
#endif

// thư viện cho module DHT11
#include "DHT11.h"
// thư viện cho module MQ135
#include "MQ135.h"
// Thư viện để giao tiếp với InfluxDb
#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>

// WiFi AP SSID
#define WIFI_SSID "AIoT Lab 2G"
// WiFi password
#define WIFI_PASSWORD "ptitlab@123"

// Địa chỉ của InfluxDb server
#define INFLUXDB_URL "http://192.168.137.153:8086"
#define INFLUXDB_TOKEN "izPAUHhBqLy0YVBj2pClyNN2LOfqTcK4DOb7X8hD__161SdPV0sste7uOiA8G8hm_GZ8RkX4fooRH2KyqcPqNg=="
#define INFLUXDB_ORG "demo"
#define INFLUXDB_BUCKET "ESP32_Sensor_Data"
// thông tin thời gian của khu vực
#define TZ_INFO "ICT"
// Khai báo phiên bản máy khách InfluxDB với chứng chỉ InfluxCloud được cấu hình sẵn
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);

// Declare Data point
Point sensor1("MQ135");
Point sensor2("Device");
Point sensor3("DHT11");

void setup() {
  Serial.begin(9600);
  
  // thiết lập wifi
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Kết nối wifi");
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  // thêm tag vào các giá trị điểm
  sensor1.addTag("sensor1", "MQ135");
  sensor3.addTag("sensor2","DHT11");

  timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");

  // Kiểm tra kết nối
  if (client.validateConnection()) {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(client.getServerUrl());
  } else {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(client.getLastErrorMessage());
  }
  DHT11_Setup();
  MQ135_Setup();
}

void loop() {
  // Đợi giữa quá trình gửi đi
  delay(2000);

  // xoá trường
  sensor1.clearFields();
  sensor2.clearFields();
  sensor3.clearFields();

  float Temp_Value = Read_Temp();
  float Humidity_Value = Read_Humidity();
  float CO2_Value = Read_CO2();

  // Kiểm tra xem giá trị có lỗi không
  if (isnan(Humidity_Value) || isnan(Temp_Value)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  if(CO2_Value < 2) CO2_Value = CO2_Value + 1;
  if(CO2_Value < 100)
  {
    CO2_Value = CO2_Value * 100;
  }else{
    CO2_Value = CO2_Value * 10;
  }

  // Lưu giá trị thành 1 giá trị điểm
  sensor1.addField("CO2", CO2_Value);
  sensor2.addField("Device", DEVICE);
  sensor2.addField("SSID", WiFi.SSID());
  sensor3.addField("Temp", Temp_Value);
  sensor3.addField("Humidity", Humidity_Value);

  // In ra dữ liệu được gửi đi
  Serial.println("Writing to database: ");
  Serial.println(sensor1.toLineProtocol());
  Serial.println(sensor2.toLineProtocol());
  Serial.println(sensor3.toLineProtocol());
  Serial.println();

  // Kiểm tra wifi còn hoạt động
  if (wifiMulti.run() != WL_CONNECTED) {
    Serial.println("Wifi connection lost");
  }

  // Gửi dữ liệu
  if (!client.writePoint(sensor1)) {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  }
  
  if (!client.writePoint(sensor2)) {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  }
  if (!client.writePoint(sensor3)) {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  }

  Serial.println("Waiting 2 second");
}

