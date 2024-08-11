// ESP32 ->   Wi-Fi A/B/G/N

#include <WiFi.h>
#define ledAlert 23

String ssid = "JUMENTO BRANCO";
String password = "banana3338";

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ledAlert, OUTPUT);
  Serial.begin(9600);
  Serial.print("Conexão estabelecida");
  Serial.println(WiFi.localIP());
}

void loop() {

  if(WiFi.status() != WL_CONNECTED){
    digitalWrite(ledAlert,HIGH);
    VerificarConexao();
    digitalWrite(ledAlert,LOW);
  }
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
}

void VerificarConexao(){
  while (WiFi.status() != WL_CONNECTED){
    Serial.print("Estabilizando conexao");
    WiFi.begin(ssid,password);
    delay(5000);
  }
  Serial.println("Conexao estabilizada - ");
  Serial.println(WiFi.localIP());
}