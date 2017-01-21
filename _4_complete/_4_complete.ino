#include <stdio.h>
#include <ESP8266WiFi.h>
// version 1.2.3 needed
#include <DHT.h>
 
#define IFTTT_MAX_SIZE_STRING    512

#define DHTPIN 5 //ピン指定
#define DHTTYPE DHT11 //センサーの種類
DHT dht(DHTPIN, DHTTYPE);
 
const char* ssid     = ""; //SSIDを入力
const char* password = ""; //パスワードを入力

const char* host = "maker.ifttt.com";
  
void setup() {
  Serial.begin(115200);
  pinMode(16, OUTPUT);
  delay(100);
  
  //接続開始
  digitalWrite(16, HIGH);
  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

//  post_to_ifttt();
  
  delay(10);
  
  dht.begin();
  digitalWrite(16, LOW);

}

void post_to_ifttt(char v1[] ,char v2[]  ,char v3[]){
  //iFTTTへの接続開始
  Serial.print("connecting to ");
  Serial.println(host);
  // WiFiClient クラスを使用
    
  WiFiClient client;
  const int httpPort = 80;//80番ポート
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
 
  // サーバーへの送信情報
  char str[IFTTT_MAX_SIZE_STRING] = {0};
  char header[100] = "POST /trigger/temperature/with/key/fULaIbddbnSvZal8xTIS3TCpKIJGEFqOIfyDaDlzF-y HTTP/1.1\r\n";
  const char * host = "Host: maker.ifttt.com\r\n";
  char contentLen[50] = {0};
  const char * contentType = "Content-Type: application/json\r\n\r\n";
  char valueData [150] = {0};
  sprintf(valueData,"{\"value1\":\"%s\",\"value2\":\"%s\",\"value3\":\"%s\"}\r\n",v1,v2,v3);
  sprintf(contentLen,"Content-Length:%d\r\n",strlen(valueData));
  sprintf(str,"%s%s%s%s%s",header,host,contentLen,contentType,valueData);

  Serial.println("start to post");
  client.print(str); // send texts to host
  Serial.print(str);
  Serial.println("....fin");
}

void loop() {
  digitalWrite(16, HIGH);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  char h_buf[16];
  char str_h[6];
  dtostrf(h , 4, 2, str_h);
  sprintf(h_buf,"%s", str_h);

  char t_buf[16];
  char str_t[6];
  dtostrf(t , 4, 2, str_t);
  sprintf(t_buf,"%s", str_t);
  
  post_to_ifttt("test",t_buf,h_buf);
  delay(60*1000);
  digitalWrite(16, LOW);
  delay(500);
}
