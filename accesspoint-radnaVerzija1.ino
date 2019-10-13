#include <ESP8266WiFi.h>

WiFiServer server(80);
IPAddress IP (192,168,4,15);
IPAddress mask = (255,255,255,0);

byte ledPin = 2;
int D1 = 5;
int D0 = 16;

void setup()
{
  pinMode (D1, OUTPUT);
  pinMode (D0, INPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("AirsoftApp","");
  WiFi.softAPConfig(IP,IP, mask);
  server.begin();
  pinMode (ledPin, OUTPUT);
  Serial.println();
  Serial.println("AirsoftAPP.ino");
  Serial.println("Server started.");
  Serial.print("IP:"); Serial.println(WiFi.softAPIP());
  Serial.print("MAC:"); Serial.println(WiFi.softAPmacAddress());
}
void loop()
{
  WiFiClient client = server.available();
  if (!client) {return;}
  digitalWrite(ledPin, LOW);
  String request = client.readStringUntil('\b');
  String stanje = client.readStringUntil('\b');
  Serial.println("*****************");
  Serial.println("Poslato na server" + request);
  Serial.print("Poslato klijentu: ");
  Serial.println(client.println(request + "ca" + "\r"));
  digitalWrite(ledPin, HIGH);
  Serial.printf("Povezanih kontrolera = %d\n", WiFi.softAPgetStationNum());
   
  if (stanje == "KRAJ IGRE"){
    digitalWrite(D1, HIGH);
     Serial.print("Poslato serveru: ");
     Serial.println(client.print("KRAJ IGRE\b"));
    client.println("KRAJ IGRE\b");
    }
  else{
    digitalWrite(D1, LOW);
  client.println("Igra traje\b");
  }
  client.flush();
}
