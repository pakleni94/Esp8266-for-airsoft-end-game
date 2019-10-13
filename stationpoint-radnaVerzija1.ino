#include <ESP8266WiFi.h>
byte ledPin = 2;
char ssid[] = "AirsoftApp";           // SSID of your AP
char pass[] = "";         // password of your AP
IPAddress server(192,168,4,15);     // IP address of the AP
WiFiClient client;
WiFi.localIP (192,168,4,16);
IPAddress mask = (255,255,255,0);

int D0 = 16;
int D1 = 5;
int kraj = LOW;
void setup() {
  pinMode (D0, INPUT);
  pinMode (D1, OUTPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin("AirsoftApp", "" );           // connects to the WiFi AP
  Serial.println();
  Serial.println("Connection to the AP");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();
  Serial.println("Connected");
  Serial.println("AirsoftAPP.ino");
  Serial.print("LocalIP:"); Serial.println(WiFi.localIP());
  Serial.println("MAC:" + WiFi.macAddress());
  Serial.print("Gateway:"); Serial.println(WiFi.gatewayIP());
  Serial.print("AP MAC:"); Serial.println(WiFi.BSSIDstr());
  pinMode(ledPin, OUTPUT);
}

void loop() {
 kraj = digitalRead(D0);
    client.connect(server, 80);
  digitalWrite(ledPin, LOW);
  Serial.println("********************************");
  Serial.println(client.print("Saljem ti: \r"));
  String answer = client.readStringUntil('\b');
  Serial.println("Sa servera: " + answer);
  if (kraj == HIGH){
     Serial.print("Poslato serveru: ");
     Serial.println(client.print("KRAJ IGRE\b"));
    client.println("KRAJ IGRE\b");
    digitalWrite (D1, HIGH);
    }
  else{
  client.println("Igra traje \b");
     Serial.println(client.print("Igra traje\b"));
  digitalWrite (D1, LOW);
  }
  
   client.flush();
  digitalWrite(ledPin, HIGH);
  client.stop();
}
