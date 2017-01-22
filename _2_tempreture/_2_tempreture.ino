/**
 * 温度を取得して、シリアルプロッタへ出力するプログラム
 */
#include "DHT.h"
#define DHTPIN 12 //ピン指定
#define DHTTYPE DHT11 //センサーの種類
// version 1.2.3 needed
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); 
  Serial.println("DHT11 test!"); 
  dht.begin();
}

void loop() {
  delay(300);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  //シリアルプロッタ用出力
  Serial.print(h);
  Serial.print(',');//複数値をプロットする場合は','で区切る
  Serial.println(t); //改行で1データの区切り
  /* *
  //シリアルモニタ出力
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.println(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C ");
  /**/
}
