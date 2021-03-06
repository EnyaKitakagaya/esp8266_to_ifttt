#include <ESP8266WiFi.h>
 
#define IFTTT_MAX_SIZE_STRING    512
 
const char* ssid     = ""; //SSIDを入力
const char* password = ""; //パスワードを入力


const char* host = "maker.ifttt.com";
  
void setup() {
  Serial.begin(115200);
  pinMode(16, OUTPUT);
  delay(100);
  
  //接続開始
  
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

  post_to_ifttt();

  delay(10);
}

void post_to_ifttt(){
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
  char v1[16] = "name";//自分の名前を入れてください
  char v2[16] = "";
  char v3[16] = "";
  char header[100] = "POST /trigger/test/with/key/fULaIbddbnSvZal8xTIS3TCpKIJGEFqOIfyDaDlzF-y HTTP/1.1\r\n";
  const char * host = "Host: maker.ifttt.com\r\n";
  char contentLen[50] = {0};
  const char * contentType = "Content-Type: application/json\r\n\r\n";
  char valueData [150] = {0};
  sprintf(valueData,"{\"value1\":\"%s\",\"value2\":\"%s\",\"value3\":\"%s\"}\r\n",v1,v2,v3);
  sprintf(contentLen,"Content-Length:%d\r\n",strlen(valueData));
  sprintf(str,"%s%s%s%s%s",header,host,contentLen,contentType,valueData);

  Serial.println("start to post");
  client.print(str);
  Serial.print(str);
  Serial.println("....fin");
}

void loop() {
  digitalWrite(16, HIGH);
  delay(500);
  digitalWrite(16, LOW);
  delay(500);
}
