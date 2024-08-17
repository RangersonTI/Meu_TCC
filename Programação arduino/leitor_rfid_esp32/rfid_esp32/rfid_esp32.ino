// ESP32 ->   Wi-Fi A/B/G/N

#include <WiFi.h>
#include <SPI.h>
#include <MFRC522.h> // Biblioteca para conexao do com RFID-RC522
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
/*
Conexoes RFID-RC522

VSPI RST - RST -> 4 (BRANCO)
VSPI MOSI - MOSI -> 23 (ROXO)
VSPI MISO - MISO -> 19 (CINZA)
VSPI SCK - SCK -> 18 (AZUL)
VSPI SS - SS (SDA) -> 5 (VERDE)
VCC -> 3V (VERMELHO
GND -> GND (PRETO)

*/
#define ledAmarelo 22
#define ledVerde 21
#define ledVermelho 16
#define buzzer 2
#define RST_PIN 0
#define SS_PIN 5

MFRC522 leitor(SS_PIN, RST_PIN);
WiFiClient client;
MySQL_Connection connection(&client);
MySQL_Cursor* cursor;

const String ssid = "JUMENTO BRANCO";
const String password = "banana3338";

IPAddress addr_server(127,0,0,1);
int port = 3306;
char user[] = "root";
char key_mysql[] = "wrede";

char command[]= "INSERT INTO rfid.rfid_cad (rfid) VALUES (%s)";

void setup() {
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  leitor.PCD_Init(); //Inicia o módulo MFRC522
}

void loop() {
  digitalWrite(ledVermelho, HIGH);
  delay(500);

  if(WiFi.status() != WL_CONNECTED){
    digitalWrite(ledVermelho, LOW);
    VerificarConexao();
    delay(1000);
  }

  VerificarCard();
}

void VerificarConexao(){
  while (WiFi.status() != WL_CONNECTED){
    Serial.print("Estabilizando conexao");
    WiFi.begin(ssid,password);
    digitalWrite(ledVermelho,HIGH);
    delay(200);
    digitalWrite(ledVermelho,LOW);
    delay(200);
    digitalWrite(ledVermelho,HIGH);
    delay(200);
    digitalWrite(ledVermelho,LOW);
    delay(200);
    digitalWrite(ledVermelho,HIGH);
    delay(200);
    digitalWrite(ledVermelho,LOW);
    delay(200);
    digitalWrite(ledVermelho,HIGH);
    delay(200);
    digitalWrite(ledVermelho,LOW);
    delay(200);
  }
  digitalWrite(ledVerde,HIGH);
  delay(1000);
  digitalWrite(ledVerde,LOW);
  delay(50);
  Serial.println("Conexao estabilizada - ");
  Serial.println(WiFi.localIP());
}

// Método para verificar se há card sendo inserido

void VerificarCard(){

  String rfid_data;

  if (!leitor.PICC_IsNewCardPresent()){
    Serial.print("\nNenhum Card");
    delay(500);
    return;
  }

  if(!leitor.PICC_ReadCardSerial()){
    Serial.println("Erro de leitura");
    somAtencao();
    return;
  }

  digitalWrite(ledVermelho, LOW);
  Serial.print("\n");
  for (byte i = 0; i < leitor.uid.size; i++){
    rfid_data += String(leitor.uid.uidByte[i], HEX);

    if(i != 3){
      rfid_data += " ";
    }
  }
  rfid_data.toUpperCase();
  Serial.print(rfid_data);
 

  //if(EnviarDados(rfid_data)){
  //  //digitalWrite(ledVerde, HIGH);
  //  tone(buzzer, 250, 100);
  //  delay(100);
  //  tone(buzzer, 740,100);
  //  delay(1000);
  //  digitalWrite(ledVerde, LOW);
  //}
  //else{
  //  somAtencao();
  //}
}

// Método para envio das informações

bool EnviarDados(String rfid){
  char query[128];
  delay(1000);
  VerificarConexao();

  if(connection.connect(addr_server, port, user, key_mysql)){
    delay(200);
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&connection);
    //Salvar
    sprintf(query, command, rfid);
    // Executa o query
    cur_mem -> execute(query);
    delete cur_mem;
    Serial.println("Informacao salva com exito!!!");
    connection.close();
    return true;
  }
  else{
    Serial.println("Erro ao conecta com banco de dados");
    connection.close();
    return false;
  }
}

void somAtencao(){
  digitalWrite(ledAmarelo, HIGH);
  tone(buzzer, 150, 100);
  delay(140);
  tone(buzzer, 150, 100);
  delay(140);
  digitalWrite(ledAmarelo, LOW);
}