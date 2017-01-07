#include <ESP8266WiFi.h>
 
#define IFTTT_MAX_SIZE_STRING    512
 
const char* ssid     = "";
const char* password = "";
  
const char* host = "maker.ifttt.com";
  
void setup() {
  Serial.begin(115200);
  pinMode(12, OUTPUT);
  delay(100);
  
  // We start by connecting to a WiFi network
  
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
   // Connect to IFTTT
  Serial.print("connecting to ");
  Serial.println(host);
    // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
 
  // This will send POST to IFTTT server
  char str[IFTTT_MAX_SIZE_STRING] = {0};
  char v1[16] = "12345";
  char v2[16] = "";
  char v3[16] = "";
  char header[100] = "POST /trigger/{event_name}/with/key/du491ktvl_hU8aOLNO6zB8 HTTP/1.1\r\n";
  const char * host = "Host: maker.ifttt.com\r\n";
  char contentLen[50] = {0};
  const char * contentType = "Content-Type: application/json\r\n\r\n";
  char valueData [150] = {0};
  sprintf(valueData,"{\"value1\":\"%s\",\"value2\":\"%s\",\"value3\":\"%s\"}\r\n",v1,v2,v3);
  sprintf(contentLen,"Content-Length: %d\r\n",strlen(valueData));
  sprintf(str,"%s%s%s%s%s",header,host,contentLen,contentType,valueData);
   
  client.print(str);
}

  
void loop() {
  digitalWrite(12, HIGH);
  delay(500);
  digitalWrite(12, LOW);
  delay(500);
}
